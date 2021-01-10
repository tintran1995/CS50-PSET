#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = (int) round((float)(image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtGreen = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][j].rgbtRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp;
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2 ; j++)
        {
            tmp = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Create tmp original array
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // Blurring process by averaging surrounding and original pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int count = 0;
            float rsum = 0;
            float gsum = 0;
            float bsum = 0;

            // Check for corner and edges
            for (int x = i - 1; x < i + 2; x++)
            {
                if (x < 0 || x > height - 1)
                {
                    continue;
                }
                for (int y = j - 1; y < j + 2; y++)
                {
                    if (y < 0 || y > width - 1)
                    {
                        continue;
                    }
                    else
                    {
                        rsum += tmp[x][y].rgbtRed;
                        gsum += tmp[x][y].rgbtGreen;
                        bsum += tmp[x][y].rgbtBlue;
                        count++;
                    }
                }
            }
            // Calculate average pixel value
            image[i][j].rgbtRed = (int) round(rsum / count);
            image[i][j].rgbtGreen = (int) round(gsum / count);
            image[i][j].rgbtBlue = (int) round(bsum / count);
        }

    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create tmp original array
    RGBTRIPLE tmp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            tmp[i][j] = image[i][j];
        }
    }

    // Detect edges using Gx and Gy
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float rGx = 0;
            float rGy = 0;
            float gGx = 0;
            float gGy = 0;
            float bGx = 0;
            float bGy = 0;

            // Top left
            if (i > 0 && j > 0)
            {
                rGx += -1 * tmp[i - 1][j - 1].rgbtRed;
                rGy += -1 * tmp[i - 1][j - 1].rgbtRed;
                gGx += -1 * tmp[i - 1][j - 1].rgbtGreen;
                gGy += -1 * tmp[i - 1][j - 1].rgbtGreen;
                bGx += -1 * tmp[i - 1][j - 1].rgbtBlue;
                bGy += -1 * tmp[i - 1][j - 1].rgbtBlue;
            }

            // Top
            if (i > 0)
            {
                rGy += -2 * tmp[i - 1][j].rgbtRed;
                gGy += -2 * tmp[i - 1][j].rgbtGreen;
                bGy += -2 * tmp[i - 1][j].rgbtBlue;
            }

            // Top Right
            if (i > 0 && j < width - 1)
            {
                rGx += tmp[i - 1][j + 1].rgbtRed;
                rGy += -1 * tmp[i - 1][j + 1].rgbtRed;
                gGx += tmp[i - 1][j + 1].rgbtGreen;
                gGy += -1 * tmp[i - 1][j + 1].rgbtGreen;
                bGx += tmp[i - 1][j + 1].rgbtBlue;
                bGy += -1 * tmp[i - 1][j + 1].rgbtBlue;
            }

            // Left
            if (j > 0)
            {
                rGx += -2 * tmp[i][j - 1].rgbtRed;
                gGx += -2 * tmp[i][j - 1].rgbtGreen;
                bGx += -2 * tmp[i][j - 1].rgbtBlue;
            }

            // Right
            if (j < width - 1)
            {
                rGx += 2 * tmp[i][j + 1].rgbtRed;
                gGx += 2 * tmp[i][j + 1].rgbtGreen;
                bGx += 2 * tmp[i][j + 1].rgbtBlue;
            }

            // Bottom Left
            if (i < height - 1 && j > 0)
            {
                rGx += -1 * tmp[i + 1][j - 1].rgbtRed;
                rGy += tmp[i + 1][j - 1].rgbtRed;
                gGx += -1 * tmp[i + 1][j - 1].rgbtGreen;
                gGy += tmp[i + 1][j - 1].rgbtGreen;
                bGx += -1 * tmp[i + 1][j - 1].rgbtBlue;
                bGy += tmp[i + 1][j - 1].rgbtBlue;
            }

            // Bottom
            if (i < height - 1)
            {
                rGy += 2 * tmp[i + 1][j].rgbtRed;
                gGy += 2 * tmp[i + 1][j].rgbtGreen;
                bGy += 2 * tmp[i + 1][j].rgbtBlue;
            }

            // Bottom Right
            if (i < height - 1 && j < width - 1)
            {
                rGx += tmp[i + 1][j + 1].rgbtRed;
                rGy += tmp[i + 1][j + 1].rgbtRed;
                gGx += tmp[i + 1][j + 1].rgbtGreen;
                gGy += tmp[i + 1][j + 1].rgbtGreen;
                bGx += tmp[i + 1][j + 1].rgbtBlue;
                bGy += tmp[i + 1][j + 1].rgbtBlue;
            }

            image[i][j].rgbtRed = (int) fmin(round(sqrt(rGx * rGx + rGy * rGy)), 255);
            image[i][j].rgbtGreen = (int) fmin(round(sqrt(gGx * gGx + gGy * gGy)), 255);
            image[i][j].rgbtBlue = (int) fmin(round(sqrt(bGx * bGx + bGy * bGy)), 255);
        }
    }
    return;
}
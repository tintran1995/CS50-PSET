#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    //Get positive height in 1-8 range
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    //Build walls
    for (int i = 0; i < height; i++)
    {
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }

        for (int k = 0; k <= i; k++)
        {
            printf("#");
        }

        printf("  ");

        for (int l = 0; l <= i; l++)
        {
            printf("#");
        }

        printf("\n");
    }
}
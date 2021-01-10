#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open file
    FILE *file = fopen(argv[1], "r");
    if (!file)
    {
        printf("File cannot be open\n");
        printf("Usage: ./recover image\n");
        return 1;
    }

    unsigned char bytes[512];
    int filecounter = 0;
    char filename[8];
    sprintf(filename, "%03i.jpg", filecounter);
    FILE *img = fopen(filename, "w");

    // Read 512 blocks into buffer then start writing into new jpgs
    while (fread(bytes, 512, 1, file) == 1)
    {
        if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
        {
            if (filecounter == 0)
            {
                fwrite(bytes, 512, 1, img);
                filecounter++;
            }
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", filecounter);
                img = fopen(filename, "w");
                fwrite(bytes, 512, 1, img);
                filecounter++;
            }
        }
        else if (filecounter != 0)
        {
            fwrite(bytes, 512, 1, img);
        }
    }
    fclose(img);
    fclose(file);
}
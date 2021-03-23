#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
typedef uint8_t BYTE;


int main(int argc, char *argv[])
{
    bool found = NULL;
    int counter = 0;
    BYTE buffer[512];
    char imgnumber[8];
    FILE *img;
    if (argc != 2)
    {
        return 1;
    }
    FILE *card = fopen(argv[1], "r");
    while(fread(&buffer, 512, 1, card) == 1)
    {
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            found = true;
            if (counter == 0)
            {
                sprintf(imgnumber, "%03i.jpg", counter);
                img = fopen(imgnumber, "w");
                fwrite(&buffer, 512, 1, img);
                counter++;
            }
            else if (counter != 0)
            {
                fclose(img);
                sprintf(imgnumber, "%03i.jpg", counter);
                img = fopen(imgnumber, "w");
                fwrite(&buffer, 512, 1, img);
                counter++;
            }

        }
        else if(found == true)
        {
            fwrite(&buffer, 512, 1, img);
        }
    }
    fclose(img);
    fclose(card);
    return 0;
}

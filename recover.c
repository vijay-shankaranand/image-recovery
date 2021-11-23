#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
typedef uint8_t BYTE;
bool isnewjpeg(BYTE buffer[]);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
FILE *currentfile = fopen(argv[1], "r");
    if (currentfile == NULL)
    {
        printf("File not found\n");
        return 1;
    }
BYTE buffer[512];
bool firstjpegfound = false;
FILE *newfile;
int i = 0;
    while (fread(buffer, 512 , 1, currentfile))
    {
        if (isnewjpeg(buffer))
        {
            if(!firstjpegfound)
            firstjpegfound = true;

            else
            fclose(newfile);
            
            char filename[8];
            sprintf(filename, "%03i.jpg" , i++);
            
            newfile = fopen(filename,"w");
            if (newfile == NULL)
            return 1;
            fwrite(buffer , 512 , 1 , newfile);
        }
        else if (firstjpegfound)
        fwrite(buffer , 512 , 1 , newfile);
    
    }
fclose(newfile);
fclose(currentfile);
}

bool isnewjpeg(BYTE buffer[])
{
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    return true;
    else 
    return false;
}
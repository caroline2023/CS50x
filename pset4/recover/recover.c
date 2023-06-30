#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdint.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        //check usage
        printf("Check usage\n");
        return 1;
    }
    
    //open file
    FILE *f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Cannot be opened\n");
        return 1;
    }
    
    BYTE *bytes = malloc(512);
    int n = 0; //keeps track of how many blocks of 512 we have
    int x = 0; //keeps track of how many jpgs we have
    char *filename = malloc(8);
    FILE *img = NULL;
    int t = 0;
    
    while (t == 0)
    {
        //put it into the buffer
        int k = fread(bytes, sizeof(BYTE), 512, f); //number of bytes we've read
        if (k == 0)
        {
            break;
        }
        
        //first jpg
        if (img == NULL)
        {
            if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
            {
                sprintf(filename, "%03i.jpg", x); //keep track of the file thing
                x++;
                img = fopen(filename, "w");
                fwrite(bytes, sizeof(BYTE), k, img);
            }
        }
        
        //jpgs after
        else if (img != NULL)
        {
            if (bytes[0] == 0xff && bytes[1] == 0xd8 && bytes[2] == 0xff && (bytes[3] & 0xf0) == 0xe0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", x); //keep track of the file thing
                x++;
                img = fopen(filename, "w");
            }
            fwrite(bytes, sizeof(BYTE), k, img);
        }
    }
    
    fclose(f);
    fclose(img);
    free(bytes);
    free(filename);
    
    return 0;
}

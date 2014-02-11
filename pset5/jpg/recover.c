/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
 
// defines block size to 512 to avoid magic numbers
#define BLOCKSIZE 512

// define length of output file names
#define FILENAME_LENGTH 8
 
int main(void)
{
    // open file
    FILE* file = fopen("card.raw", "r");
     
    // checks to see that pointer is not NULL
    if (file == NULL)
    {
        printf("Error: Could not open image. Please try again.\n");
        return 1;
    }
    
    // create array to store jpeg
    char jpeg_filename[FILENAME_LENGTH];
    // define int to store name of jpg image
    int jpeg_number = 0;
    // create pointer to outfile
    FILE* outfile = NULL;
    
    // create buffer to store block
    unsigned char buffer[BLOCKSIZE];
    
    // read 512 bytes into buffer because file is a multiple of 512 bytes in length
    while(fread(buffer,1,BLOCKSIZE,file) == BLOCKSIZE)
    {    
        // check for jpeg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] && buffer[2] == 0xff 
        && (buffer[3] == 0xe0 || buffer[3] == 0xe1))
        {
            // if start of new jpeg, close previous file
            if (outfile != NULL)
            {
                fclose(outfile);
            }
             
            // name image
            sprintf(jpeg_filename, "%03d.jpg", jpeg_number);
            jpeg_number++;
             
            // create new jpeg image
            outfile = fopen(jpeg_filename, "w+");
             
            // check pointer is not NULL
            if(outfile == NULL)
            {
                fclose(file);
                printf("Error: Could not create image\n");
                return 1;
            }
        }
        
        // write block to outfile if a JPEG is opened
        if (outfile != NULL)
        {
            // check that block is successfully written
            if (fwrite(buffer, 1, BLOCKSIZE, outfile) != BLOCKSIZE)
            {
                fclose(outfile);
                fclose(file);
                printf("Error writing file");
                return 1;
            }
        }
    }       
     
    // close last jpeg file
    if (outfile != NULL)
    {
        fclose(outfile);
    }
    
    // check if reading was stopped due to error
    if (ferror(file))
    {
        fclose(file);
        printf("Error reading file");
        return 1;
    }
    
    // close raw file
    fclose(file); 
    return 0;
}

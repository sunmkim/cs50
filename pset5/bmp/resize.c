/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int n = atoi(argv[1]);
    char* infile = argv[2];
    char* outfile = argv[3];
    
    

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    
    // save original dimensions into new variables
    int original_width = bi.biWidth;
    int original_height = bi.biHeight;
    
    // change biHeight, biWidth & biSizeImage
    bi.biHeight *=  n;
    bi.biWidth *= n;
    bi.biSizeImage *= n;
    
    // determine paddings
    int original_padding = (4 - original_width * (sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // update header info
    bi.biSizeImage = abs(bi.biHeight) * ((bi.biWidth * sizeof(RGBTRIPLE)) + padding);
    bf.bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + bi.biSizeImage; 
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);
    
    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // declare for buffer
    RGBTRIPLE *buffer = malloc(sizeof(RGBTRIPLE)*bi.biWidth);
    
    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(original_height); i < biHeight; i++)
    {   
        int count = 0;
        
        // iterate over pixels in scanline
        for (int j=0; j < original_width; j++)
        {
            // temporary storage
            RGBTRIPLE triple;
            
            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
            
        // iterate over per pixel by scale size
        for (int k = 0; k < n; k++)
        {
            buffer[count] = triple;
            count++;
        }
    }
        
    // skip over padding, if any
    fseek(inptr, original_padding, SEEK_CUR);

    // print each row
    for(int row = 0; row < n; row++)
    {  
        // write RGB triple to outfile
        fwrite(buffer, sizeof(RGBTRIPLE), bi.biWidth, outptr);
        
        // write padding    
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}

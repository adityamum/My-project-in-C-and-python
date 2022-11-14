// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;
uint8_t header[44];
int16_t buffer;


int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);


    fread (header, 1, HEADER_SIZE, input);
    fwrite(header, 1, HEADER_SIZE, output);     //reading header of 44-byte



    while (fread(&buffer, 1 , 2, input) == 2)  //computing 2-byte of wav file
    {

        buffer = buffer * factor;
        fwrite(&buffer, 1 , 2, output);

    }

    // Close files
    fclose(input);
    fclose(output);
}

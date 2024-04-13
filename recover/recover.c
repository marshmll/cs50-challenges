#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FAT_BLOCK_SIZE 512

typedef uint8_t BYTE;

int has_header(BYTE buffer[FAT_BLOCK_SIZE]);
void set_current_outfile_name(char name[], int number);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE.\n");
        return 1;
    }

    // Open the memory card
    char *filename = argv[1];
    FILE *infile = fopen(filename, "r");
    if (infile == NULL)
    {
        printf("Could not open file %s.\n", filename);
        return 2;
    }

    FILE *outfile;
    BYTE buffer[FAT_BLOCK_SIZE];

    int image_count = 0;
    int writing = 0;
    char outfilename[] = "###.jpg";

    // While there's still data left to read from the memory card
    while (fread(buffer, FAT_BLOCK_SIZE, 1, infile))
    {
        // If it's a beginning of a .jpg file and not currently writing one
        // Increase the image counter, set the filename, open a new file and set writing status.
        if (has_header(buffer) && !writing)
        {
            image_count++;
            set_current_outfile_name(outfilename, image_count - 1);
            outfile = fopen(outfilename, "w");
            writing = 1;
        }
        // Else if it's a beginning of a .jpg file and currently writing one
        // Increase the image counter, close the current file, set a new filename
        // and open a new file.
        else if (has_header(buffer) && writing)
        {
            image_count++;
            fclose(outfile);
            set_current_outfile_name(outfilename, image_count - 1);
            outfile = fopen(outfilename, "w");
        }
        // If writing status returns true
        // write the data from the buffer to the outfile.
        if (writing)
        {
            fwrite(buffer, FAT_BLOCK_SIZE, 1, outfile);
        }
    }

    fclose(outfile);
    fclose(infile);
}
// Verify the 4 starting bytes and returns true if matches
// .jpg header values.
int has_header(BYTE buffer[FAT_BLOCK_SIZE])
{
    if (buffer[0] == 0xFF && buffer[1] == 0xD8 && buffer[2] == 0xFF && buffer[3] >= 0xE0 && buffer[3] <= 0xEF)
        return 1;
    return 0;
}
// Set the formatted outfile name according to the count of images.
void set_current_outfile_name(char name[], int number)
{
    for (int i = 0; i < 3; i++)
    {
        int module = number % (int) pow(10, i + 1);
        int digit = module / (int) pow(10, i);

        char digit_char = 48 + digit;

        name[2 - i] = digit_char;
    }
    return;
}

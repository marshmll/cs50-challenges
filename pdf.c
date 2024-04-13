#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: ./pdf filename\n");
        return 1;
    }

    char *filename = argv[1];
    FILE *f = fopen(filename, "r");

    uint8_t buffer[4];

    fread(buffer, 1, 4, f);

    if (buffer[0] == 37 && buffer[1] == 80 && buffer[2] == 68 && buffer[3] == 70)
    {
        printf("File %s is in PDF format.\n", filename);
        return 0;
    }
    else
    {
        printf("File %s is not in PDF format.\n", filename);
        return 2;
    }

    fclose(f);
}

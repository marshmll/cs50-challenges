#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
        height = get_int("Height: ");
    while (height > 8 || height < 1);


    // Loops into each row.
    for (int i = 1; i <= height; i++)
    {
        // This variables avoid magic numbers in the code.
        int blocksPerLine = 2 * i;
        int leftSpaces = height - i;
        int middleLineIndex = (blocksPerLine / 2) - 1;

        // Prints the spaces on left.
        for (int j = 0; j < leftSpaces; j++)
            printf(" ");

        // Prints the blocks.
        for (int j = 0; j < blocksPerLine; j++)
        {
            printf("#");

            // Verifies if we are in the middle of the row.
            if (j == middleLineIndex)
                // If so, we print two spaces.
                printf("  ");
        }
        // Break into the next row.
        printf("\n");
    }
}

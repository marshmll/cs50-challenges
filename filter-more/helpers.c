#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int average = round((float) (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3);
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // For each row
    RGBTRIPLE row[width];
    for (int i = 0; i < height; i++)
    {
        // Reverse-copy the row.
        for (int j = 0; j < width; j++)
        {
            row[j].rgbtRed = image[i][(width - 1) - j].rgbtRed;
            row[j].rgbtGreen = image[i][(width - 1) - j].rgbtGreen;
            row[j].rgbtBlue = image[i][(width - 1) - j].rgbtBlue;
        }
        // Write the new-reversed row into the original image.
        for (int k = 0; k < width; k++)
        {
            image[i][k].rgbtRed = row[k].rgbtRed;
            image[i][k].rgbtGreen = row[k].rgbtGreen;
            image[i][k].rgbtBlue = row[k].rgbtBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred_image[height][width];

    // Iterate for each pixel.
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize auxiliary variables.
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;
            int pixels_on_grid = 0;

            // These loops will iterate through all adjacent pixels that surround the current pixel.
            for (int h = -1; h <= 1; h++)
            {
                for (int v = -1; v <= 1; v++)
                {
                    // If the current adjacent pixel is inside the image limits
                    if (i + h >= 0 && j + v >= 0 && i + h <= height - 1 && j + v <= width - 1)
                    {
                        // Add pixel RGB to the respective sums and increase the count of pixels in the grid.
                        red_sum += image[i + h][j + v].rgbtRed;
                        green_sum += image[i + h][j + v].rgbtGreen;
                        blue_sum += image[i + h][j + v].rgbtBlue;
                        pixels_on_grid++;
                    }
                }
            }
            // Set the current pixel of the blurred image as the average of the RGB values from the original image.
            blurred_image[i][j].rgbtRed = round((float) red_sum / (float) pixels_on_grid);
            blurred_image[i][j].rgbtGreen = round((float) green_sum / (float) pixels_on_grid);
            blurred_image[i][j].rgbtBlue = round((float) blue_sum / (float) pixels_on_grid);
        }
    }

    // Write the new blurred image into the original image.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = blurred_image[h][w];
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edged_image[height][width];
    // Sobel Operator Matrices.
    const int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    const int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Initialize variables for each channel and respective matrix.
            float red_gx = 0, green_gx = 0, blue_gx = 0;
            float red_gy = 0, green_gy = 0, blue_gy = 0;

            // These loops will iterate through all adjacent pixels that surround the current pixel.
            for (int k = -1; k <= 1; k++)
            {
                for (int l = -1; l <= 1; l++)
                {
                    // If the adjacent pixel is inside image limits, use its channels values
                    // else, assume all channels are 0;
                    if (i + k >= 0 && j + l >= 0 && i + k <= height - 1 && j + l <= width - 1)
                    {
                        red_gx += image[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                        green_gx += image[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                        blue_gx += image[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];

                        red_gy += image[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                        green_gy += image[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                        blue_gy += image[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                    }
                }
            }

            int sobel_red = 0, sobel_green = 0, sobel_blue = 0;

            // Sobel Operator: sqrt(Gx² + Gy²) (for all channels)
            sobel_red = round(sqrt((float) (red_gx * red_gx) + (float) (red_gy * red_gy)));
            sobel_green = round(sqrt((float) (green_gx * green_gx) + (float) (green_gy * green_gy)));
            sobel_blue = round(sqrt((float) (blue_gx * blue_gx) + (float) (blue_gy * blue_gy)));

            // Assure that the new values are smaller than 255 (max).
            if (sobel_red > 255)
                sobel_red = 255;

            if (sobel_green > 255)
                sobel_green = 255;

            if (sobel_blue > 255)
                sobel_blue = 255;

            // Save the new pixel channels into the new generated image.
            edged_image[i][j].rgbtRed = sobel_red;
            edged_image[i][j].rgbtGreen = sobel_green;
            edged_image[i][j].rgbtBlue = sobel_blue;
        }
    }

    // Write the new edged image into the original image.
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            image[h][w] = edged_image[h][w];
        }
    }

    return;
}

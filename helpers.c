#include "helpers.h"
#include <math.h>

// Swaps two values
void swap(BYTE *a, BYTE *b)
{
    BYTE temp = *a;
    *a = *b;
    *b = temp;
    return;
}

// Adds to sum
void addall(int *rsum, int *gsum, int *bsum, RGBTRIPLE x, int *n)
{
    *rsum += x.rgbtRed;
    *gsum += x.rgbtGreen;
    *bsum += x.rgbtBlue;
    (*n)++;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            BYTE x = round((float)(image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / (float)3);
            image[i][j].rgbtRed = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtBlue = x;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int r = round(image[i][j].rgbtRed * .393 + image[i][j].rgbtGreen * .769 + image[i][j].rgbtBlue * .189);
            int g = round(image[i][j].rgbtRed * .349 + image[i][j].rgbtGreen * .686 + image[i][j].rgbtBlue * .168);
            int b = round(image[i][j].rgbtRed * .272 + image[i][j].rgbtGreen * .534 + image[i][j].rgbtBlue * .131);
            if (r > 255)
            {
                r = 255;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b > 255)
            {
                b = 255;
            }
            image[i][j].rgbtRed = r;
            image[i][j].rgbtGreen = g;
            image[i][j].rgbtBlue = b;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j].rgbtRed, &image[i][width - j - 1].rgbtRed);
            swap(&image[i][j].rgbtGreen, &image[i][width - j - 1].rgbtGreen);
            swap(&image[i][j].rgbtBlue, &image[i][width - j - 1].rgbtBlue);
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Imagec -> Image Copy
    RGBTRIPLE imagec[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            imagec[i][j].rgbtRed = image[i][j].rgbtRed;
            imagec[i][j].rgbtGreen = image[i][j].rgbtGreen;
            imagec[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rsum = imagec[i][j].rgbtRed, gsum = imagec[i][j].rgbtGreen, bsum = imagec[i][j].rgbtBlue;
            int n = 1;
            if (i == 0)
            {
                if (j == 0)
                {
                    addall(&rsum, &gsum, &bsum, imagec[i + 1][j], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i][j + 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i + 1][j + 1], &n);
                }
                else if (j == width - 1)
                {
                    addall(&rsum, &gsum, &bsum, imagec[i][j - 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i + 1][j], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i + 1][j - 1], &n);
                }
                else
                {
                    addall(&rsum, &gsum, &bsum, imagec[i][j + 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i][j - 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i + 1][j], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i + 1][j + 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i + 1][j - 1], &n);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    addall(&rsum, &gsum, &bsum, imagec[i][j + 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i - 1][j], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i - 1][j + 1], &n);
                }
                else if (j == width - 1)
                {
                    addall(&rsum, &gsum, &bsum, imagec[i][j - 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i - 1][j], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i - 1][j - 1], &n);
                }
                else
                {
                    addall(&rsum, &gsum, &bsum, imagec[i][j + 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i][j - 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i - 1][j], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i - 1][j + 1], &n);
                    addall(&rsum, &gsum, &bsum, imagec[i - 1][j - 1], &n);
                }
            }
            else if (j == 0)
            {
                addall(&rsum, &gsum, &bsum, imagec[i][j + 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i - 1][j], &n);
                addall(&rsum, &gsum, &bsum, imagec[i - 1][j + 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i + 1][j], &n);
                addall(&rsum, &gsum, &bsum, imagec[i + 1][j + 1], &n);
            }
            else if (j == width - 1)
            {
                addall(&rsum, &gsum, &bsum, imagec[i][j - 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i - 1][j], &n);
                addall(&rsum, &gsum, &bsum, imagec[i - 1][j - 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i + 1][j], &n);
                addall(&rsum, &gsum, &bsum, imagec[i + 1][j - 1], &n);
            }
            else
            {
                addall(&rsum, &gsum, &bsum, imagec[i - 1][j - 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i - 1][j], &n);
                addall(&rsum, &gsum, &bsum, imagec[i - 1][j + 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i][j - 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i][j + 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i + 1][j - 1], &n);
                addall(&rsum, &gsum, &bsum, imagec[i + 1][j], &n);
                addall(&rsum, &gsum, &bsum, imagec[i + 1][j + 1], &n);
            }
            image[i][j].rgbtRed = round((float)(rsum) / (float)(n));
            image[i][j].rgbtGreen = round((float)(gsum) / (float)(n));
            image[i][j].rgbtBlue = round((float)(bsum) / (float)(n));
        }
    }
    return;
}



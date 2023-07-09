#include "helpers.h"
#include <math.h>

void sobel(int height, int width, RGBTRIPLE imagec[height][width], RGBTRIPLE image[height][width], int k, int l)
{
    RGBTRIPLE temp;
    int rgx = 0, rgy = 0, ggx = 0, ggy = 0, bgx = 0, bgy = 0;
    int temp2 = 0;
    for (int k2 = k - 1; k2 < k + 2; k2++)
    {
        for (int l2 = l - 1; l2 < l + 2; l2++)
        {
            if (k2 < 0 || l2 < 0 || k2 == height || l2 == width)
            {
                temp.rgbtRed = 0, temp.rgbtGreen = 0, temp.rgbtBlue = 0;
            }
            else
                // Middle element surrounded by 8 elements
            {
                temp.rgbtRed = imagec[k2][l2].rgbtRed;
                temp.rgbtGreen = imagec[k2][l2].rgbtGreen;
                temp.rgbtBlue = imagec[k2][l2].rgbtBlue;
            }
            switch (temp2)
            {
                case 0:
                    rgx += -1 * temp.rgbtRed;
                    rgy += -1 * temp.rgbtRed;
                    ggx += -1 * temp.rgbtGreen;
                    ggy += -1 * temp.rgbtGreen;
                    bgx += -1 * temp.rgbtBlue;
                    bgy += -1 * temp.rgbtBlue;
                    break;

                case 1:
                    rgy += -2 * temp.rgbtRed;
                    ggy += -2 * temp.rgbtGreen;
                    bgy += -2 * temp.rgbtBlue;
                    break;

                case 2:
                    rgx += 1 * temp.rgbtRed;
                    rgy += -1 * temp.rgbtRed;
                    ggx += 1 * temp.rgbtGreen;
                    ggy += -1 * temp.rgbtGreen;
                    bgx += 1 * temp.rgbtBlue;
                    bgy += -1 * temp.rgbtBlue;
                    break;

                case 3:
                    rgx += -2 * temp.rgbtRed;
                    ggx += -2 * temp.rgbtGreen;
                    bgx += -2 * temp.rgbtBlue;
                    break;

                case 5:
                    rgx += 2 * temp.rgbtRed;
                    ggx += 2 * temp.rgbtGreen;
                    bgx += 2 * temp.rgbtBlue;
                    break;

                case 6:
                    rgx += -1 * temp.rgbtRed;
                    rgy += 1 * temp.rgbtRed;
                    ggx += -1 * temp.rgbtGreen;
                    ggy += 1 * temp.rgbtGreen;
                    bgx += -1 * temp.rgbtBlue;
                    bgy += 1 * temp.rgbtBlue;
                    break;

                case 7:
                    rgy += 2 * temp.rgbtRed;
                    ggy += 2 * temp.rgbtGreen;
                    bgy += 2 * temp.rgbtBlue;
                    break;

                case 8:
                    rgx += 1 * temp.rgbtRed;
                    rgy += 1 * temp.rgbtRed;
                    ggx += 1 * temp.rgbtGreen;
                    ggy += 1 * temp.rgbtGreen;
                    bgx += 1 * temp.rgbtBlue;
                    bgy += 1 * temp.rgbtBlue;
                    break;
            }
            temp2++;
        }
    }
    int r = round(sqrt((float)rgx * rgx + (float)rgy * rgy));
    int g = round(sqrt((float)ggx * ggx + (float)ggy * ggy));
    int b = round(sqrt((float)bgx * bgx + (float)bgy * bgy));
    if (r > 255)
    {
        image[k][l].rgbtRed = 255;
    }
    else
    {
        image[k][l].rgbtRed = r;
    }
    if (g > 255)
    {
        image[k][l].rgbtGreen = 255;
    }
    else
    {
        image[k][l].rgbtGreen = g;
    }
    if (b > 255)
    {
        image[k][l].rgbtBlue = 255;
    }
    else
    {
        image[k][l].rgbtBlue = b;
    }
    return;
}

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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
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

    for (int k = 0; k < height; k++)
    {
        for (int l = 0; l < width; l++)
        {
            //Applies Sobel algorithm
            sobel(height, width, imagec, image, k, l);
        }
    }
    return;
}

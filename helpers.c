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
            int k = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);

            image[i][j].rgbtRed = k;
            image[i][j].rgbtGreen = k;
            image[i][j].rgbtBlue = k;

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
            RGBTRIPLE temp = image[i][j];
            int k = width - j - 1;
            image[i][j] = image[i][k];
            image[i][k] = temp;


        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float sumRed = 0;
            float sumGreen = 0;
            float sumBlue = 0;
            int counter = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        sumRed = sumRed + temp[i + k][j + l].rgbtRed;
                        sumGreen = sumGreen + temp[i + k][j + l].rgbtGreen;
                        sumBlue = sumBlue + temp[i + k][j + l].rgbtBlue;
                        counter++;
                    }
                }
            }
            image[i][j].rgbtRed = round(sumRed / counter);
            image[i][j].rgbtGreen = round(sumGreen / counter);
            image[i][j].rgbtBlue = round(sumBlue / counter);
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float GxRed = 0;
            float GxGreen = 0;
            float GxBlue = 0;
            float GyRed = 0;
            float GyGreen = 0;
            float GyBlue = 0;
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    if ((i + k >= 0 && i + k < height) && (j + l >= 0 && j + l < width))
                    {
                        GxRed += Gx[k + 1][l + 1] * temp[i + k][j + l].rgbtRed;
                        GxGreen += Gx[k + 1][l + 1] * temp[i + k][j + l].rgbtGreen;
                        GxBlue += Gx[k + 1][l + 1] * temp[i + k][j + l].rgbtBlue;

                        GyRed += Gx[k + 1][l + 1] * temp[i + k][j + l].rgbtRed;
                        GyGreen += Gx[k + 1][l + 1] * temp[i + k][j + l].rgbtGreen;
                        GyBlue += Gx[k + 1][l + 1] * temp[i + k][j + l].rgbtBlue;
                    }
                }
            }
            image[i][j].rgbtRed = round(sqrt(GxRed * GxRed + GyRed * GyRed));
            if (image[i][j].rgbtRed > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            image[i][j].rgbtGreen = round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen));
            if (image[i][j].rgbtGreen > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            image[i][j].rgbtBlue = round(sqrt(GxBlue * GxBlue + GyBlue * GyBlue));
            if (image[i][j].rgbtBlue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }

        }
    }
    return;
}

#include "helpers.h"
#include <stdlib.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int x; //define it here cuz defining in loop sounds annoying

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            x = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            //this would be the average of the rgb things
            image[i][j].rgbtBlue = x;
            image[i][j].rgbtGreen = x;
            image[i][j].rgbtRed = x;
        }
    } //use ./filter -g images/yard.bmp out.bmp to execute code
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*newimage)[width] = calloc(height, width * sizeof(RGBTRIPLE)); //ok apparently u have to allocate memory

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            newimage[i][width - 1 - j].rgbtBlue = image[i][j].rgbtBlue; //let this become the reflected image
            newimage[i][width - 1 - j].rgbtGreen = image[i][j].rgbtGreen;
            newimage[i][width - 1 - j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue; //turn the original image to the reflected one
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
        }
    } //use ./filter -r images/yard.bmp out.bmp to execute code
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*newimage)[width] = calloc(height, width * sizeof(RGBTRIPLE)); //once again, create a copy

    //corners
    //upper left
    newimage[0][0].rgbtBlue =
        round((image[0][0].rgbtBlue + image[0][1].rgbtBlue + image[1][1].rgbtBlue + image[1][0].rgbtBlue) / 4.0);
    newimage[0][0].rgbtGreen =
        round((image[0][0].rgbtGreen + image[0][1].rgbtGreen + image[1][1].rgbtGreen + image[1][0].rgbtGreen) / 4.0);
    newimage[0][0].rgbtRed =
        round((image[0][0].rgbtRed + image[0][1].rgbtRed + image[1][1].rgbtRed + image[1][0].rgbtRed) / 4.0);

    //upper right
    newimage[0][width - 1].rgbtBlue =
        round((image[0][width - 1].rgbtBlue + image[0][width - 2].rgbtBlue +
               image[1][width - 2].rgbtBlue + image[1][width - 1].rgbtBlue) / 4.0);
    newimage[0][width - 1].rgbtGreen =
        round((image[0][width - 1].rgbtGreen + image[0][width - 2].rgbtGreen +
               image[1][width - 2].rgbtGreen + image[1][width - 1].rgbtGreen) / 4.0);
    newimage[0][width - 1].rgbtRed =
        round((image[0][width - 1].rgbtRed + image[0][width - 2].rgbtRed +
               image[1][width - 2].rgbtRed + image[1][width - 1].rgbtRed) / 4.0);

    //bottom right
    newimage[height - 1][width - 1].rgbtBlue =
        round((image[height - 1][width - 1].rgbtBlue + image[height - 1][width - 2].rgbtBlue +
               image[height - 2][width - 2].rgbtBlue + image[height - 2][width - 1].rgbtBlue) / 4.0);
    newimage[height - 1][width - 1].rgbtGreen =
        round((image[height - 1][width - 1].rgbtGreen + image[height - 1][width - 2].rgbtGreen +
               image[height - 2][width - 2].rgbtGreen + image[height - 2][width - 1].rgbtGreen) / 4.0);
    newimage[height - 1][width - 1].rgbtRed =
        round((image[height - 1][width - 1].rgbtRed + image[height - 1][width - 2].rgbtRed +
               image[height - 2][width - 2].rgbtRed + image[height - 2][width - 1].rgbtRed) / 4.0);

    //bottom left
    newimage[height - 1][0].rgbtBlue =
        round((image[height - 1][0].rgbtBlue + image[height - 1][1].rgbtBlue +
               image[height - 2][1].rgbtBlue + image[height - 2][0].rgbtBlue) / 4.0);
    newimage[height - 1][0].rgbtGreen =
        round((image[height - 1][0].rgbtGreen + image[height - 1][1].rgbtGreen +
               image[height - 2][1].rgbtGreen + image[height - 2][0].rgbtGreen) / 4.0);
    newimage[height - 1][0].rgbtRed =
        round((image[height - 1][0].rgbtRed + image[height - 1][1].rgbtRed +
               image[height - 2][1].rgbtRed + image[height - 2][0].rgbtRed) / 4.0);

    //sides
    //top row first
    for (int i = 1; i < width - 1; i++)
    {
        newimage[0][i].rgbtBlue =
            round((image[0][i - 1].rgbtBlue + image[0][i].rgbtBlue + image[0][i + 1].rgbtBlue +
                   image[1][i - 1].rgbtBlue + image[1][i].rgbtBlue + image[1][i + 1].rgbtBlue) / 6.0);
        newimage[0][i].rgbtGreen =
            round((image[0][i - 1].rgbtGreen + image[0][i].rgbtGreen + image[0][i + 1].rgbtGreen +
                   image[1][i - 1].rgbtGreen + image[1][i].rgbtGreen + image[1][i + 1].rgbtGreen) / 6.0);
        newimage[0][i].rgbtRed =
            round((image[0][i - 1].rgbtRed + image[0][i].rgbtRed + image[0][i + 1].rgbtRed +
                   image[1][i - 1].rgbtRed + image[1][i].rgbtRed + image[1][i + 1].rgbtRed) / 6.0);
    }
    //bottom row
    for (int i = 1; i < width - 1; i++)
    {
        newimage[height - 1][i].rgbtBlue =
            round((image[height - 1][i - 1].rgbtBlue + image[height - 1][i].rgbtBlue + image[height - 1][i + 1].rgbtBlue +
                   image[height - 2][i - 1].rgbtBlue + image[height - 2][i].rgbtBlue + image[height - 2][i + 1].rgbtBlue) / 6.0);
        newimage[height - 1][i].rgbtGreen =
            round((image[height - 1][i - 1].rgbtGreen + image[height - 1][i].rgbtGreen + image[height - 1][i + 1].rgbtGreen +
                   image[height - 2][i - 1].rgbtGreen + image[height - 2][i].rgbtGreen + image[height - 2][i + 1].rgbtGreen) / 6.0);
        newimage[height - 1][i].rgbtRed =
            round((image[height - 1][i - 1].rgbtRed + image[height - 1][i].rgbtRed + image[height - 1][i + 1].rgbtRed +
                   image[height - 2][i - 1].rgbtRed + image[height - 2][i].rgbtRed + image[height - 2][i + 1].rgbtRed) / 6.0);
    }
    //left side
    for (int i = 1; i < height - 1; i++)
    {
        newimage[i][0].rgbtBlue =
            round((image[i - 1][0].rgbtBlue + image[i][0].rgbtBlue + image[i + 1][0].rgbtBlue +
                   image[i - 1][1].rgbtBlue + image[i][1].rgbtBlue + image[i + 1][1].rgbtBlue) / 6.0);
        newimage[i][0].rgbtGreen =
            round((image[i - 1][0].rgbtGreen + image[i][0].rgbtGreen + image[i + 1][0].rgbtGreen +
                   image[i - 1][1].rgbtGreen + image[i][1].rgbtGreen + image[i + 1][1].rgbtGreen) / 6.0);
        newimage[i][0].rgbtRed =
            round((image[i - 1][0].rgbtRed + image[i][0].rgbtRed + image[i + 1][0].rgbtRed +
                   image[i - 1][1].rgbtRed + image[i][1].rgbtRed + image[i + 1][1].rgbtRed) / 6.0);
    }
    //right side
    for (int i = 1; i < height - 1; i++)
    {
        newimage[i][width - 1].rgbtBlue =
            round((image[i - 1][width - 1].rgbtBlue + image[i][width - 1].rgbtBlue + image[i + 1][width - 1].rgbtBlue +
                   image[i - 1][width - 2].rgbtBlue + image[i][width - 2].rgbtBlue + image[i + 1][width - 2].rgbtBlue) / 6.0);
        newimage[i][width - 1].rgbtGreen =
            round((image[i - 1][width - 1].rgbtGreen + image[i][width - 1].rgbtGreen + image[i + 1][width - 1].rgbtGreen +
                   image[i - 1][width - 2].rgbtGreen + image[i][width - 2].rgbtGreen + image[i + 1][width - 2].rgbtGreen) / 6.0);
        newimage[i][width - 1].rgbtRed =
            round((image[i - 1][width - 1].rgbtRed + image[i][width - 1].rgbtRed + image[i + 1][width - 1].rgbtRed +
                   image[i - 1][width - 2].rgbtRed + image[i][width - 2].rgbtRed + image[i + 1][width - 2].rgbtRed) / 6.0);
    }

    //the rest
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            newimage[i][j].rgbtBlue =
                round((image[i - 1][j - 1].rgbtBlue + image[i - 1][j].rgbtBlue + image[i - 1][j + 1].rgbtBlue +
                       image[i][j - 1].rgbtBlue + image[i][j].rgbtBlue + image[i][j + 1].rgbtBlue +
                       image[i + 1][j - 1].rgbtBlue + image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue) / 9.0);
            newimage[i][j].rgbtGreen =
                round((image[i - 1][j - 1].rgbtGreen + image[i - 1][j].rgbtGreen + image[i - 1][j + 1].rgbtGreen +
                       image[i][j - 1].rgbtGreen + image[i][j].rgbtGreen + image[i][j + 1].rgbtGreen +
                       image[i + 1][j - 1].rgbtGreen + image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen) / 9.0);
            newimage[i][j].rgbtRed =
                round((image[i - 1][j - 1].rgbtRed + image[i - 1][j].rgbtRed + image[i - 1][j + 1].rgbtRed +
                       image[i][j - 1].rgbtRed + image[i][j].rgbtRed + image[i][j + 1].rgbtRed +
                       image[i + 1][j - 1].rgbtRed + image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed) / 9.0);
        }
    }
    //change original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue; //turn the original image to the reflected one
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
        }
    }
    //use ./filter -b images/yard.bmp out.bmp to execute code
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE(*newimage)[width] = calloc(height, width * sizeof(RGBTRIPLE)); //once again, create a copy

    double Gx;
    double Gy;
    //corners
    //upper left
    Gx = 2 * image[0][1].rgbtBlue + image[1][1].rgbtBlue;
    Gy = 2 * image[1][0].rgbtBlue + image[1][1].rgbtBlue;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[0][0].rgbtBlue = 255;
    }
    else
    {
        newimage[0][0].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = 2 * image[0][1].rgbtGreen + image[1][1].rgbtGreen;
    Gy = 2 * image[1][0].rgbtGreen + image[1][1].rgbtGreen;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[0][0].rgbtGreen = 255;
    }
    else
    {
        newimage[0][0].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = 2 * image[0][1].rgbtRed + image[1][1].rgbtRed;
    Gy = 2 * image[1][0].rgbtRed + image[1][1].rgbtRed;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[0][0].rgbtRed = 255;
    }
    else
    {
        newimage[0][0].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
    }

    //upper right
    Gx = -2 * image[0][width - 2].rgbtBlue - image[1][width - 2].rgbtBlue;
    Gy = 2 * image[1][width - 1].rgbtBlue + image[1][width - 2].rgbtBlue;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[0][width - 1].rgbtBlue = 255;
    }
    else
    {
        newimage[0][width - 1].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = -2 * image[0][width - 2].rgbtGreen - image[1][width - 2].rgbtGreen;
    Gy = 2 * image[1][width - 1].rgbtGreen + image[1][width - 2].rgbtGreen;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[0][width - 1].rgbtGreen = 255;
    }
    else
    {
        newimage[0][width - 1].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = -2 * image[0][width - 2].rgbtRed - image[1][width - 2].rgbtRed;
    Gy = 2 * image[1][width - 1].rgbtRed + image[1][width - 2].rgbtRed;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[0][width - 1].rgbtRed = 255;
    }
    else
    {
        newimage[0][width - 1].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
    }

    //bottom right
    Gx = -2 * image[height - 1][width - 2].rgbtBlue - image[height - 2][width - 2].rgbtBlue;
    Gy = -2 * image[height - 2][width - 1].rgbtBlue - image[height - 2][width - 2].rgbtBlue;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[height - 1][width - 1].rgbtBlue = 255;
    }
    else
    {
        newimage[height - 1][width - 1].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = -2 * image[height - 1][width - 2].rgbtGreen - image[height - 2][width - 2].rgbtGreen;
    Gy = -2 * image[height - 2][width - 1].rgbtGreen - image[height - 2][width - 2].rgbtGreen;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[height - 1][width - 1].rgbtGreen = 255;
    }
    else
    {
        newimage[height - 1][width - 1].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = -2 * image[height - 1][width - 2].rgbtRed - image[height - 2][width - 2].rgbtRed;
    Gy = -2 * image[height - 2][width - 1].rgbtRed - image[height - 2][width - 2].rgbtRed;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[height - 1][width - 1].rgbtRed = 255;
    }
    else
    {
        newimage[height - 1][width - 1].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
    }

    //bottom left
    Gx = 2 * image[height - 1][1].rgbtBlue + image[height - 2][1].rgbtBlue;
    Gy = -2 * image[height - 2][0].rgbtBlue - image[height - 2][1].rgbtBlue;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[height - 1][0].rgbtBlue = 255;
    }
    else
    {
        newimage[height - 1][0].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = 2 * image[height - 1][1].rgbtGreen + image[height - 2][1].rgbtGreen;
    Gy = -2 * image[height - 2][0].rgbtGreen - image[height - 2][1].rgbtGreen;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[height - 1][0].rgbtGreen = 255;
    }
    else
    {
        newimage[height - 1][0].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
    }

    Gx = 2 * image[height - 1][1].rgbtRed + image[height - 2][1].rgbtRed;
    Gy = -2 * image[height - 2][0].rgbtRed - image[height - 2][1].rgbtRed;
    if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
    {
        newimage[height - 1][0].rgbtRed = 255;
    }
    else
    {
        newimage[height - 1][0].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
    }

    //sides
    //top
    for (int i = 1; i < width - 1; i++)
    {
        Gx = -2 * image[0][i - 1].rgbtBlue - image[1][i - 1].rgbtBlue +
             2 * image[0][i + 1].rgbtBlue + image[1][i + 1].rgbtBlue;
        Gy = image[1][i - 1].rgbtBlue + 2 * image[1][i].rgbtBlue + image[1][i + 1].rgbtBlue;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[0][i].rgbtBlue = 255;
        }
        else
        {
            newimage[0][i].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = -2 * image[0][i - 1].rgbtGreen - image[1][i - 1].rgbtGreen +
             2 * image[0][i + 1].rgbtGreen + image[1][i + 1].rgbtGreen;
        Gy = image[1][i - 1].rgbtGreen + 2 * image[1][i].rgbtGreen + image[1][i + 1].rgbtGreen;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[0][i].rgbtGreen = 255;
        }
        else
        {
            newimage[0][i].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = -2 * image[0][i - 1].rgbtRed - image[1][i - 1].rgbtRed +
             2 * image[0][i + 1].rgbtRed + image[1][i + 1].rgbtRed;
        Gy = image[1][i - 1].rgbtRed + 2 * image[1][i].rgbtRed + image[1][i + 1].rgbtRed;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[0][i].rgbtRed = 255;
        }
        else
        {
            newimage[0][i].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
        }
    }

    //bottom
    for (int i = 1; i < width - 1; i++)
    {
        Gx = -2 * image[height - 1][i - 1].rgbtBlue - image[height - 2][i - 1].rgbtBlue +
             2 * image[height - 1][i + 1].rgbtBlue + image[height - 2][i + 1].rgbtBlue;
        Gy = -image[height - 2][i - 1].rgbtBlue - 2 * image[height - 2][i].rgbtBlue - image[height - 2][i + 1].rgbtBlue;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[height - 1][i].rgbtBlue = 255;
        }
        else
        {
            newimage[height - 1][i].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = -2 * image[height - 1][i - 1].rgbtGreen - image[height - 2][i - 1].rgbtGreen +
             2 * image[height - 1][i + 1].rgbtGreen + image[height - 2][i + 1].rgbtGreen;
        Gy = -image[height - 2][i - 1].rgbtGreen - 2 * image[height - 2][i].rgbtGreen - image[height - 2][i + 1].rgbtGreen;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[height - 1][i].rgbtGreen = 255;
        }
        else
        {
            newimage[height - 1][i].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = -2 * image[height - 1][i - 1].rgbtRed - image[height - 2][i - 1].rgbtRed +
             2 * image[height - 1][i + 1].rgbtRed + image[height - 2][i + 1].rgbtRed;
        Gy = -image[height - 2][i - 1].rgbtRed - 2 * image[height - 2][i].rgbtRed - image[height - 2][i + 1].rgbtRed;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[height - 1][i].rgbtRed = 255;
        }
        else
        {
            newimage[height - 1][i].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
        }
    }

    //left
    for (int i = 1; i < height - 1; i++)
    {
        Gx = image[i - 1][1].rgbtBlue + 2 * image[i][1].rgbtBlue + image[i + 1][1].rgbtBlue;
        Gy = -2 * image[i - 1][0].rgbtBlue - image[i - 1][1].rgbtBlue +
             2 * image[i + 1][0].rgbtBlue + image[i + 1][1].rgbtBlue;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[i][0].rgbtBlue = 255;
        }
        else
        {
            newimage[i][0].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = image[i - 1][1].rgbtGreen + 2 * image[i][1].rgbtGreen + image[i + 1][1].rgbtGreen;
        Gy = -2 * image[i - 1][0].rgbtGreen - image[i - 1][1].rgbtGreen +
             2 * image[i + 1][0].rgbtGreen + image[i + 1][1].rgbtGreen;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[i][0].rgbtGreen = 255;
        }
        else
        {
            newimage[i][0].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = image[i - 1][1].rgbtRed + 2 * image[i][1].rgbtRed + image[i + 1][1].rgbtRed;
        Gy = -2 * image[i - 1][0].rgbtRed - image[i - 1][1].rgbtRed +
             2 * image[i + 1][0].rgbtRed + image[i + 1][1].rgbtRed;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[i][0].rgbtRed = 255;
        }
        else
        {
            newimage[i][0].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
        }
    }

    //right
    for (int i = 1; i < height - 1; i++)
    {
        Gx = image[i - 1][width - 2].rgbtBlue + 2 * image[i][width - 2].rgbtBlue + image[i + 1][width - 2].rgbtBlue;
        Gy = -2 * image[i - 1][width - 1].rgbtBlue - image[i - 1][width - 2].rgbtBlue +
             2 * image[i + 1][width - 1].rgbtBlue + image[i + 1][width - 2].rgbtBlue;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[i][width - 1].rgbtBlue = 255;
        }
        else
        {
            newimage[i][width - 1].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = image[i - 1][width - 2].rgbtGreen + 2 * image[i][width - 2].rgbtGreen + image[i + 1][width - 2].rgbtGreen;
        Gy = -2 * image[i - 1][width - 1].rgbtGreen - image[i - 1][width - 2].rgbtGreen +
             2 * image[i + 1][width - 1].rgbtGreen + image[i + 1][width - 2].rgbtGreen;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[i][width - 1].rgbtGreen = 255;
        }
        else
        {
            newimage[i][width - 1].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
        }

        Gx = image[i - 1][width - 2].rgbtRed + 2 * image[i][width - 2].rgbtRed + image[i + 1][width - 2].rgbtRed;
        Gy = -2 * image[i - 1][width - 1].rgbtRed - image[i - 1][width - 2].rgbtRed +
             2 * image[i + 1][width - 1].rgbtRed + image[i + 1][width - 2].rgbtRed;
        if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
        {
            newimage[i][width - 1].rgbtRed = 255;
        }
        else
        {
            newimage[i][width - 1].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
        }
    }

    //rest of them
    for (int i = 1; i < height - 1; i++)
    {
        for (int j = 1; j < width - 1; j++)
        {
            Gx = -image[i - 1][j - 1].rgbtBlue - 2 * image[i][j - 1].rgbtBlue - image[i + 1][j - 1].rgbtBlue +
                 image[i - 1][j + 1].rgbtBlue + 2 * image[i][j + 1].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            Gy = -image[i - 1][j - 1].rgbtBlue - 2 * image[i - 1][j].rgbtBlue - image[i - 1][j + 1].rgbtBlue +
                 image[i + 1][j - 1].rgbtBlue + 2 * image[i + 1][j].rgbtBlue + image[i + 1][j + 1].rgbtBlue;
            if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
            {
                newimage[i][j].rgbtBlue = 255;
            }
            else
            {
                newimage[i][j].rgbtBlue = round(sqrt(Gx * Gx + Gy * Gy));
            }

            Gx = -image[i - 1][j - 1].rgbtGreen - 2 * image[i][j - 1].rgbtGreen - image[i + 1][j - 1].rgbtGreen +
                 image[i - 1][j + 1].rgbtGreen + 2 * image[i][j + 1].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            Gy = -image[i - 1][j - 1].rgbtGreen - 2 * image[i - 1][j].rgbtGreen - image[i - 1][j + 1].rgbtGreen +
                 image[i + 1][j - 1].rgbtGreen + 2 * image[i + 1][j].rgbtGreen + image[i + 1][j + 1].rgbtGreen;
            if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
            {
                newimage[i][j].rgbtGreen = 255;
            }
            else
            {
                newimage[i][j].rgbtGreen = round(sqrt(Gx * Gx + Gy * Gy));
            }

            Gx = -image[i - 1][j - 1].rgbtRed - 2 * image[i][j - 1].rgbtRed - image[i + 1][j - 1].rgbtRed +
                 image[i - 1][j + 1].rgbtRed + 2 * image[i][j + 1].rgbtRed + image[i + 1][j + 1].rgbtRed;
            Gy = -image[i - 1][j - 1].rgbtRed - 2 * image[i - 1][j].rgbtRed - image[i - 1][j + 1].rgbtRed +
                 image[i + 1][j - 1].rgbtRed + 2 * image[i + 1][j].rgbtRed + image[i + 1][j + 1].rgbtRed;
            if (round(sqrt(Gx * Gx + Gy * Gy)) > 255) //cap it at 255
            {
                newimage[i][j].rgbtRed = 255;
            }
            else
            {
                newimage[i][j].rgbtRed = round(sqrt(Gx * Gx + Gy * Gy));
            }
        }
    }

    //change original image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtBlue = newimage[i][j].rgbtBlue; //turn the original image to the reflected one
            image[i][j].rgbtGreen = newimage[i][j].rgbtGreen;
            image[i][j].rgbtRed = newimage[i][j].rgbtRed;
        }
    }
    //use ./filter -e images/yard.bmp out.bmp to execute code
    return;
}

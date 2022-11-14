#include "helpers.h"
#include<math.h>
#include<stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg;

    for(int i = 0 ; i <= height - 1 ; i++){
        for(int j = 0 ; j <= width - 1 ; j++){
        RGBTRIPLE col = image[i][j];
        avg = round((col.rgbtBlue + col.rgbtGreen + col.rgbtRed) / 3.0);
            col.rgbtBlue = avg;
            col.rgbtGreen = avg;
            col.rgbtRed = avg;
            image[i][j] = col;

        }

    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int green;
    int blue;

    for(int i = 0 ; i <= height - 1 ; i++){
        for(int j = 0 ; j <= width - 1 ; j++){

            red = round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            green = round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            blue = round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));

            if(red > 255){

                red = 255;

            }

            if(green > 255){

             green = 255;

            }

            else if(blue > 255){

             blue = 255;
            }

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;


        }

        }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

RGBTRIPLE temp;
int x = width / 2;

 for(int i = 0; i< height ; i++){
    for(int j = 0 ; j < x ; j++){

        temp = image[i][width - j - 1];
        image[i][width - j - 1] = image[i][j];
        image[i][j] = temp;
    }

 }


    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int red;
    int green;
    int blue;


    for(int i = 0 ; i <= height -1 ; i++){

        for(int j = 0 ; j <= width - 1 ; j++){

            copy[i][j] = image[i][j];
        }
    }
     for(int i = 0 ; i <= height -1 ; i++){

        for(int j = 0 ; j <= width - 1 ; j++){

            if( i == 0 && j == 0){ //top left corner

                red = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed) / 4.0);
                green = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen) / 4.0);
                blue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue) / 4.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;

            }

            else if( i == (height - 1) && j == (width - 1)){ //rightend corner

                red = round((copy[i][j].rgbtRed + copy[i -1][j].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i][j-1].rgbtRed) / 4.0);
                green = round((copy[i][j].rgbtGreen + copy[i -1][j].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i][j-1].rgbtGreen) / 4.0);
                blue = round((copy[i][j].rgbtBlue + copy[i -1][j].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i][j-1].rgbtBlue) / 4.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;
            }

            else if(i == (height - 1) && j == 0){ // leftend corner

                red = round((copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j + 1].rgbtRed + copy[i][j+1].rgbtRed) / 4.0);
                green = round((copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j + 1].rgbtGreen + copy[i][j+1].rgbtGreen) / 4.0);
                blue = round((copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j + 1].rgbtBlue + copy[i][j+1].rgbtBlue) / 4.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;

            }

            else if(i == 0 && j == (width - 1)){ //top right corner

                red = round((copy[i][j].rgbtRed + copy[i][j-1].rgbtRed + copy[i + 1][j].rgbtRed + copy[i + 1][j - 1].rgbtRed) / 4.0);
                green = round((copy[i][j].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i + 1][j].rgbtGreen+ copy[i + 1][j - 1].rgbtGreen) / 4.0);
                blue = round((copy[i][j].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i + 1][j].rgbtBlue+ copy[i + 1][j - 1].rgbtBlue) / 4.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;

            }

            else if((i > 0  && i != (height - 1) && j == 0 )){ //edges below top left corner

                red = round((copy[i][j].rgbtRed + copy[i-1][j].rgbtRed + copy[i - 1][j+1].rgbtRed + copy[i][j+1].rgbtRed + copy[i+1][j+1].rgbtRed + copy[i+1][j].rgbtRed ) / 6.0);
                green = round((copy[i][j].rgbtGreen + copy[i-1][j].rgbtGreen  + copy[i - 1][j+1].rgbtGreen  + copy[i][j+1].rgbtGreen  + copy[i+1][j+1].rgbtGreen  + copy[i+1][j].rgbtGreen  ) / 6.0);
                blue = round((copy[i][j].rgbtBlue + copy[i-1][j].rgbtBlue  + copy[i - 1][j+1].rgbtBlue  + copy[i][j+1].rgbtBlue  + copy[i+1][j+1].rgbtBlue  + copy[i+1][j].rgbtBlue ) / 6.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;


            }

            else if((i > 0 && i != (height - 1)) && j == (height - 1) ){ //edges below top right corner

                red = round((copy[i][j].rgbtRed + copy[i - 1][j].rgbtRed + copy[i - 1][j - 1].rgbtRed + copy[i][j-1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i + 1][j].rgbtRed ) / 6.0);
                green =round((copy[i][j].rgbtGreen  + copy[i - 1][j].rgbtGreen + copy[i - 1][j - 1].rgbtGreen + copy[i][j-1].rgbtGreen  + copy[i+1][j-1].rgbtGreen  + copy[i + 1][j].rgbtGreen  ) / 6.0);
                blue =round((copy[i][j].rgbtBlue  + copy[i - 1][j].rgbtBlue + copy[i - 1][j - 1].rgbtBlue + copy[i][j-1].rgbtBlue  + copy[i+1][j-1].rgbtBlue  + copy[i + 1][j].rgbtBlue  ) / 6.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;

            }

            else if(i == 0 && (j > 0 && j != (width -1) )) { //edges after the right end corner

                    red = round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j+1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i][j-1].rgbtRed) / 6.0);
                    green = round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen + copy[i + 1][j+1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i][j-1].rgbtGreen) / 6.0);
                    blue = round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue + copy[i + 1][j+1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j-1].rgbtBlue+ copy[i][j-1].rgbtBlue) / 6.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;

            }

            else if(i == (height -1) && (j > 0 && j != (width -1))){ //edges after the left end corner

                red = round((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j-1].rgbtRed  + copy[i][j-1].rgbtRed ) /6.0);
                green = round((copy[i][j].rgbtGreen  + copy[i][j+1].rgbtGreen  + copy[i-1][j+1].rgbtGreen  + copy[i-1][j].rgbtGreen  + copy[i-1][j-1].rgbtGreen   + copy[i][j-1].rgbtGreen) /6.0);
                blue = round((copy[i][j].rgbtBlue  + copy[i][j+1].rgbtBlue  + copy[i-1][j+1].rgbtBlue  + copy[i-1][j].rgbtBlue  + copy[i-1][j-1].rgbtBlue   + copy[i][j-1].rgbtBlue) /6.0);

             image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;

            }
            else{ //tale care of middle pixels

                red = round((copy[i][j].rgbtRed + copy[i][j+1].rgbtRed + copy[i][j-1].rgbtRed + copy[i-1][j-1].rgbtRed + copy[i-1][j].rgbtRed + copy[i-1][j+1].rgbtRed + copy[i+1][j-1].rgbtRed + copy[i+1][j].rgbtRed + copy[i+1][j+1].rgbtRed)/9.0);
                green = round((copy[i][j].rgbtGreen + copy[i][j+1].rgbtGreen + copy[i][j-1].rgbtGreen + copy[i-1][j-1].rgbtGreen + copy[i-1][j].rgbtGreen + copy[i-1][j+1].rgbtGreen + copy[i+1][j-1].rgbtGreen + copy[i+1][j].rgbtGreen + copy[i+1][j+1].rgbtGreen)/9.0);
                blue = round((copy[i][j].rgbtBlue + copy[i][j+1].rgbtBlue + copy[i][j-1].rgbtBlue + copy[i-1][j-1].rgbtBlue + copy[i-1][j].rgbtBlue + copy[i-1][j+1].rgbtBlue + copy[i+1][j-1].rgbtBlue + copy[i+1][j].rgbtBlue + copy[i+1][j+1].rgbtBlue)/9.0);

              image[i][j].rgbtRed = red;
             image[i][j].rgbtGreen = green;
             image[i][j].rgbtBlue = blue;


            }




        }

     }

    return;
}

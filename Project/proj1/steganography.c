/************************************************************************
**
** NAME:        steganography.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**				Justin Yokota - Starter Code
**				YOUR NAME HERE
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This should not affect Image, and should allocate space for a new Color.
Color *evaluateOnePixel(Image *image, int row, int col)
{
	Color* pixel = malloc(sizeof(Color));
	if(pixel == NULL){
		return NULL;
	}
	if(((image->image[row * image->cols + col]->B) & (0b00000001)) == 0){
		pixel->R = 0;
		pixel->G = 0;
		pixel->B = 0;
	}else {
		pixel->R = 255;
		pixel->G = 255;
		pixel->B = 255;
	}

	return pixel;
}

//Given an image, creates a new image extracting the LSB of the B channel.
Image *steganography(Image *image)
{
	Image* new_image = malloc(sizeof(Image));
	new_image->rows = image->rows;
	new_image->cols = image->cols;
	new_image->image = malloc(new_image->cols * new_image->rows * sizeof(Color*));
	for(int i = 0; i < new_image->rows; ++i){
		for(int j = 0; j < new_image->cols; ++j){
			new_image->image[i*new_image->cols + j] = evaluateOnePixel(image, i, j);
		}
	}

	return new_image;
}

/*
Loads a file of ppm P3 format from a file, and prints to stdout (e.g. with printf) a new image, 
where each pixel is black if the LSB of the B channel is 0, 
and white if the LSB of the B channel is 1.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a file of ppm P3 format (not necessarily with .ppm file extension).
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!
*/
int main(int argc, char **argv)
{
	if(argc != 2){
		return -1;
	}
	char* filename = argv[1];

	Image* image = readData(filename);
	if(image == NULL){
		return -1;
	}
	Image* new_image = steganography(image);
	if(new_image == NULL){
		freeImage(image);
		return -1;
	}
	writeData(new_image);

	freeImage(image);
	freeImage(new_image);

	return 0;
}

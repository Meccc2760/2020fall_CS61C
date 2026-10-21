/************************************************************************
**
** NAME:        gameoflife.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-23
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "imageloader.h"

//Determines what color the cell at the given row/col should be. This function allocates space for a new Color.
//Note that you will need to read the eight neighbors of the cell in question. The grid "wraps", so we treat the top row as adjacent to the bottom row
//and the left column as adjacent to the right column.
Color *evaluateOneCell(Image *image, int row, int col, uint32_t rule)
{
	Color* pixel = calloc(1, sizeof(Color));
	if (pixel == NULL){
		return NULL;
	}

	Color* curr = image->image[row * image->cols + col];
	for (int b = 0; b < 8; ++b){
		int alive = (curr->R >> b) & 1;
	    int neighbours = 0;
		for (int i = -1; i < 2; ++i){
			for (int j = -1; j < 2; ++j){
				if (i == 0 && j == 0){
					continue;
				}

				int nr = (row + i + image->rows) % image->rows;
        		int nc = (col + j + image->cols) % image->cols;
				Color* neighbor = image->image[nr * image->cols + nc];
        		neighbours += (neighbor->R >> b) & 1;
			}
		}
		int index = alive ? 9 + neighbours : neighbours;
		int next = (rule >> index) & 1;

		if(next){
			pixel->R |= (1u << b);
		}
	}

	for (int b = 0; b < 8; ++b){
		int alive = (curr->G >> b) & 1;
	    int neighbours = 0;
		for (int i = -1; i < 2; ++i){
			for (int j = -1; j < 2; ++j){
				if (i == 0 && j == 0){
					continue;
				}

				int nr = (row + i + image->rows) % image->rows;
        		int nc = (col + j + image->cols) % image->cols;
				Color* neighbor = image->image[nr * image->cols + nc];
        		neighbours += (neighbor->G >> b) & 1;
			}
		}
		int index = alive ? 9 + neighbours : neighbours;
		int next = (rule >> index) & 1;

		if(next){
			pixel->G |= (1u << b);
		}
	}

	for (int b = 0; b < 8; ++b){
		int alive = (curr->B >> b) & 1;
	    int neighbours = 0;
		for (int i = -1; i < 2; ++i){
			for (int j = -1; j < 2; ++j){
				if (i == 0 && j == 0){
					continue;
				}

				int nr = (row + i + image->rows) % image->rows;
        		int nc = (col + j + image->cols) % image->cols;
				Color* neighbor = image->image[nr * image->cols + nc];
        		neighbours += (neighbor->B >> b) & 1;
			}
		}
		int index = alive ? 9 + neighbours : neighbours;
		int next = (rule >> index) & 1;

		if(next){
			pixel->B |= (1u << b);
		}
	}

	return pixel;
}

//The main body of Life; given an image and a rule, computes one iteration of the Game of Life.
//You should be able to copy most of this from steganography.c
Image *life(Image *image, uint32_t rule)
{
	Image* new_image = malloc(sizeof(Image));
	if(new_image == NULL){
        return NULL;
    }
	new_image->rows = image->rows;
	new_image->cols = image->cols;
	new_image->image = malloc(new_image->cols * new_image->rows * sizeof(Color*));
	if(new_image->image == NULL){
        free(new_image);
        return NULL;
    }
	for(int i = 0; i < new_image->rows; ++i){
		for(int j = 0; j < new_image->cols; ++j){
			Color* pixel = evaluateOneCell(image, i, j, rule);
            if(pixel == NULL){
                freeImage(new_image);
                return NULL;
            }
            new_image->image[i * new_image->cols + j] = pixel;}
	}

	return new_image;
}

/*
Loads a .ppm from a file, computes the next iteration of the game of life, then prints to stdout the new image.

argc stores the number of arguments.
argv stores a list of arguments. Here is the expected input:
argv[0] will store the name of the program (this happens automatically).
argv[1] should contain a filename, containing a .ppm.
argv[2] should contain a hexadecimal number (such as 0x1808). Note that this will be a string.
You may find the function strtol useful for this conversion.
If the input is not correct, a malloc fails, or any other error occurs, you should exit with code -1.
Otherwise, you should return from main with code 0.
Make sure to free all memory before returning!

You may find it useful to copy the code from steganography.c, to start.
*/
int main(int argc, char **argv)
{	
	if(argc != 3){
		return -1;
	}
	char* filename = argv[1];
	uint32_t rule = (uint32_t)strtoul(argv[2], NULL, 0);

	Image* image = readData(filename);
	if(image == NULL){
		return -1;
	}
	Image* new_image = life(image, rule);
	if(new_image == NULL){
		freeImage(image);
		return -1;
	}
	writeData(new_image);

	freeImage(image);
	freeImage(new_image);

	return 0;
}

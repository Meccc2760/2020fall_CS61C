/************************************************************************
**
** NAME:        imageloader.c
**
** DESCRIPTION: CS61C Fall 2020 Project 1
**
** AUTHOR:      Dan Garcia  -  University of California at Berkeley
**              Copyright (C) Dan Garcia, 2020. All rights reserved.
**              Justin Yokota - Starter Code
**				YOUR NAME HERE
**
**
** DATE:        2020-08-15
**
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include "imageloader.h"

//Opens a .ppm P3 image file, and constructs an Image object. 
//You may find the function fscanf useful.
//Make sure that you close the file with fclose before returning.
Image *readData(char *filename) 
{
	FILE *fp = fopen(filename, "r");
	if (fp == NULL){
		return NULL;
	}

	char format[3];
	unsigned int cols, rows, scale;
	fscanf(fp, "%2s", format);
	fscanf(fp, "%u %u", &cols, &rows);
	fscanf(fp, "%u", &scale);

	Image* image = malloc(sizeof(Image));
	if(image == NULL){
		fclose(fp);
		return NULL;
	}
	image->cols = cols;
	image->rows = rows;
	image->image = calloc(image->cols * image->rows, sizeof(Color *));
	if(image->image == NULL){
		fclose(fp);
		free(image);
		return NULL;
	}
	for (int i = 0; i < image->rows; ++i){
		for (int j = 0; j < image->cols; ++j){
			Color* pixel = malloc(sizeof(Color));
			if(pixel == NULL){
				fclose(fp);
				freeImage(image);
				return NULL;
			}
			unsigned int r, g, b;
			fscanf(fp, "%u %u %u", &r, &g, &b);
			pixel->R = (uint8_t)r;
			pixel->G = (uint8_t)g;
			pixel->B = (uint8_t)b;
			image->image[i * image->cols + j] = pixel;
		}
	}

	fclose(fp);
	return image;
}

//Given an image, prints to stdout (e.g. with printf) a .ppm P3 file with the image's data.
void writeData(Image *image)
{
	printf("P3\n%u %u\n255\n", image->cols, image->rows);

    for (int i = 0; i < image->rows; ++i){
        for (int j = 0; j < image->cols; ++j){
            Color* pixel = image->image[i * image->cols + j];

            if (j > 0){
                printf("   ");
            }
            printf("%3d %3d %3d", pixel->R, pixel->G, pixel->B);
        }
        printf("\n");
    }
}

//Frees an image
void freeImage(Image *image)
{	
	if(image == NULL){
		return;
	}

	for (int i = 0; i < image->rows; ++i){
		for (int j = 0; j < image->cols; ++j){
			free(image->image[i * image->cols + j]);
		}
	}
	free(image->image);
	free(image);
}
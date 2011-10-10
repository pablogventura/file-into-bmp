/*
This source file is part of f2bmp.  This code was
written by Pablo Ventura in 2011, and is covered by the GPL.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

typedef struct spixel * pixel;

typedef struct sbmp_file * bmp_file;

bmp_file open_bmp(char * path);

int32_t width_bmp(bmp_file me);

int32_t height_bmp(bmp_file me);

pixel get_pixel(bmp_file me, int x, int y);

pixel get_i_pixel(bmp_file me, unsigned int i);

unsigned char red_pixel(pixel me);

unsigned char green_pixel(pixel me);

unsigned char blue_pixel(pixel me);

void set_red_pixel(pixel me, unsigned char value);

void set_green_pixel(pixel me, unsigned char value);

void set_blue_pixel(pixel me, unsigned char value);

void save_bmp(bmp_file me, char * path);

bmp_file close_bmp(bmp_file me);

/*
This source file is part of f2bmp.  This code was
written by Pablo Ventura in 2011, and is covered by the GPL.
 */

#include "simplebmp.h"

struct sbmp_file{
  uint32_t header_sz;
  int32_t width;
  int32_t height;
  uint16_t nplanes;
  uint16_t bitspp;
  uint32_t compress_type;
  uint32_t bmp_bytesz;
  int32_t hres;
  int32_t vres;
  uint32_t ncolors;
  uint32_t nimpcolors;
  FILE * f_bmp;
  pixel * bitmap;
  unsigned char headers[54];
  unsigned char * buffer;
  unsigned char * endoffile;
};

struct spixel{
  unsigned char * red;
  unsigned char * green;
  unsigned char * blue;
};

bmp_file open_bmp(char * path){
	bmp_file result;

	int x = 0;
	int y = 0;
	
	result = ((bmp_file) malloc (sizeof (struct sbmp_file)));
	
	result->f_bmp = fopen(path, "r");
	fread(result->headers, sizeof (unsigned char), 54, result->f_bmp);
	
	result->width = *(int32_t *) &result->headers[18];
	result->height = *(int32_t *) &result->headers[22];

	result->buffer = calloc (result->width * result->height * 3, sizeof (unsigned char));
	fread(result->buffer, sizeof (unsigned char), result->width * result->height * 3, result->f_bmp);
	
	result->bitmap = calloc (result->width * result->height, sizeof (pixel));
	
	
	while (x < result->width){
		while (y < result->height){
			result->bitmap[(y * result->width) + x] = ((pixel) malloc (sizeof (struct spixel)));
			result->bitmap[(y * result->width) + x]->blue = &result->buffer[((y * (result->width+1)) + x) * 3];
			result->bitmap[(y * result->width) + x]->green = &result->buffer[(((y * (result->width+1)) + x) * 3) + 1];
			result->bitmap[(y * result->width) + x]->red = &result->buffer[(((y * (result->width+1)) + x) * 3) + 2];
			y++;
		}
		y=0;
		x++;
	}
	return result;
}

int32_t width_bmp(bmp_file me){

	return (me->width);
	
}

int32_t height_bmp(bmp_file me){

	return (me->height);
	
}

pixel get_pixel(bmp_file me, int x, int y){
	
	return me->bitmap[(y * me->width) + x];
	
}

pixel get_i_pixel(bmp_file me, unsigned int i){
	
	return me->bitmap[i];
	
}

unsigned char red_pixel(pixel me){
	
	return *(me->red);
	
}

unsigned char green_pixel(pixel me){
	
	return *(me->green);
	
}

unsigned char blue_pixel(pixel me){
	
	return *(me->blue);
	
}

void set_red_pixel(pixel me, unsigned char value){
	
	*me->red = value;
	
}

void set_green_pixel(pixel me, unsigned char value){
	
	*me->green = value;
	
}

void set_blue_pixel(pixel me, unsigned char value){
	
	*me->blue = value;
	
}

void save_bmp(bmp_file me, char * path){
	FILE * save_file;
	save_file = fopen(path, "w");
	
	fwrite (me->headers, sizeof (unsigned char), 54, save_file);
	fwrite (me->buffer, sizeof (unsigned char), me->width * me->height * 3, save_file);
	fclose(save_file);
}

bmp_file close_bmp(bmp_file me){
	fclose(me->f_bmp);
	free(me);
	return NULL;
}

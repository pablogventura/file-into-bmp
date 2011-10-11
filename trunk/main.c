/*
This source file is part of f2bmp.  This code was
written by Pablo Ventura in 2011, and is covered by the GPL.
 */


#include <stdbool.h>
#include <string.h>
#include "simplebmp.h"
unsigned char read(pixel me);
void write (pixel me, unsigned char value);
unsigned char generate_remainder(unsigned char number, unsigned char divisor, unsigned char remainder);
void read_file_in_bmp(bmp_file me, char * path);
void write_file_in_bmp(bmp_file me, char * path);

int main(int argc, char *argv[]){
	bool read = true;
	bmp_file archivo;
	if (argc == 1){
		printf("\nF2Bmp\n"
		       "This program encrypt a binary file into an image either BMP without this having a noticeable change in their colors.\n"
		       "Usage:\n"
		       "f2bmp -r [bmp to read] [file to write]\n"
		       "f2bmp -w [original bmp] [file to encrypt] [new bmp]\n\n");
	}else{
		if (strcmp(argv[1], "-w")==0){
			read = false;
		}
		if (read == true){
			archivo = open_bmp(argv[2]);

			read_file_in_bmp(archivo, argv[3]);
	
			archivo = close_bmp(archivo);
		}else{
			archivo = open_bmp(argv[2]);
			printf("\nMax size supported by this image: %i Kb",
				width_bmp(archivo) * height_bmp(archivo) / 1024);
			write_file_in_bmp(archivo, argv[3]);
	
			save_bmp(archivo, argv[4]);
	
			archivo = close_bmp(archivo);
		}
	}
	return 0;
}

void write_file_in_bmp(bmp_file me, char * path){
	FILE * from_file;
	unsigned char buffer[1];
	unsigned int i = 4;
	unsigned int j = 0;
	unsigned char c_size[4];
	int32_t * size = (int32_t *) &c_size[0];
	from_file = fopen(path, "r");
	
	
	while (fread(buffer, sizeof (unsigned char), 1, from_file) != 0){
		write (get_i_pixel(me, i), buffer[0]);
		j++;
		i++;
	}
	write (get_i_pixel(me, i), buffer[0]);
	j++;
	i++;
		
	*size = i - 5;
	write (get_i_pixel(me, 0), c_size[0]);
	write (get_i_pixel(me, 1), c_size[1]);
	write (get_i_pixel(me, 2), c_size[2]);
	write (get_i_pixel(me, 3), c_size[3]);
}
	
void read_file_in_bmp(bmp_file me, char * path){
	FILE * to_file;
	unsigned char * buffer;
	unsigned int i = 4;
	unsigned int j = 0;
	unsigned char c_size[4];
	int32_t * size = (int32_t *) &c_size[0];
	to_file = fopen(path, "w");
	
	c_size[0] = read(get_i_pixel(me, 0));
	c_size[1] = read(get_i_pixel(me, 1));
	c_size[2] = read(get_i_pixel(me, 2));
	c_size[3] = read(get_i_pixel(me, 3));
	
	buffer = calloc (*size, sizeof (unsigned char));
	
	while (j<*size){
		buffer[j] = read (get_i_pixel(me, i));
		j++;
		i++;
	}
	fwrite(buffer, sizeof (unsigned char), *size, to_file);
	
}

void write (pixel me, unsigned char value){
	
	unsigned char t1 = value & 0x07; /*0x07 = 0b00000111*/
	unsigned char t2 = (value & 0x38)>>3; /*0x38 = 0b00111000*/
	unsigned char t3 = (value & 0xC0)>>6; /*0xC0= 0b11000000*/
	
	set_red_pixel(me, generate_remainder(red_pixel(me), 8, t1));
	set_green_pixel(me, generate_remainder(green_pixel(me), 8, t2));
	set_blue_pixel(me, generate_remainder(blue_pixel(me), 4, t3));
}

unsigned char read(pixel me){
	unsigned char result = 0;
		
	unsigned char t1 = (red_pixel(me) % 8) & 0x07; /*0x07 = 0b00000111*/
	unsigned char t2 = (((green_pixel(me) % 8)<<3) & 0x38); /*0x38 = 0b00111000*/
	unsigned char t3 = (((blue_pixel(me) % 4)<<6) & 0xC0); /*0xC0= 0b11000000*/
	
	result = t1 | t2 | t3;
	
	return result;
	
}

unsigned char generate_remainder(unsigned char number, unsigned char divisor, unsigned char remainder){
	unsigned int diference = (number % divisor) - remainder;
	/*esta funcion hay que mejorarla mucho*/
	while (number % divisor != remainder){
		
		diference = (number % divisor) - remainder;
		
		if ((int)number + diference <= 255 && (int)number + diference >= 0){
			number = number + diference;
		}else if ((int)number - diference <= 255 && (int)number - diference >= 0){
			number = number - diference;
		}
	}
	
	return number;
}

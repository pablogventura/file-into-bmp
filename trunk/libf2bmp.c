/*
This source file is part of f2bmp.  This code was
written by Pablo Ventura in 2011, and is covered by the GPL.
 */

#include "libf2bmp.h" 

void write_file_in_bmp(char * bmp_path, char * path, char * new_bmp_path){
	FILE * from_file;
	bmp_file bmp;
	unsigned char buffer[1];
	unsigned int i = 4;
	unsigned int j = 0;
	unsigned char c_size[4];
	int32_t * size = (int32_t *) &c_size[0];

	bmp = open_bmp(bmp_path);
	from_file = fopen(path, "r");
	
	
	while (fread(buffer, sizeof (unsigned char), 1, from_file) != 0){
		write (get_i_pixel(bmp, i), buffer[0]);
		j++;
		i++;
	}
	write (get_i_pixel(bmp, i), buffer[0]);
	j++;
	i++;
		
	*size = i - 5;
	write (get_i_pixel(bmp, 0), c_size[0]);
	write (get_i_pixel(bmp, 1), c_size[1]);
	write (get_i_pixel(bmp, 2), c_size[2]);
	write (get_i_pixel(bmp, 3), c_size[3]);
	
	save_bmp(bmp, new_bmp_path);
	
	bmp = close_bmp(bmp);
}
	
void read_file_in_bmp(char * bmp_path, char * path){


	FILE * to_file;
	bmp_file bmp;
	unsigned char * buffer;
	unsigned int i = 4;
	unsigned int j = 0;
	unsigned char c_size[4];
	int32_t * size = (int32_t *) &c_size[0];
	
	bmp = open_bmp(bmp_path);
	to_file = fopen(path, "w");
	
	c_size[0] = read(get_i_pixel(bmp, 0));
	c_size[1] = read(get_i_pixel(bmp, 1));
	c_size[2] = read(get_i_pixel(bmp, 2));
	c_size[3] = read(get_i_pixel(bmp, 3));
	
	buffer = calloc (*size, sizeof (unsigned char));
	
	while (j<*size){
		buffer[j] = read (get_i_pixel(bmp, i));
		j++;
		i++;
	}
	fwrite(buffer, sizeof (unsigned char), *size, to_file);


	
	bmp = close_bmp(bmp);

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

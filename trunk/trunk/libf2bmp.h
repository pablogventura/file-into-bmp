/*
This source file is part of f2bmp.  This code was
written by Pablo Ventura in 2011, and is covered by the GPL.
 */


#include "simplebmp.h"

unsigned char read(pixel me);

void write (pixel me, unsigned char value);

unsigned char generate_remainder(unsigned char number, unsigned char divisor, unsigned char remainder);

void read_file_in_bmp(char * bmp_path, char * path);

void write_file_in_bmp(char * bmp_path, char * path, char * new_bmp_path);

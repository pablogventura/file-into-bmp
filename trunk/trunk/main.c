/*
This source file is part of f2bmp.  This code was
written by Pablo Ventura in 2011, and is covered by the GPL.
 */


#include <stdbool.h>
#include <string.h>
#include "libf2bmp.h"

int main(int argc, char *argv[]){

	bool read = true;
	bool to_stdout = false;
	
	if (argc == 1){
		printf("\nF2Bmp\n"
		       "This program encrypts a binary file into an image either BMP\n"
		       "without this having a noticeable change in their colors.\n"
		       "Usage:\n"
			   "\tf2bmp -w [original bmp] [file to encrypt] [new bmp]\n"
			   "\tf2bmp -r [bmp to read] [file to write]\n"
			   "\tf2bmp -rs [bmp to read]\n\n");
	}else{
		if (strcmp(argv[1], "-w")==0){
			read = false;
		} else if (strcmp(argv[1], "-rs")==0){
			read = true;
			to_stdout = true;
		}
		if (read == true){
			if (to_stdout == true){
				read_file_in_bmp_to_stdout(argv[2]);
			}else{
				read_file_in_bmp(argv[2], argv[3]);
			}
			
		}else{
		
			write_file_in_bmp(argv[2], argv[3], argv[4]);
			
		}
	}
	return 0;
}


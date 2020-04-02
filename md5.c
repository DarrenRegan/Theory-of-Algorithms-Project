#include <stdio.h>
#include <inttypes.h>

int main(int argc, char *argv[]){
	if(argc != 2){
		printf("Error: expected single filename as arugment. \n");
		return 1;
	}

	FILE *infile = fopen(argv[1], "rb");
	if(!infile){
		printf("Error: couldn't open file %s. \n", argv[1]);
		return 1;
	}

	uint8_t b;
	//Reads 1 bit, 1 copy of 1 bit from infile
	for(;fread(&b, 1, 1, infile) == 1;){
		printf("%02x ", b);
	}
	printf("\n");
	fclose(infile);
	
	return 0;
}

// Darren Regan
// Padding for SHA256
//
#include <stdio.h>
#include <inttypes.h>

uint64_t nozerobytes(uint64_t nobits){

	uint64_t result = 512ULL - (nobits % 512ULL);

	if (result < 65)
		result += 512;
	result -= 72;

	// Tell num of bytes, of zeros needed to output inbetween the one bit and the 64 bit integer that prints at end
	return (result / 8ULL);
}



int main(int argc, char *argv[]){

	if (argc != 2) {
		printf("Error: expected single filename as arugment.\n");
		return 1;
	}

	FILE *infile = fopen(argv[1], "rb");
	if (!infile) {
		printf("Error: couldn't open file %s. \n", argv[1]);
		return 1;
	}	

	uint8_t b;
	uint64_t nobits;

	//Reads 1 bit, 1 copy of 1 bit from infile
	for (nobits = 0; fread(&b, 1, 1, infile) == 1; nobits += 8){
		printf("%02" PRIx8 " ", b);
	}

	printf("%02" PRIx8 " ", 0x80); // Bits: 1000 0000

	for (uint64_t i = nozerobytes(nobits); i > 0; i--)
		printf("%02" PRIx8 " ", 0x00);

	printf("%016" PRIx64 "\n", nobits);

	fclose(infile);
	return 0;
}

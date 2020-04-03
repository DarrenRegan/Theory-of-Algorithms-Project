// Darren Regan - G00326934
// MD5 Implementation Project
// https://tools.ietf.org/html/rfc1321
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <string.h>

//Page 9
#define S11 7
#define S12 12
#define S13 17
#define S14 22
#define S21 5
#define S22 9
#define S23 14
#define S24 20
#define S31 4
#define S32 11
#define S33 16
#define S34 23
#define S41 6
#define S42 10
#define S43 15
#define S44 21
/* ROTATE_LEFT rotates x left n bits.*/
#define ROTATE_LEFT(x, n) (((x) << (n)) | ((x) >> (32-(n))))

const uint32_t T[64] = {
        0xd76aa478, 0xe8c7b756, 0x242070db, 0xc1bdceee,
        0xf57c0faf, 0x4787c62a, 0xa8304613, 0xfd469501,
        0x698098d8, 0x8b44f7af, 0xffff5bb1, 0x895cd7be,
        0x6b901122, 0xfd987193, 0xa679438e, 0x49b40821,
        0xf61e2562, 0xc040b340, 0x265e5a51, 0xe9b6c7aa,
        0xd62f105d, 0x02441453, 0xd8a1e681, 0xe7d3fbc8,
        0x21e1cde6, 0xc33707d6, 0xf4d50d87, 0x455a14ed,
        0xa9e3e905, 0xfcefa3f8, 0x676f02d9, 0x8d2a4c8a,
        0xfffa3942, 0x8771f681, 0x6d9d6122, 0xfde5380c,
        0xa4beea44, 0x4bdecfa9, 0xf6bb4b60, 0xbebfbc70,
        0x289b7ec6, 0xeaa127fa, 0xd4ef3085, 0x04881d05,
        0xd9d4d039, 0xe6db99e5, 0x1fa27cf8, 0xc4ac5665,
        0xf4292244, 0x432aff97, 0xab9423a7, 0xfc93a039,
        0x655b59c3, 0x8f0ccc92, 0xffeff47d, 0x85845dd1,
        0x6fa87e4f, 0xfe2ce6e0, 0xa3014314, 0x4e0811a1,
        0xf7537e82, 0xbd3af235, 0x2ad7d2bb, 0xeb86d391};

// Initialize MD Buffer - Section 3.3
uint32_t A = 0x67452301;
uint32_t B = 0xefcdab89;
uint32_t C = 0x98badcfe;
uint32_t D = 0x10325476;

// FGHI - Process Message in 16-Word Blocks - Section 3.4
uint32_t F(uint32_t x, uint32_t y, uint32_t z){
	return (x & y) | ((~x) & z);
}

uint32_t G(uint32_t x, uint32_t y, uint32_t z){
	return (x & z) | (y & (~z));
}

uint32_t H(uint32_t x, uint32_t y, uint32_t z){
	return x ^ y ^ z;
}

uint32_t I(uint32_t x, uint32_t y, uint32_t z){
	return y ^ (x | (~z));
}

enum flag {
	READ, PAD0, PAD1, FINISH
};

union block {
	uint64_t sixfour[8];
	uint32_t threetwo[16];
	uint8_t eight[64];
};

uint64_t nozerobytes(uint64_t nobits){

	uint64_t result = 512ULL - (nobits % 512ULL);

	if(result < 65)
		result += 512;
	
	result -= 72;

	// Tell num of bytes, of zeros needed to output inbetween the one bit and the 64 bit integer that prints at end
	return (result / 8ULL);
}


int nextblock(union block *M, FILE *infile, uint64_t *nobits, enum flag *status){
	uint8_t i;

	for (nobits = 0, i = 0; fread(&M->eight[i], 1, 1, infile) == 1; *nobits += 8){
		printf("%02 ", PRIx8, M->eight[i]);
	}

	printf("%02 ", PRIx8, 0x80); // Bits: 1000 0000
	for (uint64_t i = nozerobytes(*nobits); i > 0; i --){
		printf("02 ", PRIx8, 0x00);
	}
	printf("%016 ", PRIx64, *nobits);
}

void nexthash(union block *M, uint32_t *H){
}



int main(int argc, char *argv[]){

/*	uint32_t x = 0x0f0f0f0f;
	uint32_t y = 0xcccccccc;
        uint32_t z = 0x55555555;

	printf("x        = %08x\n", x);
   	printf("y        = %08x\n", y);
  	printf("z        = %08x\n", z);

	printf("F(x,y,z) = %08x\n", F(x, y, z));
	printf("G(x,y,z) = %08x\n", G(x, y, z));
	printf("H(x,y,z) = %08x\n", H(x, y, z));
	printf("I(x,y,z) = %08x\n", I(x, y, z));
*/

	if(argc != 2){
		printf("Error: expected single filename as arugment. \n");
		return 1;
	}

	FILE *infile = fopen(argv[1], "rb");
	if(!infile){
		printf("Error: couldn't open file %s. \n", argv[1]);
		return 1;
	}

	uint32_t H[] = {A, B, C, D};
	uint8_t i;
	union block M;
	uint64_t nobits = 0;
	enum flag status = READ;

	
	// Read through all of the padded message blocks.
	while (nextblock(&M.eight, infile)){
		// Calculate the next hash value.
		nexthash(&M, &H);
	}

	for (int i = 0; i < 8; i++){
		printf("%02",o PRIX32, H[i]);
	}

	printf("/n");
	fclose(infile);
	
	return 0;
}

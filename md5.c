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
/* ROTATE_LEFT rotates x left c bits.*/
#define ROTATE_LEFT(x, c) (((x) << (c)) | ((x) >> (32-(c))))

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

//Page 10&11 of md5 memo
void FF(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, uint32_t k, uint32_t s, uint32_t ac) {
    u_int32_t sum = (*a + F(b, c, d) + k + ac);
    uint32_t f = F(b, c, d);
    // printf("rotateLeft(%x + %x + %x + %x, %d)\n", *a, f, ac, k, s);
    *a = b + LEFTROTATE(sum, s);
}

void GG(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
    u_int32_t sum = (*a + G(b, c, d) + x + ac);//(a) += F ((b), (c), (d)) + (x) + (UINT4)(ac);
    uint32_t g = G(b, c, d);
    //printf("rotateLeft(%x + %x + %x + %x, %d)\n", *a, g, ac, x, s);
    *a = b + LEFTROTATE(sum, s);//(a) = ROTATE_LEFT ((a), (s));
}

void HH(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
    u_int32_t sum = (*a + H(b, c, d) + x + ac);
    uint32_t h = H(b, c, d);
    // printf("rotateLeft(%x + %x + %x + %x, %d)\n", *a, h, ac, x, s);
    *a = b + LEFTROTATE(sum, s);
}

void II(uint32_t *a, uint32_t b, uint32_t c, uint32_t d, uint32_t x, uint32_t s, uint32_t ac) {
    u_int32_t sum = (*a + I(b, c, d) + x + ac);
    uint32_t i = I(b, c, d);
    // printf("rotateLeft(%x + %x + %x + %x, %d)\n", *a, i, ac, x, s);
    *a = b + LEFTROTATE(sum, s);
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
	//Pg 11,12,13 md5 memo
	uint32_t copyH[4];
	copyH[0] = H[0];
	copyH[1] = H[1];
	copyH[2] = H[2];
	copyH[3] = H[3];

	/* Round 1 */
	FF(&H[0], H[1], H[2], H[3], M->threetwo[0], S11, 0xd76aa478);  /* 1 */
    	FF(&H[3], H[0], H[1], H[2], M->threetwo[1], S12, 0xe8c7b756);  /* 2 */
    	FF(&H[2], H[3], H[0], H[1], M->threetwo[2], S13, 0x242070db);  /* 3 */
    	FF(&H[1], H[2], H[3], H[0], M->threetwo[3], S14, 0xc1bdceee);  /* 4 */
    	FF(&H[0], H[1], H[2], H[3], M->threetwo[4], S11, 0xf57c0faf);  /* 5 */
    	FF(&H[3], H[0], H[1], H[2], M->threetwo[5], S12, 0x4787c62a);  /* 6 */
    	FF(&H[2], H[3], H[0], H[1], M->threetwo[6], S13, 0xa8304613);  /* 7 */
   	FF(&H[1], H[2], H[3], H[0], M->threetwo[7], S14, 0xfd469501);  /* 8 */
    	FF(&H[0], H[1], H[2], H[3], M->threetwo[8], S11, 0x698098d8);  /* 9 */
    	FF(&H[3], H[0], H[1], H[2], M->threetwo[9], S12, 0x8b44f7af);  /* 10 */
    	FF(&H[2], H[3], H[0], H[1], M->threetwo[10], S13, 0xffff5bb1); /* 11 */
    	FF(&H[1], H[2], H[3], H[0], M->threetwo[11], S14, 0x895cd7be); /* 12 */
    	FF(&H[0], H[1], H[2], H[3], M->threetwo[12], S11, 0x6b901122); /* 13 */
    	FF(&H[3], H[0], H[1], H[2], M->threetwo[13], S12, 0xfd987193); /* 14 */
    	FF(&H[2], H[3], H[0], H[1], M->threetwo[14], S13, 0xa679438e); /* 15 */
    	FF(&H[1], H[2], H[3], H[0], M->threetwo[15], S14, 0x49b40821); /* 16 */
   	printf("\n");

	/* Round 2 */
   	GG(&H[0], H[1], H[2], H[3], M->threetwo[1], S21, 0xf61e2562);  /* 17 */
    	GG(&H[3], H[0], H[1], H[2], M->threetwo[6], S22, 0xc040b340);  /* 18 */
   	GG(&H[2], H[3], H[0], H[1], M->threetwo[11], S23, 0x265e5a51); /* 19 */
     	GG(&H[1], H[2], H[3], H[0], M->threetwo[0], S24, 0xe9b6c7aa);  /* 20 */
   	GG(&H[0], H[1], H[2], H[3], M->threetwo[5], S21, 0xd62f105d);  /* 21 */
    	GG(&H[3], H[0], H[1], H[2], M->threetwo[10], S22, 0x2441453);  /* 22 */
    	GG(&H[2], H[3], H[0], H[1], M->threetwo[15], S23, 0xd8a1e681); /* 23 */
    	GG(&H[1], H[2], H[3], H[0], M->threetwo[4], S24, 0xe7d3fbc8);  /* 24 */
    	GG(&H[0], H[1], H[2], H[3], M->threetwo[9], S21, 0x21e1cde6);  /* 25 */
   	GG(&H[3], H[0], H[1], H[2], M->threetwo[14], S22, 0xc33707d6); /* 26 */
    	GG(&H[2], H[3], H[0], H[1], M->threetwo[3], S23, 0xf4d50d87);  /* 27 */
    	GG(&H[1], H[2], H[3], H[0], M->threetwo[8], S24, 0x455a14ed);  /* 28 */
    	GG(&H[0], H[1], H[2], H[3], M->threetwo[13], S21, 0xa9e3e905); /* 29 */
    	GG(&H[3], H[0], H[1], H[2], M->threetwo[2], S22, 0xfcefa3f8); /* 30 */
    	GG(&H[2], H[3], H[0], H[1], M->threetwo[7], S23, 0x676f02d9); /* 31 */
    	GG(&H[1], H[2], H[3], H[0], M->threetwo[12], S24, 0x8d2a4c8a); /* 32 */
    	printf("\n");

    	/* Round 3 */
   	HH(&H[0], H[1], H[2], H[3], M->threetwo[5], S31, 0xfffa3942); /* 33 */
    	HH(&H[3], H[0], H[1], H[2], M->threetwo[8], S32, 0x8771f681); /* 34 */
    	HH(&H[2], H[3], H[0], H[1], M->threetwo[11], S33, 0x6d9d6122); /* 35 */
    	HH(&H[1], H[2], H[3], H[0], M->threetwo[14], S34, 0xfde5380c); /* 36 */
    	HH(&H[0], H[1], H[2], H[3], M->threetwo[1], S31, 0xa4beea44); /* 37 */
    	HH(&H[3], H[0], H[1], H[2], M->threetwo[4], S32, 0x4bdecfa9); /* 38 */
    	HH(&H[2], H[3], H[0], H[1], M->threetwo[7], S33, 0xf6bb4b60); /* 39 */
    	HH(&H[1], H[2], H[3], H[0], M->threetwo[10], S34, 0xbebfbc70); /* 40 */
    	HH(&H[0], H[1], H[2], H[3], M->threetwo[13], S31, 0x289b7ec6); /* 41 */
    	HH(&H[3], H[0], H[1], H[2], M->threetwo[0], S32, 0xeaa127fa); /* 42 */
    	HH(&H[2], H[3], H[0], H[1], M->threetwo[3], S33, 0xd4ef3085); /* 43 */
    	HH(&H[1], H[2], H[3], H[0], M->threetwo[6], S34, 0x4881d05); /* 44 */
    	HH(&H[0], H[1], H[2], H[3], M->threetwo[9], S31, 0xd9d4d039); /* 45 */
    	HH(&H[3], H[0], H[1], H[2], M->threetwo[12], S32, 0xe6db99e5); /* 46 */
   	HH(&H[2], H[3], H[0], H[1], M->threetwo[15], S33, 0x1fa27cf8); /* 47 */
    	HH(&H[1], H[2], H[3], H[0], M->threetwo[2], S34, 0xc4ac5665); /* 48 */
    	printf("\n");

    	/* Round 4 */
    	II(&H[0], H[1], H[2], H[3], M->threetwo[0], S41, 0xf4292244); /* 49 */
    	II(&H[3], H[0], H[1], H[2], M->threetwo[7], S42, 0x432aff97); /* 50 */
    	II(&H[2], H[3], H[0], H[1], M->threetwo[14], S43, 0xab9423a7); /* 51 */
    	II(&H[1], H[2], H[3], H[0], M->threetwo[5], S44, 0xfc93a039); /* 52 */
    	II(&H[0], H[1], H[2], H[3], M->threetwo[12], S41, 0x655b59c3); /* 53 */
   	II(&H[3], H[0], H[1], H[2], M->threetwo[3], S42, 0x8f0ccc92); /* 54 */
    	II(&H[2], H[3], H[0], H[1], M->threetwo[10], S43, 0xffeff47d); /* 55 */
    	II(&H[1], H[2], H[3], H[0], M->threetwo[1], S44, 0x85845dd1); /* 56 */
    	II(&H[0], H[1], H[2], H[3], M->threetwo[8], S41, 0x6fa87e4f); /* 57 */
    	II(&H[3], H[0], H[1], H[2], M->threetwo[15], S42, 0xfe2ce6e0); /* 58 */
    	II(&H[2], H[3], H[0], H[1], M->threetwo[6], S43, 0xa3014314); /* 59 */
    	II(&H[1], H[2], H[3], H[0], M->threetwo[13], S44, 0x4e0811a1); /* 60 */
    	II(&H[0], H[1], H[2], H[3], M->threetwo[4], S41, 0xf7537e82); /* 61 */
    	II(&H[3], H[0], H[1], H[2], M->threetwo[11], S42, 0xbd3af235); /* 62 */
    	II(&H[2], H[3], H[0], H[1], M->threetwo[2], S43, 0x2ad7d2bb); /* 63 */
    	II(&H[1], H[2], H[3], H[0], M->threetwo[9], S44, 0xeb86d391); /* 64 */
    	printf("\n");

    	H[0] += copyH[0];
    	H[1] += copyH[1];
    	H[2] += copyH[2];
   	H[3] += copyH[3];
}//nexhhash

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

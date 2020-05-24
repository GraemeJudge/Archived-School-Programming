/* main.cpp - Client for the RLE compression/ decompression
*
*  		Copyright 2019 Graeme Judge
*		Change Log:
*  			October 30, 2019: Source file created
*/
#include "RLE.h";


void main() {

	unsigned char message[] = "AAAAAAAABCDEFG";

	unsigned char outString[140];
	unsigned char cESC = 0x1b;


	int compressedLen = 0;

	compressedLen = RLECompress(message, strlen((char*)message), outString, 140, cESC);

	printf("\nInput string : %s\nInput length : %d\n", message, strlen((char*)message));
	printf("\nOutput string : %s\nOutput length : %d\n", outString, strlen((char*)outString));
	printf("\nCompression ratio : %.2f", strlen((char*)message) / strlen((char*)outString) );


}





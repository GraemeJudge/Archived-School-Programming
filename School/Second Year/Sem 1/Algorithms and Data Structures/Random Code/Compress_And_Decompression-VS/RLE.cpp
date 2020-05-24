/* RLE.cpp -	Implementation of RLE
*
*  		Copyright 2019 Graeme Judge
*		Change Log:
*  			October 10, 1999: Source file created
*/

#pragma warning (disable : 4996)

#include "RLE.h"


int RLECompress(unsigned char* in, int inLength, unsigned char* out, int outMax, unsigned char cESC)
{
	unsigned char charc;					//repeated character
	unsigned char output[10];				//tmporary buffer

	out[0] = '\0';							//set so we can use strcat()

	int i = 0;								//counter
	int count;								//number of repeats


	while (i < inLength) {
		count = 1;							//stars count for the set
		while ((in[i] == in[i++]) && (i < inLength)) {			//while there are repeated characters
			charc = in[i];					//save the repeated character
			count++;						//adds to the count
		}

		//Encode the repeating value
		if (count >= 3) {					//Encode
			//copy to temp buffer
			sprintf((char*)output, "%c%02x%c", cESC, count, charc);
			//copy to output
			strcat((char*)out, (char*)output);	
		
		}
		else if(count == 2){				//Dont encode
			sprintf((char*)output, "%c%c", charc, charc);
			strcat((char*)out, (char*)output);
		}
		else if (count == 1) {
			output[0] = in[1];
			output[1] = '\0';
			strcat((char*)out, (char*) output);
		}
	}
	return(strlen((char*)out));
}


int RLEDecompress(unsigned char* in, int inLength, unsigned char* out, int outMax, unsigned char cESC)
{
	return 0;
}

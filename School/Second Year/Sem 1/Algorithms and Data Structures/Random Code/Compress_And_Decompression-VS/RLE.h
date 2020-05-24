/* name.Extension -	Description
*
*  		Copyright 2019 Graeme Judge
*		Change Log:
*  			October 10, 1999: Source file created
*/


#include <stdio.h>
#include <stdlib.h>
#include<string.h>

//function prototypes
int RLECompress(unsigned char* in, int inLength, unsigned char* out, int outMax, unsigned char cESC);

int RLEDecompress(unsigned char* in, int inLength, unsigned char* out, int outMax, unsigned char cESC);




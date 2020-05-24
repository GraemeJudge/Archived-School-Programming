/* Checksum.cpp : Computes checksum for 8 or 16 bits
*             By: Graeme Judge
*/

#include "Checksum.h"
#include<stdio.h>



unsigned int Checksum(void *buf, int iBufLen, CHECKSUM iType) {
	unsigned short* newBuf16;
	unsigned char* newBuf8;

	int i;
	unsigned int sum = 0, checksum = 0;
	
	
	switch (iType) {
	case CHK_16BIT:
		newBuf16 = (unsigned short*)buf; //16 bit
		
		for (i = 0; i < iBufLen; i++)
		{
			sum += *newBuf16;
			newBuf16++;
		}
		checksum = sum % 0x1000;
		return (checksum);
		break;
	case CHK_8BIT:
		newBuf8 = (unsigned char*)buf; //8 bit

		for (i = 0; i < iBufLen; i++)
		{
			sum += *newBuf8;
			newBuf8++;
		}
		checksum = sum % 0x100;
		return (checksum);
		break;
	default:
		printf("You must select 8 or 16 bit checksums \n\n");
		return(0x100000); //larger than 16 bits so signals an error
		break;	
	}
}







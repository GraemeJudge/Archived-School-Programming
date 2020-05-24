/* Parity.c -	Returns PAR_EVEN if parity is even
*				Returns PAR_ODD if parity is odd
*				Returns PAR_ERROR if error in input
*				Copyright 2019 Graeme Judge
*/


#include "Parity.h"


PARITY ParityOnBytes(char* buf, int iBufLen) {
	int iSum=0;

	for (size_t i = 0; i < iBufLen; i++, buf++)
	{
		if ((*buf) == '1') {
			//its a one
			iSum++;
		}
		else if (*buf != '0') {
				return (PAR_ERROR);
			}
		}

	if (iSum % 2 == 1) {
		return (PAR_ODD);
	}
	else {
		return(PAR_EVEN);
	}

}


PARITY Parity(unsigned char *buf, int iBufLen) {
	int iSum = 0;
	int i = 0;
	unsigned char iMask = 0x80;  //b1000 0000
	
	for (int i = 0; i < iBufLen;)
	{
		if ((*buf & iMask) != 0) {
			iSum++;
		}
		iMask >>= 1;
		if (iMask == 0) {
			iMask = 0x80;
			buf++;
			i++;
		}
	}

		if (iSum % 2 == 1) {
			return PAR_ODD;
		}
		else {
			return PAR_EVEN;
		}
} //end of parity


		

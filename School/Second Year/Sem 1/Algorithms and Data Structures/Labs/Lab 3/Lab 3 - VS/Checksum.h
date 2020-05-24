/* Checksum.cpp : Header file for lab 3
*             By: Graeme Judge
*/




//enum
enum CHECKSUM {CHK_16BIT, CHK_8BIT, CHK_ERROR};	

//function prototyes
unsigned int Checksum(void *buf, int iBufLen, CHECKSUM iType);
	
/* main.c : computes the crcSlow() of a message and appends the crc to the message. Also shows the effect of changes to the message on the computed crc
*
* Copyright Graeme Judge 2019
*/

//#pragma warning 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "crc.h"



int main(){
	//variables

	char message[] = "123456789";   //message buffer
	int mBytes = strlen(message);	// number of bytes in the message
	crc computedCRC;				//computed crc
	char computedCRCString[5];		//String representation of the computed crc
	int newMessageSize = mBytes + 8;
	char* newMessage = (char*)malloc(newMessageSize * sizeof(char));		//8 because 5 from string message crc and 3 from " 0x" 

	for (int i = 0; i <= mBytes; i++)
	{


	//test crcslow on a buffer

	computedCRC = crcSlow(message, mBytes);    //messgae and the number of bytes in the message

	sprintf_s(computedCRCString, 5,"%x", computedCRC);

	//append the computed crc to the message

	strcpy_s(newMessage, newMessageSize, message);
	strcat_s(newMessage, newMessageSize, " 0x");
	strcat_s(newMessage, newMessageSize, computedCRCString);


	printf("\n%s", newMessage);

	message[i] = '0';
	}
	//change some bits

	return 0;
}

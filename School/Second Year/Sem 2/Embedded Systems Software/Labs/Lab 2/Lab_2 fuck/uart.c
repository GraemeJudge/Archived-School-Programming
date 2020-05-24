/* uart.c-	Implementation of the uart.h file
*
*  		Copyright 20120 Graeme Judge
*		Change Log:
*  			January 23, 2020: Source file created
*/
#include "uart.h"

void uartPrintf(char *fmt, ...) {
	va_list myArgs;


	va_start(myArgs, fmt);
	vsprintf();
	va_end(myArgs, fmt);
}
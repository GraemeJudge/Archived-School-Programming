/* uart.h -	function and variabe delcaration for using the uart
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			January 23, 2020: Source file created
*				April 27, 2020: Added functionality for using virtual serial port
*/

#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>
#include "stm32l476xx.h"

#define MAX_BUFFER_SIZE 70



/*
	void uartInit;

	iitalizes the uart port by setting the needed values in the registers

	Input: None
	Output: None
*/
void uartInit(void);

/*
	void uartPrintf;

	Prints a given character buffer using the provided format

	Input: char *fmt
					Buffer including any extra fomatting 
	Output: None
*/
void uartPrintf(char *fmt, ...);

/*
	void uartPutC;

	Puts a character into the buffer being transmitted

	Input: Char c
					Character to be transmitted
	Output: None
*/
void uartPutC(char c);

/*
	void uartPutS

	Takes a string and puts it character by character into the buffer being transmitted

	Input: char *str
					A character buffer containing the message to be sent
	Output: None
*/
void uartPutS(char *str);

/*
	void usartGpioInit

	Initalizes the usart pin and sets up the clock needed for it

	Input: None
	Output: None
*/
void usartGpioInit(void);

/*
	void USARTWrite

	Write the buffer onto USART2 for virtualy serial port usage

	Input: uint8_t *buffer
						Buffer to be written to the port
				 uint32_t nBytes
						Size of the buffer to be written
	Output: None
*/
void USARTWrite(uint8_t *buffer, uint32_t nBytes);

/*
	void USART_Delay

	USART delay function

	Input: uint32_t ns
						Nano seconds to be delayed for
	Output: None
*/
void USART_Delay(uint32_t ns);

/*
	void USART_Read_String

	Reads the characters from the usart into a string until the max bytes is met or enter is pressed
	Input: char* buffer
						Buffer to store the string output
				 int nbytes
						Max number of bytes to read
	Output: None
*/
void USART_Read_String(char* buffer, int nbytes);

/*
	void USART_Read

	Reads the character from the usart
	Input: USART_TypeDef * USARTx
						The usart port to read from
	Output: uint8_t
						The character that was read
*/
uint8_t USART_Read(USART_TypeDef * USARTx);

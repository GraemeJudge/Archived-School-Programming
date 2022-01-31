/* uart.h -	function and variabe delcaration for using the uart
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			January 23, 2020: Source file created
*/

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


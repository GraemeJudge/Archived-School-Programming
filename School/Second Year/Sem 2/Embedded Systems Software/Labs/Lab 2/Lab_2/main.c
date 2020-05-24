/* main.c
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			January 23, 2020: Source file created
*/
#include "stm32l476xx.h"
#include "SysClock.h"
#include "uart.h"


/*
	void main;

	The main function for the program, initaizes everything then sends the data
	to the usart port to be printed on the serial line

	Input: None
	Output: None
*/
int main() {

	unsigned int counter = 0x6899;												//the inital value of the vounter being used
	
System_Clock_Init();															//initalize the system clock
uartInit();																		//initalize the clocks and the registers for the usart port
	
while(1){	
	uartPrintf("Graeme Judge\nSean Berkvens\nCount: %x\n", counter++);	//printed line
	for(int i = 0; i < 100000; i++);																		//delay
}

return 0;	

}


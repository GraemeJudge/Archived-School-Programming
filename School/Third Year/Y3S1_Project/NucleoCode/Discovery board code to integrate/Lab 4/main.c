/* main.c -	Main line for the LCD program being used with the STM32 discovery board
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			February 10, 2020: Source file created
*/

#include "stm32l476xx.h"
#include "SysClock.h"
#include "lcd.h"
#include <stdarg.h>

#define DELAY		for(int i = 0; i < 1000000; i++) 		//DELAY function




int main(void){
	System_Clock_Init(); 																// Switch System Clock = 80 MHz
	
	LCDInit();																					//initalizes the gpio port e and the syncs the lcd and puts it into 4 bit mode
	uint32_t counter = 0;
	
	for(;;){																						//infinite loop
		LCDprintf("Sean and Graeme\n%04X", counter++);		//print function 
		DELAY;																						//delay to make reading easier and a little more consistant
		LCDclear(); 																			//clears the lcd to prepare for the next write cycle
	}
}


#include "stm32l476xx.h"
#include "SysClock.h"
#include "Menu.h"
#include <String.h>
#include <stdlib.h>

#define DELAY  for(int i = 0; i < 10000000UL; i++) 		//DELAY function

uint8_t buffer[32];
char str2[] = "Give Red LED control input (Y = On, N = off):\r\n";


int main(void){
	
	System_Clock_Init(); // Switch System Clock = 80 MHz

	LCDInit();
	LCDclear();
	
	uartInit();
	
	while(1){
		drawCurrentMenu();		
		DELAY;
		LCDclear();
	}
}


#include "stm32l476xx.h"
#include "SysClock.h"


int main(void){

	System_Clock_Init(); // Switch System Clock = 80 MHz


	while(1);
}


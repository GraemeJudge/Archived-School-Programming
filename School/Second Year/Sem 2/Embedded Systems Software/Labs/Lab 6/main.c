#include "stm32l476xx.h"
#include "SysClock.h"

#include "lcd.h"
#include "LED.h"
#include "Timer.h"



#define DELAY		for(int i = 0; i < 10000000UL; i++) 		//DELAY function


int main(void){
	System_Clock_Init(); // Switch System Clock = 80 MHz
	initDistanceSensor();
	//DS_Init();
	LED_Init();
	LCDInit();
	LCDclear();
	
	
	while(1){
		uint32_t distance = getDistanceCM();
		if(distance != -1){
			LCDprintf("Distance: %d", distance);
		}
		else{
			LCDprintf("Invalid");
		}
			DELAY;
		LCDclear();
		Red_LED_Off();
		Green_LED_Off();
	}
}




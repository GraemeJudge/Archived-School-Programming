#include "stm32l476xx.h"
#include "SysClock.h"

#include "DistanceSensor.h"
#include "lcd.h"

#define DELAY		for(int i = 0; i < 10000000UL; i++) 	//delay function

int main(void){	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	initDistanceSensor();
	LCDInit();
	
	
	while(1){
		uint32_t distance = getDistanceCM();		//get the distance
		if(distance != -1){											//as long as the value is within range
			LCDprintf("Distance: %d", distance);	//print distance
		}
		else{
			LCDprintf("Invalid");
		}
		DELAY;
		LCDclear();
	}
}


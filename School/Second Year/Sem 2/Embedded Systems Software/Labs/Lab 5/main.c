#include "stm32l476xx.h"
#include "SysClock.h"

#include "servo.h"
#include "ADC.h"
#include "lcd.h"

#define DELAY		for(int i = 0; i < 10000000; i++) 		//DELAY function

int main(void){
	//servo on pin PE8
	System_Clock_Init(); // Switch System Clock = 80 MHz
	//start the lcd
	LCDInit();
	//start the servo pwm setup
	//initServo();
	//start the ADC
	//initADC();
	
		uint32_t counter = 0;
	
	while(1){
		//uint16_t reading = triggerADCConversion();
		//int16_t deg = servoMove(reading);
		LCDprintf("Fuck Yeah boyyyyyyysss");
		DELAY;
		LCDclear();
	}
}


#include "stm32l476xx.h"
#include "SysClock.h"
#include "EXTI.h"
#include "LED.h"

// delay count between changing LED states
#define DELAY_COUNT 10000000UL


// Push joystick center and toggle Green LED
int main(void){
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	LED_Init();
	EXTI_Init();
		
		for(;;) {
			Red_LED_Toggle();
			for(uint32_t i = 0; i < DELAY_COUNT; i++);
		}
		
} // main()


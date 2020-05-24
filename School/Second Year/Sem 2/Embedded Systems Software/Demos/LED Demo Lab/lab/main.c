//-------------------------------------------------------------------
// Hack demo to toggle red and green LEDS on Discovery board
// Jan 2019 - WPS
//
// Uses Zhu's SysClock code to init system clocks
//-------------------------------------------------------------------

#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
	
// delay count between changing LED states
#define DELAY_COUNT 10000000UL


int main(void){

	System_Clock_Init(); 	// Switch System Clock = 80 MHz
	LED_Init();						// Init GPIO bits to drive LEDs

	// loop forever toggling LEDs 
	for(;;) {

		Red_LED_Toggle();

		for( uint32_t i = 0; i < DELAY_COUNT; i++);
			
		Green_LED_Toggle();
			
		for( uint32_t i = 0; i < DELAY_COUNT; i++);
		
	} // for
	
} //main()




// Code from ppt to turn on red LED
#if 0	
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;  // Enable clock of Port B

	GPIOB->MODER &= ~(3UL<<4); // Clear mode bits
	GPIOB->MODER |=   1UL<<4;  // Set mode to output

	GPIOB->OTYPER &= ~(1UL<<2); // Select push-pull output

	GPIOB->ODR   |= 1UL << 2;  // Output 1 to turn on red LED
#endif

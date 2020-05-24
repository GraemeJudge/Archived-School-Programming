/* Joystick.c - function implementation for the Joystick.h
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			February 3, 2020: Source file created
*/

#include <stdlib.h>
#include "Joystick.h"
#include "stm32l476xx.h"


int state = 0;														//state of the output (table index)

int table[] = {8, 10, 2, 6, 4, 5, 1, 9};	//order of powering for the coils



void initGPIOPort(void){
	
	//Clock init
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	//clear bits 1 and 2 for pin 0 (bit shift to get to the next pin) 
	//00 is input mode
	GPIOA ->MODER &= ~(uint32_t)0xFFF;
		
	//no pull up or pull down all of the others will need a pull down (center is the ony one that doesnt)
	//00 none
	//01 pullup
	//10 pulldown
	//11 reserved
	GPIOA -> PUPDR |= (uint32_t)0x8A8;

//	//01 is output mode
//	GPIOE->MODER = ~(255U<<(2*12));  
//	GPIOE->MODER |= 85U<<(2*12);      //  Output(01)
//	
//	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
//	GPIOE->OSPEEDR &= ~(255U<<(2*12));
//	GPIOE->OSPEEDR |=   255U<<(2*12);  // High speed
//	
//	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
//	GPIOE->OTYPER &= ~(1U<<15);       // Push-pull
//	
//	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
//	GPIOE->PUPDR   &= ~(255U<<(2*12));  // No pull-up, no pull-down
//	
//	//clears the output data register for port E
//	GPIOE->ODR &= (uint32_t)0x0000;	
}


void step(int direction){
//1/-1 for halfsetp and 2/-2 for fullstep
	state += (direction);
	int f = state;
	if(state >= 8){
		state = state - 8;
	}
	if(state<= -1){
		state = 8 - abs(direction);
	}
	GPIOE->ODR &= 0x0FFF; //clears the upper 4 bits
	GPIOE->ODR |= (uint32_t)table[state] << 12; //shifts the new result into the output register
}



uint32_t getInput(void){
	return GPIOA ->IDR & (uint32_t)0xFF;	
}




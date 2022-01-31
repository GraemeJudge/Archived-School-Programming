/* Keypad.c - implemetation of Keypad.h
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			May 3, 2020: Source file created
*/


#include "Keypad.h"

#define KEYDELAY for(int i =0; i < 8000; i++)

#define DELLY for(int i =0; i < 100000; i++)

uint8_t rows[4] = {ROW1, ROW2, ROW3, ROW4};

void GPIOInit(){
	GPIOInitRow();
	GPIOInitCol();
	
}

void GPIOInitRow(){
	//Clock init
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	//using PE12 to PE15 
	for(int i = 12; i < 16; i++){ //for loop to go through all of the pins being used and initializes them 
		// GPIO Mode
		//00 input mode
		//01 output mode
		//10 alternate mode
		//11 analog mode
		GPIOE->MODER &= ~(3UL<<(2*i));  
		GPIOE->MODER |= (1UL<<(2*i));      	//  Output(01)
		
		//GPIO Speed
		GPIOE->OSPEEDR &= (~(3UL<<(2*i)));
		GPIOE->OSPEEDR |=   (3UL<<(2*i));  // Low speed
				
		//00 none
		//01 pullup
		//10 pulldown
		//11 reserved
		GPIOE->PUPDR   |= (1UL<<(2*i));  // pull-up
		
		//GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
		GPIOE->OTYPER |= (1U<<(1*i));       // Push-pull open drain
	}	
	
	//clears the output data register for port E
	GPIOE->ODR &= (uint32_t)0x0000;	
}



void GPIOInitCol(){
	//Clock init
	RCC -> AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	//using PA1 to PA5 excluding 4	
	for(int i = 1; i < 4; i++){ //for loop to go through all of the pins being used and initializes them 
			// GPIO Mode
			//00 input mode
			//01 output mode
			//10 alternate mode
			//11 analog mode
			GPIOA->MODER &= ~(3UL<<(2*i));  
					
			//00 none
			//01 pullup
			//10 pulldown
			//11 reserved
			GPIOA->PUPDR |= (1UL<<(2*i));  // pull-up
		}
		
			// GPIO Pin 5
			//00 input mode
			//01 output mode
			//10 alternate mode
			//11 analog mode
			GPIOA->MODER &= ~(3UL<<(2*5));  
					
			//00 none
			//01 pullup
			//10 pulldown
			//11 reserved
			GPIOA->PUPDR |= (1UL<<(2*5));  // pull-up
}



enum Keys scan(){
	GPIOE->ODR &= 0b0000 << 12;
	DELLY;
	uint8_t button = debouncedKey();
	
	if((button & 0xFF) == 0x2E){
		return Key_None;
	}
	
	for(int i = 0; i < 4; i++){
		GPIOE->ODR = (rows[i])<<12;
		DELLY;
		button = debouncedKey();
		if(button != 0x2E){
			if(button == COL1){
				return Matrix[i][0];
			}
			if(button == COL2){
				return Matrix[i][1];
			}
			if(button == COL3){
				return Matrix[i][2];
			}
			if(button == COL4){
				return Matrix[i][3];
			}
		}
	}
}

uint8_t getInput(){
	volatile uint8_t IDR = (GPIOA->IDR & 0x2E);
	return IDR;
}

uint8_t debouncedKey(){
	uint8_t read = getInput();
	
	for(int i = 0; i < DEBOUNCETIME; i++){
		uint8_t newRead = getInput();
		if(read != newRead || read == 0x2E){
			read = 0x2E;
			return read;
		}
		KEYDELAY;
	}
	return read;
}








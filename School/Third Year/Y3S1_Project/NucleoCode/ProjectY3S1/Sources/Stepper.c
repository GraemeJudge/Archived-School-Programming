/* Stepper.c - function implementation for the Joystick.h
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			February 3, 2020: Source file created
*/

#include "Stepper.h"


int state = 0;														//state of the output (table index)
int table[] = {8, 10, 2, 6, 4, 5, 1, 9};	//order of powering for the coils

int stepCounter = 0;

//PC0-3 for stepper output
void initStepper(void){	
	SET_BITS(RCC->AHBENR, RCC_AHBENR_GPIOCEN);

	//01 is output mode
	CLR_BITS(GPIOC->MODER, 0xFF);
	SET_BITS(GPIOC->MODER, 0x55);
	
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	//setting to low speed: Reset value is low so nothing needs to be done
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	//set to push pull: Reset state is 0 so nothing needs to be done
	
	//GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	//No pull-up, no pull-down : Reset state is 00 so nothing needs to be done
	
	//clears the output data register for port C
	SET_BITS(GPIOC->ODR, 0x00);
}


void step(int direction){
//1/-1 for halfsetp and 2/-2 for fullstep
	state += (direction);
	if(state >= 8){
		state = state - 8;
	}
	if(state<= -1){
		state = 8 - abs(direction);
	}
	CLR_BITS(GPIOC->ODR, 0xFF); //clears the upper 4 bits
	GPIOC->ODR |= (uint32_t)table[state]; //shifts the new result into the output register
}



void homeCamera(void){
		
	while(triggered != -1){
		step(-2);
		SHORTERDELAY;
	}
	stepCounter = 0;
	printf("Hit the left edge!\n");

	while(triggered != 1){
		step(2);
		SHORTERDELAY;
		stepCounter += 1;
	}
	printf("Steps counted: %d\n", stepCounter);
	
	for(int i = 0; i < stepCounter/2; i++){
		step(-2);
		SHORTERDELAY;
	}
	setServo(0);

	triggered = 0;
	stepCounter = 0;
	printf("Centered the camera!\n");
}


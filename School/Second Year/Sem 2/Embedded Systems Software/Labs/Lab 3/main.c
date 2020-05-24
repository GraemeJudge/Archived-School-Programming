/* main.c - Main line program for the joy stick and stepper motor lab
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			February 3, 2020: Source file created
*/

#include "stm32l476xx.h"
#include "SysClock.h"
#include "Joystick.h"


uint32_t input;
uint32_t DELAY_COUNT = 10000UL; //10 seconds ish	


/*
	void main;

	The main function for the program, initaizes everything then checks the input port
	and steps the stepper motor if input is active

	Input: None
	Output: returns an integer as an exit status
*/
int main(void){
	
	System_Clock_Init(); // Switch System Clock = 80 MHz

	
	initGPIOPort();

		// loop forever checking input and moving the stepper motor if input has been pressed
	for(;;) {
		input = getInput(); //get the input
		
		//full stepping on left and right
//		if(input == left){
//			step(2);
//		}
//		if(input == right){
//			step(-2);
//		}
//		//half stepping on up down
//		if(input == up){
//			step(1);
//		}
//		if(input == down){
//			step(-1);
//		}
		
		//delay
		for(int i =0; i < 1000000; i++);
		
	}
}


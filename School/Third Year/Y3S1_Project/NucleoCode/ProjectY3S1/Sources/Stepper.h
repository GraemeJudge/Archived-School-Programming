/* Stepper.h - function prototypes and declarations for the c implemetation file
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			February 3, 2020: Source file created
*/

#include <stdint.h>
#include "stm32f303xe.h"
#include "utils.h"
#include "servo.h"
#include "LimitSwitches.h"
#include <stdlib.h>
#include <stdio.h>


/*
	void initStepper;

	initalizes the gpio ports as needed for the stepper outout for 
	the program to function properly

	Input: None
	Output: None
*/
 void initStepper(void);
 
/*
	void step;

	Steps the motor based on the given input, an input of 1 will halfstep the motor and -1 will halfstep
	in the opposite direction. 2 will full step the motor and -2 will full step in the opposite direction

	Input: int direction
						The direction and step size for the motor to take
	Output: None
*/
void step(int direction);


void homeCamera(void);

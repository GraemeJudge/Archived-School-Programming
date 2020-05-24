/* Joystick.h - function prototypes and declarations for the c implemetation file
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			February 3, 2020: Source file created
*/

#include <stdint.h>

//bit patters for the different button presses to be read on the joystick
#define center 0x1
#define left 0x2
#define right 0x4
#define up 0x8
#define down 0x20


/*NOTES:
	Joystick: pins PA0 center, PA1 left, PA5 down, PA2 right, PA3	up
	//page 360
*/

/*
	void initGPIOPort;

	initalizes the gpio ports as needed for the input and the outout for 
	the program to function properly

	Input: None
	Output: None
*/
 void initGPIOPort(void);

/*
	void step;

	Steps the motor based on the given input, an input of 1 will halfstep the motor and -1 will halfstep
	in the opposite direction. 2 will full step the motor and -2 will full step in the opposite direction

	Input: int direction
						The direction and step size for the motor to take
	Output: None
*/
void step(int direction);

/*
	void getInput;

	This function gets the input from port a (the joystick) and masks it to isolate the lower byte
	to be used for comparison

	Input: None
	Output: uint32_t
						The result of masking the port for the input checking the lowest byte
*/
uint32_t getInput(void);

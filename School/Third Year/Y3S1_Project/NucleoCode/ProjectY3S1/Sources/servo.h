#include "stm32f303xe.h"
#include "utils.h"
#include "UART.h"

/*
	void initServo;

	Initalizes the servo gpio port

	Input: 	None
	Output: None
*/
void initServo(void);

/*
	void initTimer;

	Initalizes the PWM timer output for driving the servo

	Input: 	None
	Output: None
*/
void initTimer(void);

/*
	void servoMove;

	moves the servo based on a given ADC input value

	Input: uint16_t val
		the ADC value to use to determine the position of the servo
	Output: uint16_t
		The degrees the servo motor is at
*/
int16_t servoMove(uint16_t val);

/*
	void setDutyCycle;

	Sets the duty cycle for the PWM timer output for driving the servo

	Input: uint16_t duty
		The duty cycle to set the PWM timer to
	Output: None
*/
void setDutyCycle(uint8_t duty);	

//
//
//
//
void setServo(int8_t deg);


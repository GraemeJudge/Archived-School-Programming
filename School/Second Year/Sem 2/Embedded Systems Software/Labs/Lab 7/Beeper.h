/* Beeper.h - function prototypes and declarations for the c implemetation file
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			May 3, 2020: Source file created
*/

#include "stm32l476xx.h"

/*
	void InitBeeper;

	initalizes the gpio ports as needed for the input and the outout for 
	the program to function properly

	Input: None
	Output: None
*/	
void InitBeeper( void );

/*
	void Beep;

	Causes the beeper to create a tone at a specific frequency 

	Input: a 16bit integer for the frequency to beep at
	Output: None
*/	
void Beep( uint32_t hertz );

/*
	void StopBeep;

	Stops the beeper from making noise

	Input: None
	Output: None
*/	
void StopBeep( void );

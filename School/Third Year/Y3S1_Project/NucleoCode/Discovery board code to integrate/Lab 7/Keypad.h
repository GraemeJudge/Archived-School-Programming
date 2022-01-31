/* Keypad.h - function prototypes and declarations for the c implemetation file
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			May 3, 2020: Source file created
*/

#include "stm32l476xx.h"

//defined values
#define DEBOUNCETIME 3

#define COL1 0x2C
#define COL2 0x2A
#define COL3 0x26
#define COL4 0xE

#define START  0b11110111

#define ROW4 0b1110
#define ROW3 0b1101
#define ROW2 0b1011
#define ROW1 0b0111



enum Keys {
	Key_None = -1, 
	Key_1, 
	Key_2, 
	Key_3, 
	Key_A, 
	Key_4, 
	Key_5, 
	Key_6,
	Key_B, 
	Key_7, 
	Key_8, 
	Key_9,
	Key_C, 
	Key_Star, 
	Key_0, 
	Key_Pound, 
	Key_D
};

static enum Keys Matrix[4][4] = {{Key_1, Key_2, Key_3, Key_A},
												{Key_4, Key_5, Key_6, Key_B},
												{Key_7, Key_8, Key_9, Key_C},
												{Key_Star, Key_0, Key_Pound, Key_D}};

												
/*
	void GPIOInit;

	initalizes the gpio ports as needed for the input and the outout for 
	the program to function properly

	Input: None
	Output: None
*/												
void GPIOInit();
			
/*
	void GPIOInitRow;

	initalizes the gpio ports as needed for the row outout for 
	the program to function properly

	Input: None
	Output: None
*/													
void GPIOInitRow(void);

/*
	void GPIOInitCol;

	initalizes the gpio ports as needed for the input for 
	the program to function properly

	Input: None
	Output: None
*/	
void GPIOInitCol(void);												

/*
	void scan;

	scans the keypad and returns the key thats being pressed

	Input: None
	Output: The pressed key as defined in the Keys struct 
*/	
enum Keys scan(void);

/*
	void getInput;

	Gets the input form the port

	Input: None
	Output: the lowest 8 bits from the input port
*/	
uint8_t getInput(void);

/*
	void debouncedKey;

	gets the pressed key value and uses debounce to ensure the correct value
	
	Input: None
	Output: the bit pattern of the input  port with debounce
*/	
uint8_t debouncedKey(void);

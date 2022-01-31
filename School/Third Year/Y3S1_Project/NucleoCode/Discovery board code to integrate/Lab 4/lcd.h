#ifndef _LCD_H
#define _LCD_H

#include "stm32l476xx.h"
#include "utils.h"

#define MAX_LCD_BUFSIZ      (80 + 1)

// Commands to LCD module
#define LCD_CMD_CLEAR           0x01u
#define LCD_CMD_HOME            0x02u
#define LCD_CMD_ENTRY           0x04u
#define LCD_CMD_DISPLAY         0x08u
#define LCD_CMD_CD_SHIFT        0x10u
#define LCD_CMD_FUNCTION        0x20u
#define LCD_CMD_CGRAMADDR       0x40u
#define LCD_CMD_SET_DDADDR      0x80u

// Settings for LCD_CMD_ENTRY
#define LCD_ENTRY_MOVE_DISPLAY  0x01
#define LCD_ENTRY_MOVE_CURSOR   0x00
#define LCD_ENTRY_INC           0x02    
#define LCD_ENTRY_DEC           0x00

// Settings for LCD_CMD_DISPLAY
#define LCD_DISPLAY_BLINK       0x01
#define LCD_DISPLAY_NOBLINK     0x00
#define LCD_DISPLAY_CURSOR      0x02
#define LCD_DISPLAY_NOCURSOR    0x00
#define LCD_DISPLAY_ON          0x04
#define LCD_DISPLAY_OFF         0x00

// Settings for LCD_CMD_CD_SHIFT (shift cursor or display without changing data)
#define LCD_CD_SHIFT_RIGHT      0x04
#define LCD_CD_SHIFT_LEFT       0x00
#define LCD_CD_SHIFT_DISPLAY    0x08
#define LCD_CD_SHIFT_CURSOR     0x00

// Settings for LCD_CMD_FUNCTION
#define LCD_FUNCTION_5X10FONT   0x04
#define LCD_FUNCTION_5X8FONT    0x00
#define LCD_FUNCTION_2LINES     0x08
#define LCD_FUNCTION_1LINE      0x00
#define LCD_FUNCTION_8BIT       0x10
#define LCD_FUNCTION_4BIT       0x00

#define LCD_LONG_CMD_DELAY      16

#define LCD_PORT_BITS       (LCD_E_BIT | LCD_RS_BIT | LCD_BUS_BITS)

#define LCD_ADDR_LINE2      0x40

#define LCD_PORT            GPIOE->ODR

#define LCD_E_BIT           GPIO_ODR_ODR_11
#define LCD_RS_BIT          GPIO_ODR_ODR_10
#define LCD_BUS_BITS        (GPIO_ODR_ODR_15 | GPIO_ODR_ODR_14 | GPIO_ODR_ODR_13 | GPIO_ODR_ODR_12)

#define LCD_E_LO            CLR_BITS( LCD_PORT, LCD_E_BIT )
#define LCD_E_HI            SET_BITS( LCD_PORT, LCD_E_BIT )
#define LCD_RW_READ         SET_BITS( LCD_PORT, LCD_RW_BIT )
#define LCD_RW_WRITE        CLR_BITS( LCD_PORT, LCD_RW_BIT )
#define LCD_RS_DR           SET_BITS( LCD_PORT, LCD_RS_BIT )
#define LCD_RS_IR           CLR_BITS( LCD_PORT, LCD_RS_BIT )
#define LCD_BUS( value )    FORCE_BITS( LCD_PORT, LCD_BUS_BITS, (value)<<12 )

/*
	void Delay_ms;

	Delays the program by the given number of ms formatted as a 16 bit unsigned integer

	Input: uint16_t delaTime
		number of miliseconds to delay for 
	Output: None
*/
extern void Delay_ms(uint16_t delayTime );

/*
	void LCDInit;

	Initalizies the lcd by setting up the gpio port for port e 
	and syncing the lcd and setting it into 4 bit mode

	Input:  None
	Output: None
*/
extern void LCDInit( void );

/*
	void LCDclear;

	Clears the LCD screen to prepare it for the next time is being written onto

	Input:  None
	Output: None
*/
extern void LCDclear( void );

/*
	void LCDhomeCursor;

	Sets the cursor back to the home location in the top left corner

	Input: none
	Output: None
*/
extern void LCDhomeCursor( void );

/*
	void LCDprintf;

	Prints a formatted string onto the LCD screen

	Input: char* formatString
				Formatted stirng to be printed out onto the LCD screen
	Output: None
*/
extern void LCDprintf( char * formatString, ... );

/*
	void LCDputs;

	Puts a string into the buffer to be sent to the LCD

	Input: char* thisString
				Character buffer (string) to be printed n the LCD
	Output: None
*/
extern void LCDputs( char * thisString );

/*
	void LCDputc;

	Puts a character into the buffer to be sent to the LCD

	Input: unsigned char thisChar
				character to be sent to the lcd and be printed
	Output: None
*/
extern void LCDputc( unsigned char thisChar );

/*
	void LCDcmd;

	Sends a command to the LCD

	Input: unsigned char thisByte
				The command byte to be sent
	Output: None
*/
extern void LCDcmd( unsigned char thisByte );

/*
	void LCDdata;

	Sends the given data to the LCD module

	Input: unsigned char thisByte
				Byte of data to be sent to the LCD module
	Output: None
*/
extern void LCDdata( unsigned char thisByte );

#endif

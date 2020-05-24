/* lcd.c -	Implementation and definition of the lcd.h header file
*						to be used to initalze and utilize a lcd display
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*			Change Log:
*  			February 10, 2020: Source file created
*/

#include "lcd.h"
#include <stdio.h>
#include <stdarg.h>

uint8_t line_Count = 0;

extern void Delay_ms(uint16_t delayTime ){
	//Bill said there was a typo in this
	SysTick->CTRL = 0;																									//Disable systick
	SysTick->LOAD = (800000000 / 1000UL) * delayTime;										//set reload register
	SysTick->VAL = 0;																										//Reset the systick counter value
	
	//select processor clock: 1 = processor clock; 0 = external clock
	SysTick->CTRL |= SysTick_CTRL_CLKSOURCE_Msk;
	//disable systick interrupt, 1 = Enable, 0 = disable
	SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
	//enable systick
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;
	//wait for timeout
	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	//disable systick until next time
	SysTick->CTRL = 0;
}




extern void LCDInit(){ 
	//first init the gpio port for the lcd
	 
	//Enable Clock for port E
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOEEN;
	
	//using PE10 to PE15 
	for(int i = 10; i < 16; i++){ //for loop to go through all of the pins being used and initializes them 
		// GPIO Mode
		GPIOE->MODER &= ~(3UL<<(2*i));  
		GPIOE->MODER |= (1UL<<(2*i));      //  Output(01)
		
		//GPIO Speed
		GPIOE->OSPEEDR &= (~(3UL<<(2*i)));
		GPIOE->OSPEEDR |=   (3UL<<(2*i));  // High speed
				
		//GPIO Push-Pull
		GPIOE->PUPDR   &= ~(3UL<<(2*i));  // No pull-up, no pull-down
	}	
	
	//second sync the display and wake it and stuff
		LCD_E_HI;
		LCD_BUS(0x03);	//wake up display & sync
		LCD_E_LO;
	
		Delay_ms(5);
	
		LCD_E_HI;
		LCD_BUS(0x03);	//wake up display & sync
		LCD_E_LO;
	
		Delay_ms(1);
	
		LCD_E_HI;
		LCD_BUS(0x03);	//wake up display & sync
		LCD_E_LO;
	
		LCD_E_HI;
		LCD_BUS(0x02);	//wake up display & sync - force 4 bit mode
		LCD_E_LO;
	
		Delay_ms(2);
		
		//4-bit mode commands to configure the display
		LCDcmd( LCD_CMD_FUNCTION | LCD_FUNCTION_4BIT | LCD_FUNCTION_5X8FONT);
		LCDcmd( LCD_CMD_DISPLAY | LCD_DISPLAY_OFF);
		LCDclear();
		LCDcmd(LCD_CMD_ENTRY| LCD_ENTRY_MOVE_CURSOR | LCD_ENTRY_INC);
		LCDcmd(LCD_CMD_DISPLAY | LCD_DISPLAY_ON | LCD_DISPLAY_NOCURSOR | LCD_DISPLAY_NOBLINK);
}


extern void LCDclear( void ){
	LCDcmd(LCD_CMD_CLEAR);
	line_Count = 0;
}

extern void LCDhomeCursor( void ){
	LCDcmd(LCD_CMD_HOME);
}

extern void LCDprintf( char * formatString, ... ){
	va_list args;
	char buffer[MAX_LCD_BUFSIZ];
	
	va_start(args, formatString);
	vsnprintf(buffer, MAX_LCD_BUFSIZ, formatString, args);
	va_end(args);
	
	LCDputs(buffer);
	
}

extern void LCDputs( char * thisString ){
	while(*thisString){
		LCDputc(*thisString++);
	}
}

extern void LCDputc( unsigned char thisChar ){	
	if ('\n' == thisChar){
		if(line_Count >= 3){
			line_Count = 0;
			LCDhomeCursor();
		return;
		}
		if(line_Count == 0){
			LCDcmd(LCD_CMD_SET_DDADDR | LCD_ADDR_LINE2);
			line_Count++; 
			return;
		}
		if(line_Count == 1){
			LCDcmd(LCD_CMD_SET_DDADDR | LCD_ADDR_LINE3);
			line_Count++; 
			return;
		}
		if(line_Count == 2){
			LCDcmd(LCD_CMD_SET_DDADDR | LCD_ADDR_LINE4);
				line_Count++;
			return;
		}
	} else {
		LCDdata(thisChar);
	}
}

extern void LCDcmd( unsigned char thisByte ){
	LCD_E_LO; 		//Pull the E line low
	LCD_RS_IR; 		//Set the RS line to select the instruction (low) or data register high
	LCD_E_HI; 		//pull the E line high
	LCD_BUS(HI_NYBBLE(thisByte));		//Output the upper 4 bits of data to LCD Data Bus
	LCD_E_LO;		//Pull the E line low
	LCD_E_HI;		//Pull the E line high
	LCD_BUS(LO_NYBBLE(thisByte)); 	//Output the lower 4 bits of data to LCD Data Bus [7:4]
	LCD_E_LO; 		//Pull the E line low
	Delay_ms(1);
}

extern void LCDdata( unsigned char thisByte ){
	LCD_E_LO; 		//Pull the E line low
	LCD_RS_DR; 		//Set the RS line to select the instruction (low) or data register high
	LCD_E_HI; 		//pull the E line high
	LCD_BUS(HI_NYBBLE(thisByte));		//Output the upprt4 bits of data to LCD Data Bus
	LCD_E_LO;		//Pull the E line low
	LCD_E_HI;		//Pull the E line high
	LCD_BUS(LO_NYBBLE(thisByte)); 	//Output the lower 4 bits of data to LCD Data Bus [7:4]
	LCD_E_LO; 		//Pull the E line low
	Delay_ms(1);
}

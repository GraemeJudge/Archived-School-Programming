#include "stm32l476xx.h"
#include "SysClock.h"
#include "LED.h"
#include "Keypad.h"
#include "Beeper.h"

#define DELAY for(int i = 0; i < 10000000; i ++);

int toneFrequencies[16] = {131, 523, 494, 440, 392, 349, 330, 294, 262, 247, 220, 193, 175, 165, 147, 587};

int main(void){

	int running = 1;
	
	System_Clock_Init(); // Switch System Clock = 80 MHz
	
	GPIOInitRow();
	GPIOInitCol(); 
	
	InitBeeper();
	
	enum Keys keyPressed;
	
	while(running == 1){
		keyPressed = scan();
		if(keyPressed == Key_None){
			StopBeep();
		}else{
			Beep(toneFrequencies[keyPressed]);
		}
		DELAY;
	}
	
}


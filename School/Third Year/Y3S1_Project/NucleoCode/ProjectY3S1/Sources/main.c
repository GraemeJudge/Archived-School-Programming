//-------------------------------------------------------------------
// Shell code for Nucleo-64 STM32F303RE @ 72 MHz
//
// Changes Green (user) LED state in response to character commands
//	received over ST Link Virtual COM port
//
// Alternate version flashes green LED 	
//
// WPS 30 Apr 2020 - from Zhu Virtual Com Port demo code
//
//-------------------------------------------------------------------

#include "stm32f303xe.h"
#include "SysClock.h"
#include "LED.h"
#include "UART.h"
#include "servo.h"
#include "Stepper.h"
#include "Commands.h"
#include "motors.h"
#include "Heartbeat.h"
#include "LimitSwitches.h"
#include "encoders.h"

int main(void){
	System_Clock_Init(); 			// Switch System Clock = 72 MHz
	SystemCoreClockUpdate();	// update global var SystemCoreClock to new clock value (72 MHz)
	
	LED_Init();								//LED init
	initSwitches();
	UART2_Init();							//UART port init
	initStepper();						//Stepper init
	initServo();							//Servo init
	
	rightMotorInit();					//Initializes the right motor
	leftMotorInit();					//Initializes the left motor
	
	L_Encoder_timer_init();
	
	initHB();
	
	homeCamera();
	
	while(1){		
		if(commandBuffer[rx_Counter - 1] == '\n'){		//if newline is last character read from the usart port 
			process();
		}
		
		//servo test
		//servoMove(2620);
		//DELAY;
		//servoMove(3750);
 		//DELAY;
			
		
		//Stepper motor test
		//		step(1);
		//		DELAY;
		//		step(2);
		//		DELAY;		
		//		
		
	}	
	
}	// main()


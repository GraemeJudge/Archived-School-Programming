/* Menu.c -	Implementation of Menu.h
*
*  		Copyright 2020 Graeme Judge
*		Change Log:
*				April 27, 2020: File created
*/

#include "Menu.h"

#define DELAY  for(int i = 0; i < 100000000UL; i++) 		//DELAY function

int menuState = 0;

void drawCurrentMenu(void){
	USARTWrite((uint8_t *)header, strlen(header));	
	switch(menuState){
		case MAIN:
			drawMainMenu();
			break;
		case RS232:
			drawRS232Menu();
			break;
		case MOTOR:
			drawMotorMenu();
			break;
		case MOTORMOVE:
			drawMotorMoveMenu();
			break;
		case LCDMENU:
			drawLCDMenu();
			break;
		case LEFTMOTOR:
			leftMotorMenu();
			break;
		case RIGHTMOTOR:
			rightMotorMenu();
			break;
		case STEPPERMOTOR:
			stepperMotorMenu();
			break;
		case SERVOMOTOR:
			servoMotorMenu();
			break;
	}
}


void drawMainMenu(){
	char inByte;
	USARTWrite((uint8_t *)mainMenu, strlen(mainMenu));	
	inByte = USART_Read(USART2);
		if (inByte == '1'){
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
			menuState = RS232;
		}
		if (inByte == '2'){
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
			menuState = MOTOR;	//motor test menu
		}
		if (inByte == '3'){
			USARTWrite((uint8_t *)"option 3 selected\r\n\r\n", 24);
			menuState = LCDMENU;	//lcd test menu
		}
}



void drawMotorMenu(void){
	char inByte;
	USARTWrite((uint8_t *)MotorTestMenu, strlen(MotorTestMenu));
	
	inByte = USART_Read(USART2);
	if (inByte == '1'){	//stepper
		USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
		menuState = STEPPERMOTOR;
	}
	if (inByte == '2'){	//limit
		USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
		USARTWrite((uint8_t *)"Press Limit Switch To Test\r\n\r\n", 32);
	}
	if (inByte == '3'){ //motor movement test
		USARTWrite((uint8_t *)"option 3 selected\r\n\r\n", 24);
		menuState = MOTORMOVE;	//motor movement menu
	}
	if (inByte == '4'){	//encoder
		USARTWrite((uint8_t *)"option 4 selected\r\n\r\n", 24);
		USARTWrite((uint8_t *)"Left Motor Speed:     Right Motor Speed: \r\n\r\n", 48);
		DELAY;
	}
	if (inByte == '5'){	//Servo
		USARTWrite((uint8_t *)"option 5 selected\r\n\r\n", 24);
		menuState = SERVOMOTOR;	//back to the main menu
	}
		if (inByte == '6'){	//back to menu
		USARTWrite((uint8_t *)"option 6 selected\r\n\r\n", 24);
		menuState = MAIN;	//back to the main menu
	}
}


void drawMotorMoveMenu(){
	char inByte;
	USARTWrite((uint8_t *)MotorMoveMenu, strlen(MotorMoveMenu));
	inByte = USART_Read(USART2);
		if (inByte == '1'){	//left motor
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
			menuState = LEFTMOTOR;
		}
		if (inByte == '2'){	//right motor
			menuState = RIGHTMOTOR;
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
		}
		if (inByte == '3'){	//back to motor menu
			USARTWrite((uint8_t *)"option 5 selected\r\n\r\n", 24);
			menuState = MOTOR;	//back to the motor menu
		}
}

void leftMotorMenu(){
	char inByte;
	char* duty;
	int n;
	duty = malloc(3);
	
	uint8_t buffer[32];
	
	USARTWrite((uint8_t *)LeftMotor, strlen(LeftMotor));
	inByte = USART_Read(USART2);
		if (inByte == '1'){	//forwards
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Enter Duty Cycle:\r\n\r\n", 24);
			USART_Read_String(duty, 3);
			
			n = sprintf((char *)buffer, "Running Motor Forwards At %d%%\r\n\r\n", atoi(duty));
			USARTWrite((uint8_t *)buffer, n);
			DELAY;
		}
		if (inByte == '2'){	//backwards
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Enter Duty Cycle:\r\n\r\n", 24);
			USART_Read_String(duty, 3);
			
			n = sprintf((char *)buffer, "Running Motor Backwards At %d%%\r\n\r\n", atoi(duty));
			USARTWrite((uint8_t *)buffer, n);
			DELAY;
		}
		if (inByte == '3'){	//back to motor menu
			USARTWrite((uint8_t *)"option 3 selected\r\n\r\n", 24);
			menuState = MOTORMOVE;	//back to the motor menu
		}
}

void rightMotorMenu(){
	char inByte;
	char* duty;
	int n;
	duty = malloc(3);
	
	uint8_t buffer[32];
	
	USARTWrite((uint8_t *)RightMotor, strlen(RightMotor));
	inByte = USART_Read(USART2);
		if (inByte == '1'){	//forwards
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Enter Duty Cycle:\r\n\r\n", 24);
			USART_Read_String(duty, 3);
			
			n = sprintf((char *)buffer, "Running Motor Forwards At %d%%\r\n\r\n", atoi(duty));
			USARTWrite((uint8_t *)buffer, n);
			DELAY;
		}
		if (inByte == '2'){	//backwards
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Enter Duty Cycle:\r\n\r\n", 24);
			USART_Read_String(duty, 3);
			
			n = sprintf((char *)buffer, "Running Motor Backwards At %d%%\r\n\r\n", atoi(duty));
			USARTWrite((uint8_t *)buffer, n);
			DELAY;
		}
		if (inByte == '3'){	//back to motor menu
			USARTWrite((uint8_t *)"option 3 selected\r\n\r\n", 24);
			menuState = MOTORMOVE;	//back to the motor menu
		}
}

void stepperMotorMenu(){
	char inByte;
	char* position;
	int n;
	position = malloc(3);
	
	uint8_t buffer[32];
	
	USARTWrite((uint8_t *)StepperMotor, strlen(StepperMotor));
	inByte = USART_Read(USART2);
		if (inByte == '1'){	//home
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Sending Stepper Motor Home\r\n\r\n", 32);
		}
		if (inByte == '2'){	//to position
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Enter Position(Degrees):\r\n\r\n", 32);
			USART_Read_String(position, 3);
			
			n = sprintf((char *)buffer, "Moving Motor To %d Degrees\r\n\r\n", atoi(position));
			USARTWrite((uint8_t *)buffer, n);
			DELAY;
		}
		if (inByte == '3'){	//set Step
			USARTWrite((uint8_t *)"option 3 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)StepSelect, strlen(StepSelect));
			char selectByte;
			selectByte = USART_Read(USART2);
			if(selectByte == '1'){
				USARTWrite((uint8_t *)"Half Step Selected\r\n\r\n", 25);
				menuState = STEPPERMOTOR;
			}
			if(selectByte == '2'){
				USARTWrite((uint8_t *)"Full Step Selected\r\n\r\n", 25);
				menuState = STEPPERMOTOR;
			}
			if(selectByte == '3'){
				menuState = STEPPERMOTOR;
			}
		}
		if (inByte == '4'){	//getPosition
			USARTWrite((uint8_t *)"option 4 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Stepper Position(Degrees):\r\n\r\n", 32);
		}
		if (inByte == '5'){	//back to motor menu
			USARTWrite((uint8_t *)"option 5 selected\r\n\r\n", 24);
			menuState = MOTORMOVE;	//back to the motor menu
		}
}

void servoMotorMenu(){
	char inByte;
	char* position;
	int n;
	position = malloc(3);
	
	uint8_t buffer[32];
	
	USARTWrite((uint8_t *)ServoMotor, strlen(ServoMotor));
	inByte = USART_Read(USART2);
		if (inByte == '1'){	//to position
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Enter Position(Degrees):\r\n\r\n", 32);
			USART_Read_String(position, 3);
			
			n = sprintf((char *)buffer, "Moving Motor To %d Degrees\r\n\r\n", atoi(position));
			USARTWrite((uint8_t *)buffer, n);
			DELAY;
		}
		if (inByte == '2'){	//back
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
			menuState = MOTOR;
		}
}

void drawRS232Menu(void){
	char inByte;
	char* buffer;
	int n;
	uint8_t buff[64];
	buffer = malloc(32);
	
	USARTWrite((uint8_t *)RS232TestMenu, strlen(RS232TestMenu));
	inByte = USART_Read(USART2);
		if (inByte == '1'){	//send	
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Enter Text To Send(max 32 characters) Then Press Enter: \r\n\r\n", 64);	

			USART_Read_String(buffer, 32);
			n = sprintf((char *)buff, "Sending: %s\n\r\n\r", buffer);
			USARTWrite((uint8_t *)buff, n);
			DELAY;
		
		}
		if (inByte == '2'){	//recieve
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Place Holder\r\n\r\n", 20);
		}
		if (inByte == '3'){	//echo mode	
			USARTWrite((uint8_t *)"option 3 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Place Holder\r\n\r\n", 20);
		}
		if (inByte == '4'){	//back to menu
			USARTWrite((uint8_t *)"option 4 selected\r\n\r\n", 24);
			menuState = MAIN;
		}
}

void drawLCDMenu(){
	char inByte;
	char* buffer;
	buffer = malloc(32);
	USARTWrite((uint8_t *)LCDTestMenu, strlen(LCDTestMenu));
	inByte = USART_Read(USART2);
		if (inByte == '1'){
			USARTWrite((uint8_t *)"option 1 selected\r\n\r\n", 23);
			USARTWrite((uint8_t *)"See LCD Screen\r\n\r\n", 20);
			LCDclear();
			USARTWrite((uint8_t *)DisplayLCDTest, strlen(DisplayLCDTest));
			LCDprintf("Testing Line 1\n Testing Line 2\n  Testing Line 3\n   Testing Line 4");
			DELAY;
		}
		if (inByte == '2'){
			USARTWrite((uint8_t *)"option 2 selected\r\n\r\n", 24);
			USARTWrite((uint8_t *)"Type text to display (max 32 chars) and press enter to display it:\r\n", 70);
			USART_Read_String(buffer, 32);
			USARTWrite((uint8_t *)"Displaying message\r\n\r\n", 24);
			LCDprintf(buffer);
			DELAY;
		}
		if (inByte == '3'){
			USARTWrite((uint8_t *)"option 3 selected\r\n\r\n", 24);
			menuState = MAIN;
		}
	}



/* Menu.h -	function and variabe delcaration for the menu to be displayed on a serial port
*
*  		Copyright 2020 Graeme Judge
*		Change Log:
*				April 27, 2020: File created
*/

#include "lcd.h"	
#include <String.h>
#include "uart.h"
#include <stdlib.h>

//values for the menu states
#define MAIN 0
#define RS232 1
#define MOTOR 2
#define MOTORMOVE 3
#define LCDMENU 4
#define LEFTMOTOR 5
#define RIGHTMOTOR 6
#define STEPPERMOTOR 7
#define SERVOMOTOR 8


static char header[] = "**** MCB Test Software      ****\n\r**** Graeme Judge           ****\n\r**** Build Dtae: 04/27/2020 ****\n\r";

static char mainMenu[] = "**** Main Menu              ****\n\rPlease enter a number 1 to 3 to pick an option:\n\r1)RS232 Module\n\r2)Motor Module\n\r3)LCD Module\r\n";

static char DisplayLCDTest[] = "Displaying LCD Test Message\r\n\r\n";

static char MotorTestMenu[] = "**** Motor Test Menu        ****\n\rPlease enter a number 1 to 6 to pick an option:\n\r1)Stepper Motor\n\r2)Limit Switches\n\r3)Driving Motor\r\n4)Encoder\n\r5)Servo Motor\n\r6)Back To Main Menu\n\r";
static char MotorMoveMenu[] = "**** Motor Movement Menu    ****\n\rPlease enter a number 1 to 3 to pick an option:\n\r1)Left Motor\n\r2)Right Motor\n\r3)Back To Motor Test Menu\r\n";

static char RS232TestMenu[] = "**** RS232 Test Menu        ****\n\rPlease enter a number 1 to 4 to pick an option:\n\r1)Test Sending\n\r2)Testing Receiving\n\r3)Echo Mode\r\n4)Back to Main Menu\n\r";

static char LCDTestMenu[] = "**** LCD Test Menu          ****\n\rPlease enter a number 1 to 3 to pick an option:\n\r1)Line Test\n\r2)Display Message\n\r3)Back to Main Menu\n\r";

static char LeftMotor[] = "**** Left Motor Menu        ****\n\rPlease enter a number 1 to 3 to pick an option:\n\r1)Forwards\n\r2)Backwards\n\r3)Back To Motor Movement Menu\n\r";
static char RightMotor[] = "**** Right Motor Menu       ****\n\rPlease enter a number 1 to 3 to pick an option:\n\r1)Forwards\n\r2)Backwards\n\r3)Back To Motor Movement Menu\n\r";
static char StepperMotor[] = "**** Stepper Motor Menu     ****\n\rPlease enter a number 1 to 5 to pick an option:\n\r1)Home\n\r2)To Position\n\r3)Set Step\n\r4)Get Positioon\r\n5)Back To Motor Movement Menu\n\r";
static char StepSelect[] = "**** Step Select Menu     ****\n\rPlease enter a number 1 to 3 to pick an option:\n\r1)Half\n\r2)Full\n\r3)Back To Stepper Menu\n\r";
static char ServoMotor[] = "**** Servo Motor Menu       ****\n\rPlease enter a number 1 to 2 to pick an option:\n\r1)Set Position\n\r2)Back To Motor Test Menu\n\r";

/*
	void drawCurrentMenu;

	Draws the currently active menu on the console

	Input:  None
	Output: None
*/
void drawCurrentMenu(void);

/*
	void drawMainMenu;

	Draws the main menu on the console

	Input:  None
	Output: None
*/
void drawMainMenu(void);

/*
	void drawMotorMenu;

	Draws the motor menu on the console

	Input:  None
	Output: None
*/
void drawMotorMenu(void);

/*
	void drawMotorMoveMenu;

	Draws the motor movement menu on the console

	Input:  None
	Output: None
*/
void drawMotorMoveMenu(void);

/*
	void leftMotorMenu;

	Draws the left motor movement menu on the console

	Input:  None
	Output: None
*/
void leftMotorMenu(void);

/*
	void rightMotorMenu;

	Draws the right motor movement menu on the console

	Input:  None
	Output: None
*/
void rightMotorMenu(void);

/*
	void stepperMotorMenu;

	Draws the stepper motor movement menu on the console

	Input:  None
	Output: None
*/
void stepperMotorMenu(void);

/*
	void servoMotorMenu;

	Draws the servo motor movement menu on the console

	Input:  None
	Output: None
*/
void servoMotorMenu(void);

/*
	void drawRS232Menu;

	Draws the RS232 menu on the console

	Input:  None
	Output: None
*/
void drawRS232Menu(void);

/*
	void drawLCDMenu;

	Draws the LCD menu on the console

	Input:  None
	Output: None
*/
void drawLCDMenu(void);


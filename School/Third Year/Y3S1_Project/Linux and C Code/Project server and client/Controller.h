/* Controller.h
 * The function declaration and prototypes for Controller.c
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */


#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "Client.h"
#include "Communication.h"


#define JS_EVENT_BUTTON	0x01    // button pressed/released
#define JS_EVENT_AXIS		0x02    // joystick moved
#define JS_EVENT_INIT		0x80    // initial state of device
#define DEADZONE 		30


typedef struct JS_EVENT{
	unsigned int time;	//event timestamp in milliseconds
	short value;   	//value for the event
	unsigned char type;	//event type
	unsigned char number;	//axis/ button number
}js_event;

/* void runController(void)
 *
 * Main loop to take in controller data and pass it to the appropriate handler
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void runController();

/* void handleButton(void)
 *
 * Handles button events and performs actions based on button clicks
 *
 * Inputs:
 	int number	- The button number that was pressed
 * Outputs:
 *	None
 */
void handleButton(int number);

/* void handleJoystick(void)
 *
 * Handles joystick events and performs actions based on joystick motion
 *
 * Inputs:
 	int number	- The joystick number thats been moved
 	int16_t value	- The signed integer value of the joystick location
 * Outputs:
 *	None
 */
void handleJoystick(int number, int16_t value);

#endif


/* Communication.h
 * The function declaration and prototypes for Communication.c
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <pthread.h> 

#include "Controller.h"
#include "Client.h"

extern int dir;				//Direction variable for the camera (stepper and servo)		
extern int LRMove;				//The percent movement left and right of the left stick
extern int FBMove;				//The percent movement up and down of the left stick

/* void setUp(void)
 *
 * Sets up the thread to run in the background and do the data processig
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void setUp(void);

/* void end(void)
 *
 * Ends the running thread
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void end(void);

/* void handle(void)
 *
 * Handles and processes the data sends the commands to the server
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void handle(void);

/* void handleMotorMovement(void)
 *
 * Handles and processes the data for moving the robots main motors
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void handleMotorMovement(void);

/* void handleCameraMovement(void)
 *
 * Handles and processes the data for moving the robots camera (stepper and servo motors)
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void handleCameraMovement(void);

#endif


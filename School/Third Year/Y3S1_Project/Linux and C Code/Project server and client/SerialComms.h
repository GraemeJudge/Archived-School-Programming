/* SerialComms.c
 * The implementation of the SerialComms.h header file, handles the data coming from the nucelo and processes heartbeat requests
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#ifndef SERIALCOMMS_H
#define SERIALCOMMS_H

#include <stdio.h>  
#include <errno.h>
#include <fcntl.h> 
#include <termios.h>
#include <stdlib.h>
#include "Server.h"	

extern int readingRun;		//Variable to contorl the running of the reading loop

typedef struct DATAPASS 	//Struct to pass the needed data into the thread
{
	int socketID;
	int comPort;
}dataPass;

/* void serialPortInit(void)
 *
 * Initilizes the serial port and ensures its settings are all proper before use
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
int serialPortInit(int fd);

/* void reading(void* arg)
 *
 * Main loop to take in nucleo responses and process and send back to the client and handle the heartbeat for connection verification
 *
 * Inputs:
 	void* arg	- Struct input for to pass the serial port file descriptor and the socket descriptor for data transfer
 * Outputs:
 *	None
 */
void reading(void *arg);

#endif


/* Server.h
 * The function declaration and prototypes for the Server.c file
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#ifndef SEVER_H
#define SERVER_H


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h> 

#include "SerialComms.h"

extern char* comPort;
extern int moving;

/* void sendToClient(void)
 *
 * Sends data to the client program
 *
 * Inputs:
 	char* buffer		- Character buffer to write to the client
 	int socket		- File descriptor for the client socket
 * Outputs:
 *	None
 */
void sendToClient(char* buffer, int socket);

/* void closeComPort(void)
 *
 * Closes the given COM port
 *
 * Inputs:
 	int port		- File descriptor for the COM port to close
 	pthread_t reader	- The thread id for the serial port reader to close the thread
 * Outputs:
 *	None
 */
void closeComPort(int port,pthread_t reader);

/* void closeSocket(void)
 *
 * Closes the given socket
 *
 * Inputs:
 	int socket		- File descriptor for the socket to close
 * Outputs:
 *	None
 */
void closeSocket(int socket);

#endif


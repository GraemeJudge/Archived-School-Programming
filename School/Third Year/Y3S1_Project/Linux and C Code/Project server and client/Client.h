/* Client.h
 * The function declaration and prototypes of the Client.c file for the client connection
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#ifndef CLIENT_H
#define CLIENT_H


#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <signal.h>

#include "Controller.h"

extern int client_socket;			//Placeholder for the client socket
extern int clientRunning;			//Placeholder for the controlling variable of the main loop

char buffer[BUFSIZ];				//Buffer to hold the incoming and outgoing data for the client

/* void killClient(void)
 *
 * Ends the clients running and passes the info to the server
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void killClient(void);

/* void startClient(char* addr, int port)
 *
 * Starts the socket communication with the server
 *
 * Inputs:
 	char* addr 	- The IP address of the server to connect to
 	int port	- The port to use when connecting
 * Outputs:
 *	None
 */
void startClient(char* addr, int port);

/* void sendToServer(char* buffer)
 *
 * Sends the data in buffer to the server and reads the response back into the same variable
 *
 * Inputs:
 	char* buffer 	- The buffer to send and write back into
 * Outputs:
 *	None
 */
void sendToServer(char* buffer); 

/* void handleConnection(void)
 *
 * Displays the menu and takes the user input passing the data between the server and the client
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void handleConnection();	

/* void diosplayHelp(void)
 *
 * Prints the help dialog for the user
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void displayHelp(void);

/* void killClient(void)
 *
 * Prints the main menu for the user
 *
 * Inputs:
 	None
 * Outputs:
 *	None
 */
void displayMenu(void);

#endif



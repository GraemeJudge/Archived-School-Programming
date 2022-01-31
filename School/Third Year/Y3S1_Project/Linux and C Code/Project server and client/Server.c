/* Server.c
 * The implementation of the Server.h header file, handles the data coming from the client and processes commands from the user
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#include "Server.h"

pid_t parent;
int activeCount = 0;

int serverRunning = 1;
int processRunning = 1;

/*
 * this signal handler is used to catch the termination
 * of the child. Needed so that we can avoid wasting
 * system resources when "zombie" processes are created
 * upon exit of the child (as the parent could concievably
 * wait for the child to exit)
 */
void
SigCatcher (int n)
{
	wait3 (NULL, WNOHANG, NULL);    
	signal (SIGCHLD, SigCatcher);
}



void sendToClient(char* buffer, int socket){											//Sends data to the given client socket
	write(socket, buffer, strlen(buffer));										//Write the data to the client scoket
}

int
main (int argc, char *argv[])
{	
	pid_t parent = getpid();												//Get the parent PID
	int server_socket, client_socket;											//Place holders for the sockets
	unsigned int client_len;												//CLient length variable				
	struct sockaddr_in client_addr, server_addr;										//Sever socket struct


	if (argc != 2) {													//Ensure user put the correct number of input args
		printf ("usage: c serialPort_NUMBER\n");									//Remind the user how to use it properly
		return 1;													//Return with error code
	}

	signal (SIGCHLD, SigCatcher);												//attach a signal handler for SIGCHILD (when the child terminates)

	if ((server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0) {							//Obtain a socket for the server and ensure no errors		
		printf ("grrr, can't get the server socket\n");								//Indicate error to user
		return 1;													//Return with error code
	}

	memset (&server_addr, 0, sizeof (server_addr));									//Initialize our server address info for binding purposes
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
	server_addr.sin_port = htons (atoi(argv[1]));
	
	if (bind (server_socket, (struct sockaddr *)&server_addr, sizeof (server_addr)) < 0) {				//Attempt to bind the socket
		printf ("grrr, can't bind server socket\n");									//Print error to user
		close (server_socket);												//Ensure socket is closed
		return 2;													//Return with error code
	}

	if (listen (server_socket, 5) < 0) {											//Start listening on the socket
		printf ("grrr, can't listen on socket\n");									//Print error for user
		close (server_socket);												//Ensure the socket is closed
		return 3;													//Return with error code
	}

	printf("Server Started!\n");												//Print for user that server has successfully started		

	/*
	 * for this server, run an endless loop that will accept incoming requests from a remote client. the server will fork a child copy of itself
	 * to handle the request, and the parent will continue to listen for the next request
	 */
	 
	int serialPort = 0;													//Holds the file descriptor for the serial port
	int nextCustom = 0;													//Holder flag for the
	int invalidCount = 0;													//Placeholder for the number of invalid commands in a row
	int moving = 0;													//Placeholder for if ther client is sending movement commands
	pthread_t readerID;													//Thread id for the serial port reader
	 
	while (serverRunning) {
		client_len = sizeof (client_addr);										
		if ((client_socket = accept (server_socket, (struct sockaddr *)&client_addr, &client_len)) < 0) {		//Accept a packet from the client
			printf ("grrr, can't accept a packet from client\n");						//Print error for user
			close (server_socket);											//Ensure socket is closed
			return 4;												//Return with error code
		}

		if (fork() == 0) {												//Fork a child to handle the client
			printf("\n\n***------------------------------------------------------------***\n");			//Print for the user
			printf("New client connected, processes forked to handle incoming commands\n"); 	
			moving = 0;												//Ensure placeholder values are set to 0 at start
			nextCustom = 0;
			
			serialPort = open("/dev/ttyS0", O_RDWR);								//Open the serial port and save the file descriptor
			serialPortInit(serialPort);										//Initalize port vlaues
			
			dataPass pass;												//Set up  the struct to pass the needed data to the serial port reader
			pass.comPort = serialPort;										//Com port
			pass.socketID = client_socket;									//Client socket
			pthread_create(&readerID, NULL, (void*)reading, &pass);						//Creates the thread to run the serial reader
			
			char buffer[BUFSIZ];											//Buffer to hold and send commands with
			while(processRunning){											//While the server is processing commands
				memset(buffer, 0, BUFSIZ);									//Clear the buffer to prepare for next read 
				read (client_socket, buffer, BUFSIZ);								//Read a block of info max of BUFSIZE bytes

				//If else-if sequence to process varias commands				 
				if(nextCustom){										//Pass custom command through to the nucleo
				 	char command[64];									//Holder for command to send to nucelo
				 	int ret = snprintf(command, 64, "%s\n", buffer);					//Copy command with a newline on the end to send to nucleo
				 	if (ret < 0){										//Check for errors on the copy
				 		printf("Commanmd copy error for custom command\n");				//Inform user of errors
				 	}				
				 	write(serialPort, command, strlen(command));						//Send the data to the serial port
				 	nextCustom = 0;									//Disable the next cutom flag
				}else if(moving && strcmp(buffer, "cancel") != 0){						//Handle moving commands
				 	printf("Command: %s\n", buffer);							//Print command for the user feedback
				 	char command[64];									//Holder for the command to send to the nucleo
				 	int ret = snprintf(command, 64, "%s\n", buffer);					//Copy the command to the buffer
				 	if (ret < 0){										//Check for copy errors
				 		printf("Command copy error during moving\n");					//Indicate to the user if there are any errors
				 	}			
				 	write(serialPort, command, strlen(command));						//Write command to the serial port
				 }else if (strcmp (buffer, "send command") == 0) {						//Handle the "when" command
					printf("Recieved \"send command\" command\n");					//Print to the server to indicate the recieved command
					strcpy(buffer, "Server awaiting command...");						//Copy the response into the buffer to be sent back
					sendToClient(buffer, client_socket);							//Send the status info back to the client
					nextCustom = 1;									//Set the next custom flag
					invalidCount = 0;									//Reset the invalid commands count
				} else if (strcmp (buffer, "move robot") == 0) {						//Handle the "where" commands
					printf("Recieved \"move robot\" command\n");						//Print to the server to indicate the recieved command
					strcpy(buffer, "Awaiting movement input");						//Copy the response into the buffer to be sent back
					moving = 1;										//Set the moving flag
					sendToClient("Moving robot, use your controller\n", client_socket);			//Send status info to the client
					invalidCount = 0;									//Reset the invalid commands count
				} else if (strcmp (buffer, "close") == 0) {							//Handle the "close" command
					printf("Recieved \"close\" command\n");						//Print to the server to indicate the recieved command
					strcpy(buffer, "Closing socket");							//Copy the response into the buffer to be sent back
					sendToClient("Closing socket", client_socket);					//Send the info to the client
					close(client_socket);									//Close the client socket
					closeComPort(serialPort, readerID);							//Close the COM port
					printf("That client socket is now closed, waiting for new client to connect\n");	//Indicate the socket is closed
					return 0;										//Return from the function to end the child
				} else if (strcmp (buffer, "shutdown") == 0) {						//Handle the "shutdown" command
					printf("Recieved \"shutdown\" command\n");						//Print to the server to indicate the recieved command
					sendToClient("Shutting down server\0", client_socket);				//Send it to the client
					closeSocket(server_socket);								//Close the server socket
					closeSocket(client_socket);								//Close the client socket
					closeComPort(serialPort, readerID);							//Close the com port
					printf("client socket is now closed\n");						//Print to the server to indicate the client socket is closed
					printf("parent socket is now closed\n");						//Print to the server to indicate the server socket is closed
					kill(parent, SIGKILL);									//Kill the parent process
					return 0;										//Return from the function to end the child process
				} else if (strcmp (buffer, "cancel") == 0) {							//Cancels the moving commands
					moving = 0;										//Stops moving
					nextCustom = 0;									//Makes sure the next command wont be read as custom
					printf("canceling!\n");								//Visual indication
					sendToClient("canceling!\0", client_socket);						//Copy the response into the buffer to be sent back
				}else {											//Handle any invalid commands
					invalidCount++;									//Increment the tracking value for the number of invalids in a row
					printf("Recieved an invalid command number %d in a row\n", invalidCount);		//Print to the server to indicate the recieved command
					strcpy (buffer, "invalid command\n");							//Copies the invalid command promt into the buffer to send to the client
					sendToClient(buffer, client_socket);							//Send the invalid command info to the client
					/*
					 * Noticed in testing that if the client suddenly disconnects for some reason it floods the server with 
					 * blank commands that register as invalid commands, this will keep track of invalid commands and auto close the socket
					 * if it recieves 5 invalid commands in a row. If a valid command is recieved it resets the counter
					 */				
					if(invalidCount == 5){											//If 5 in a row
						printf("It appears the client has been disconnected so im going to close the socket\n");	//Print to server indicating the likely disconnection
						close(client_socket);										//Closes the client socket
						closeComPort(serialPort, readerID);								//Closes the com port
						kill(getpid(), SIGKILL);									//Kills the child process
					}
				}
			}
		} else {
			//this is done by parent ONLY
			if(serialPort != 0){											//Check if serial port is active
				closeComPort(serialPort, readerID);								//Close it if it was
			}
			close (client_socket);											//Ensure the client socket is closed
		}
	}
	
	if(serialPort != 0){													//Close serial port at the end of running on shut down
		closeComPort(serialPort, readerID);										//Close COM port
	}
	close (client_socket);													//Close client socket
	return 0;														//End with no error code
}


void closeComPort(int port,pthread_t reader){
	readingRun = 0;													//Set the flagf to stop the serial port reading
	write(port, "disconnect\n", strlen("disconnect\n"));									//Tell the nucleo were disconnecting
	pthread_join(reader, NULL);												//Join the thread to end it
	if(port != 0){														//If the port exsists
		close(port);													//Close the port
		printf("closed serialPort\n");										//Print status info for the user
	}
	readingRun = 1;													//Reset the reading flag for next time
}

void closeSocket(int socket){
	close(socket);														//Close the socket
}



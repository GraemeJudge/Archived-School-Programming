/* Client.c
 * The implementation of the Client.h header file and the main menu and data handling for the client connection
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */
#include "Client.h"


int client_socket;												//Global variable to hold the client socket
int clientRunning = 1;												//Global variable to indicate if the client is running

void killClient(void){												//Deal with violent deaths
	printf("\nreceived SIGINT, killing client\n");							//Indicate to the user that the signal was recieved
	char buffer[64];											//Buffer to hold error message to send to the server
	strcpy(buffer, "close");										//Message for the server indicating the soicket should be closed
	clientRunning = 0;											//Stop running loop of the clien
	sendToServer(buffer);											//Send the message to the server			
	close (client_socket);											//Close the socket
	printf ("Client is finished\n");									//Indicates the client is now finished
	exit(0);												//Exits
}

void sendToServer(char* buffer){
	int len = 0;
	write(client_socket, buffer, strlen (buffer));							//Send the close socket command to the server
	len = read (client_socket, buffer, BUFSIZ);								//Read the response
	buffer[len] = '\0';											//Set the end of the read in string to a null terminator
}

void startClient(char* addr, int port){	

	struct sockaddr_in server_addr;	

	if ((client_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0) {					//Get a socket for communications
		printf ("grrr, can't get a client socket!\n");						//Print statement to display error
		return;											//Exit
	}	

	memset (&server_addr, 0, sizeof (server_addr));							//Initialize struct to get a socket to host
	server_addr.sin_addr.s_addr = inet_addr(addr);
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons (port);
	
	if (connect (client_socket, (struct sockaddr *)&server_addr, sizeof (server_addr)) < 0) {		//Attempt a connection to the created server
		printf ("grrr, can't connet to server!\n");							//Print to display error
		close (client_socket);										//Ensure the socket is closed before ending
		return;											//Exit
	}

	handleConnection();											//Display the menu and promt the user for input

	close (client_socket);											//Close the socket
	printf ("Client is finished\n");									//Indicates the client is now finished
}	


void handleConnection(void){
	while(clientRunning){											//Will continue to run in a loop allowing the user to keep sending commands	
		
		displayMenu();
		
		fflush (stdout);										//Flushes the stdout
		fgets (buffer, sizeof (buffer), stdin);							//Gets the string input from the terminal window
		
		if (buffer[strlen (buffer) - 1] == '\n'){							//If the last character was a newline
			buffer[strlen (buffer) - 1] = '\0';							//Change it to a null terminator
		}
		
		if(strcmp(buffer, "help") == 0){								//If the command was help it prints the help dialog
			displayHelp();
		}else if(strcmp(buffer, "shutdown") == 0){							//If the command was shutdown
			sendToServer((char*)buffer);								//Send the command to the server
			printf ("Shutting down! bye!\n");
			break;
		}else if(strcmp(buffer, "exit") == 0){							//If the command was exit								
			int err = snprintf(buffer, 64, "close");						//Copy the comamnd into the buffer
			if(err < 0){										//Check to make sure there were no errors
				printf("error copying the exit command\n");					//Indicate to the user if there was
			}								
			sendToServer((char*)buffer);								//Send the command to the server and get the response
			printf ("Exiting leaving the server running\n");					//Print the results
			break;
		}else if(strcmp(buffer, "move robot") == 0){							//If the command was exit
			sendToServer((char *)buffer);								//Send the command to the server					
			printf("Use the left analog stick to move the robot\n");				//Controls overview when it starts
			printf("The use the right analog stick to move the camera\n");
			printf("Use the select button to home the camera\n");
			printf("Use the start button to cancel and return to the main menu\n");
			fflush(stdout);
			runController();									//Run loop for reading and sending the controller data
			fflush(stdout);
		}else if(strcmp(buffer, "send command") == 0){
			sendToServer((char *)buffer);								//Send the command to the server and get the response
			printf ("Result of command:\n  %s\n\n", buffer);					
			printf("Enter command:\n");								//Prompt to enter the command
			fflush (stdout);									//Flushes the stdout
			fgets (buffer, sizeof (buffer), stdin);						//Gets the string input from the terminal window
			if (buffer[strlen (buffer) - 1] == '\n'){						//If the last character was a newline
				buffer[strlen (buffer) - 1] = '\0';						//Change it to a null terminator
			}
			sendToServer((char *)buffer);
			printf ("Result of custom command:\n  %s\n\n", buffer);
		}else{
			printf ("Invalid command:\n");
		}
		printf("Press enter to return to the main menu\n");						//promt the user to press senter to return to the menu
		getchar();											//Wait for enter
	}
}


void displayHelp(void){
	printf("\n***-----***\n");
	printf("Help dialog:\n");
	printf("  Before sending a command please ensure the server is running\n");
	printf("  To send a command to there server simply type the command and hit enter, \n");
	printf("  The response will be displayed when it is receieved and then a promt will be displayed to return to the main menu\n");
	printf("  To use the move robot command ensure the controller is plugged in and follow the promts, to exit the robot moving hit 'start'\n");
	printf("  The \"exit\" command will close the socket connection and end this program leaving the server running\n");
	printf("  The \"shutdown\" command will close the socket connection and end this program shutting down the server\n");
}

void displayMenu(void){
	system("@cls||clear");										//Clears the terminal window for readability		
	printf ("Please enter one of the following commands to send to the server:\n");		//Promts the user to enter a command
	printf("  move robot\n");									//Option for moving the robot using the game controller
	printf("  send command\n");									//Send a custom command
	printf("  exit\n");										//Exit the client leaving the server intact
	printf("  shutdown\n");									//Shutdown the client and the server
	printf("  help\n\n");										//Display the help dialog
}


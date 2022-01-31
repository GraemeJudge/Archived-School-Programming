/* ClientMain.c
 * The mainline for the client, it starts the client and handles any kill signals it recieves
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#include "Client.h"

void
SigCatcher (int n) {							//Signal handler
	killClient();							//Kills the client process
}


int main(int argc, char *argv[]){					//Main
	if (argc != 3) {						//Ensure the correct number of arguements are passed in
		printf ("usage: c IP_ADDRESS PORT_NUMBER\n");		//Promt to remind the user of the correct usage
		return 1;
	}
	
	signal (SIGINT, SigCatcher);					//Attach signal handler
	
	printf("starting client\n");					//Indicate the client is starting (client menu clears screen so this will likely never been seen)
	
	startClient(argv[1], atoi(argv[2]));				//Starts the client with the given input arguments
	
	return 0;
}

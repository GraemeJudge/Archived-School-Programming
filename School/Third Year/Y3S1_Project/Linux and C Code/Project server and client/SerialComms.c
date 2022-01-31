/* SerialComms.c
 * The implementation of the SerialComms.h header file, handles the data coming from the nucelo and processes heartbeat requests
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#include "SerialComms.h"

int readingRun = 1;

int serialPortInit(int fd){
	struct termios tty;
	if (tcgetattr (fd, &tty) != 0)
	{
	        printf ("error %d from tcgetattr", errno);
	        return -1;
	}

	cfsetospeed (&tty, B9600);				//Output speed 9600 baud
	cfsetispeed (&tty, B9600);				//Input speed 9600 baud

	tty.c_cflag = (tty.c_cflag & ~CSIZE) | CS8;     	// 8-bit chars
	
	tty.c_iflag = IGNBRK;     				//Disable break processing
	tty.c_lflag = ICANON;         			//No signaling chars, no echo,
			                			//No canonical processing
	tty.c_oflag = 0;               			//No remapping, no delays
	tty.c_cc[VMIN]  = 0;           			//Read doesn't block
	tty.c_cc[VTIME] = 5;           			//0.5 seconds read timeout

	tty.c_iflag &= ~(IXON | IXOFF | IXANY); 		//Shut off xon/xoff ctrl

	tty.c_cflag |= (CLOCAL | CREAD);			//Ignore modem controls,
	                                			//Enable reading
	tty.c_cflag &= ~(PARENB | PARODD);      		//Shut off parity
	tty.c_cflag |= 0;
	tty.c_cflag &= ~CSTOPB;				//Only 1 stop bit
	tty.c_cflag &= ~CRTSCTS;				//Disable rts and cts flow control

	if (tcsetattr (fd, TCSANOW, &tty) != 0)		//Set the data to the COM port and check for errors
	{				
	        printf("error %d from tcsetattr", errno);	//Print error to user
	        return -1;					//Return with error code
	}
	return 0;						//End of setup
}



void reading(void *arg){

	dataPass *data = arg;												//DataPass sturct to hold the COM port and socket information for sending data

	int port = data->comPort;											//Save the com port file descriptor into a easy to use variable
	int count = 0;													//Count variable to hold the number of bytes being read in
	char buffer[64];												//Buffer to hold the commands to send
	char response[64];												//Buffer to hold the response from the nucleo
	
	while(readingRun){												//While running
		memset(buffer, 0, 64);											//Clear the buffer before the next use
		count += read(port, buffer, 64);									//Read the data from the port into the buffer and count the number of bytes
		
		if(buffer[count - 1] == '\n'){									//If the last chaarcter read in was a new line process it
			if(strcmp(buffer, "heartbeat\n") == 0){							//If the nucleo was sending the heartbeat to ensure connection
				write(port, "pulse\n", strlen("pulse\n"));						//Return the pulse to the nucleo and dont say anything to the user
				count = 0;										//Reset the count variable
			}else{
				//printf("Recieved from the nucleo: %s\n", buffer);					//Debug print line to view all incoming messages from the nucleo
				int check = snprintf(response, 64, "Response from Nucleo:\n\t%s\n", buffer);		//Copy the respone into the buffer to send to the user
				if(check < 0){										//Checlk for errors
					printf("Copy error in the serial communication response!\n");		//Indicate to the user there was an error
				}
					sendToClient(response, data->socketID);					//Send the response back to the client
					count = 0;									//Reset the count variable
			}
		}
	}
	printf("Ending serial port reading\n");									//Print to indicate the end of the serial port reading
}


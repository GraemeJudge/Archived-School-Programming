/* Communication.c
 * The implementation of Communication.h, handles the processing of the controller axis to the commands needed to control the robot (motors and camera)
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */
 
#include "Communication.h"

pthread_t tid[1];							//An array to hold the id's assinged to each thread to allow it to be joined later	
int dir = 0;								// 0 = not moving, 1 = stepper left, 2 = stepper right, 3 = servo up, 4 = servo down

int LRMove = 0;							//The left and right movement variable as a percentage of the left stick
int FBMove = 0;							//The up and down movement variable as a percentage of the left stick

int lastLR = 0;							//Holds the last value to make it only send updates when the datas been changed
int lastFB = 0;							//Holds the last value to make it only send updates when the datas been changed

int tRunning = 1;							//If the thread is running handling the movements						
int angle = 0;								//Keeps track of the angle to ensure the camera does not exced its limits							
int angleStep = 5;							//The step amount of the servo angle (5 degrees)

void delay(){
	usleep(0.15 * 1000000); 					//0.15 seconds delay
}

void setUp(void){
	tRunning = 1;							//Ensure the running state is set again
	pthread_create(&tid[0], NULL, (void *)handle, NULL);		//Create the thread to run in the background and process and send the data as the controller is moved
	pthread_detach(tid[0]);					//Detach the thread so it runs in the back ground and isnt noticed
}

void end(void){			
	tRunning = 0;							//Stop the threads running loop
	pthread_join(tid[0], NULL);					//Join the thread when it ends
}

void handle(void){
	while (tRunning) {						//While running
			handleCameraMovement();			//Check and handle the servo/ stepper movements
			handleMotorMovement();				//Check and handle the motor movements
	}
}	

void handleMotorMovement(){
	char buffer[BUFSIZ];						//Empty buffer to use for sending and recieving data from
	int leftSpeed;							//Integer to set the left wheels speed to
	int rightSpeed;						//Integer to set the right wheels speed to
	
	if(LRMove != lastLR || FBMove != lastFB){			//Ensure a value has changed
		leftSpeed = -FBMove + LRMove;				//Calculate the left wheel speed
		rightSpeed = -FBMove - LRMove;			//Calculate the right wheel speed
		
		leftSpeed = (abs(leftSpeed) > 100 ? leftSpeed + ((leftSpeed/abs(leftSpeed))*(100 - abs(leftSpeed))) : leftSpeed);		//Ensure the left wheel is within the -100 to 100 value range
		rightSpeed = (abs(rightSpeed) > 100 ? rightSpeed + ((rightSpeed/abs(rightSpeed))*(100-abs(rightSpeed))) : rightSpeed);	//Ensure the right wheel is within the -100 to 100 value range
		
		int ret = snprintf(buffer, 64, "set motors %04d %04d",leftSpeed, rightSpeed);						//Copy the command to the buffer to send
		if(ret < 0){						//Ensure the copy was successful
			printf("copy error in motor movement\n");	//Print error message if it was not succesful
		}	
		sendToServer(buffer);					//Send the command to the server
		lastLR = LRMove;					//Set the last value to the current value in preperation of the next loop
		lastFB = FBMove;					//Set the last value to the current value in preperation of the next loop
		delay();						//Short delay to ensure enough time for the command to be sent without overflowing the UART port
	}	
}


void handleCameraMovement(){
	char buffer[BUFSIZ];						//Empty buffer to use for sending and recieving data from
	if(dir == 1){							//Stepping forward on the stepper
		strcpy(buffer, "forward step");			//Copy the command to the buffer
		sendToServer(buffer);					//Send the command to the server
		delay();						//Short delay to ensure enough time for the command to be sent without overflowing the UART port
	}else if(dir == 2){						//Stepping backwards on the stepper
		strcpy(buffer, "backward step");			//Copy the command to the buffer
		sendToServer(buffer);					//Send the command to the server
		delay();						//Short delay to ensure enough time for the command to be sent without overflowing the UART port
	}else if(dir == 3){						//Moving the servo down
		if(angle > -90){					//Ensure angle is not past limit
			angle -= angleStep;				//Subtract the step from the servo angle
			sprintf(buffer, "servo move %d", angle);	//Copy the command to the buffer to send
			sendToServer(buffer);				//Send the command to the server
			delay();					//Short delay to ensure enough time for the command to be sent without overflowing the UART port
		}
	}else if(dir == 4){						//Moving the servo up
		if(angle < 90){					//Ensure angle is not past the limit 
			angle += angleStep;				//Add the step to the servo angle
			sprintf(buffer, "servo move %d", angle);	//Copy the command to the buffer
			sendToServer(buffer);				//Send the command to the server
			delay();					//Short delay to ensure enough time for the command to be sent without overflowing the UART port
		}		
	}			
}

/* Controller.c
 * The implementation of Controller.h, handles the reading and processing of the controller data (axis and buttons)
 * passing the needed information to the comnmunications module to be processed and sent to the sever
 * By: Graeme, Sean, and Viktor
 * December 5, 2020
 */

#include "Controller.h"

int running = 1;												//Variable to control the running of controller reading

void runController(){												//Main loop for reading and processing controller data
	int fd = open ("/dev/input/js2", O_RDONLY);								//Opening the device to be used
 	running = 1;												//Ensureing the loop is ready to run
 	setUp();												//Set up the communications set up to handle the controller data
 	
	if( fd < 0){												//Ensure device was opened successfully 
		printf("cannot open the controller device\n");						//Print to inform user of any errors
		running = 0;											//No longer wish to run since the controller isnt open
 	}
 	
	while(running){											//While running
		js_event event;										//Struct to hold the controller event
		read(fd, &event, sizeof(event)); 								//Read the data from the controller	
			if( event.type == JS_EVENT_BUTTON ){ 							//If the event is a button
				if(event.value == 0){								//Registering on button release
					handleButton(event.number);						//Handle the button actions
				}
			}else if(event.type == JS_EVENT_AXIS){ 						//If the event is an axis
				handleJoystick((int)event.number, event.value);				//Handle the axis actions
			}		
		}
		
	end();													//End the communications running
	close(fd);												//Close the controller device
}

void handleButton(int number){		
	char comBuf[BUFSIZ]; 											//Buffer to hold the outgoing commands
	switch(number){											//Switch statement for button actions
		case 6:											//Select button "home camera" command
			strcpy(comBuf, "home camera");							//Copy home camera command into the buffer
			sendToServer(comBuf);									//Send command buffer to the server
			break;											//Break the switch case
		case 7:											//Start button "cancel" command
			running = 0;										//Stop the running of the loop
			dir = 0;										//Clear the moving direction for the stepper and servo
			strcpy(comBuf, "cancel");								//Copy the cancel command into the buffer
			sendToServer(comBuf);									//Send the buffer to the server to cancel the sending of controller data to the server
			break;											//Break the switch case
		default:											//Default case for any other possible button pushes
			break;											//Break the default case
	}
}

void handleJoystick(int number, int16_t value){
	int percent;												//Integer representation of the axis movement as a percentage
	
	if(value > 0){												//Positive side of the axis
		percent = (int)(((double)(value) / 0x7FFF) * 100);						//Get percentage
	}else{													//Negitive side of axis
		percent = (int)(((double)(value) / 0x7FFF) * 100);						//Get percentage
	}
	
	switch(number){ 											//Switch statement for the axis movements
		case 0:											//Left stick, left and right movements						
			if(percent > DEADZONE || percent < -DEADZONE){					//Deadzone to not register in 
				LRMove = percent;								//Set the left and right movement variable to the percentage
			}else{
				LRMove = 0;									//Set the left and right movement variable to 0 (within deadzone)
			}
			break;											//Break switch case
		case 1: 											//Left stick, up and down movements
			if(percent > DEADZONE || percent < -DEADZONE){					//Deadzone to not register in 
				FBMove = percent;								//Set the up and down movement variable to the percentage
			}else{
				FBMove = 0;									//Set the up and down movement variable to 0 (within deadzone)
			}
			break;											//Break switch cases
		case 3:											//Right stick, left and right movements
			if(percent > DEADZONE){								//Deadzone to not register in 
				dir = 1;									//Set the servo/stepper direction control to 1
			}else if (percent < -DEADZONE){							//Deadzone to not register in 
				dir = 2;									//Set the servo/stepper direction control to 2
			}else if (dir == 1 || dir == 2){
				dir = 0;									//Set the servo/stepper direction control to 0 (not moving)
			}
			break;
		case 4:											//Right stick, up and down movements			
			if(percent > DEADZONE){								//Deadzone to not register in 
				dir = 3;									//Set the servo/stepper direction control to 3
			}else if (percent < -DEADZONE){							//Deadzone to not register in 
				dir = 4;									//Set the servo/stepper direction control to 4
			}else if (dir == 3 || dir == 4){
				dir = 0;									//Set the servo/stepper direction control to 0 (not moving)
			}				
			break;
	}
}


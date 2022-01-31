#include "Commands.h"


#define test "test"
#define LEDON "led on"
#define LEDOFF "led off"
#define LEDTOGGLE "led toggle"

#define FSTEP "forward step"
#define BSTEP "backward step"

#define HOMECAMERA "home camera"
#define SERVOMOVE "servo move "

#define RIGHTMOTORSPEED "right motor speed "
#define LEFTMOTORSPEED "left motor speed "
#define SETMOTORS "set motors "

#define PULSE "pulse"

#define DISCONNECT "disconnect"

void process(){	
	char* command = (char*)commandBuffer;
	uint8_t length = rx_Counter - 1;
	
	if(1){																																			//for debugging
		printf("Command: %sLength: \"%d\"\n", command, length);
	}
	if(length == 0){																														//Blank commands previously made every command run so this fixes it
		memset(commandBuffer, 0, BufferSize);																			//Clear the bufer for the next command
		rx_Counter = 0;	
		return;
	}else if(strncmp((char*)command, (char*)LEDON, length) == 0){								//Turn on the green onboard led
		Green_LED_On();
		printf("LED on\n");
		responded = 1;
	}else	if(strncmp((char*)command, (char*)LEDOFF, length) == 0 ){							//Turn off the green onboard led
		Green_LED_Off();
		printf("LED Off\n");
		responded = 1;
	}else if(strncmp((char*)command, (char*)LEDTOGGLE, length) == 0){						//Toggle the green onboard led
		Green_LED_Toggle();
		printf("LED Toggled\n");
		responded = 1;
	}else	if(strncmp((char*)command, (char*)FSTEP, length) == 0){								//Step the stepper motor forwards
		step(-2);
		printf("Stepped Forward\n");
		responded = 1;
	}else if(strncmp((char*)command, (char*)BSTEP, length) == 0){								//Step the stepper motor backwards
		step(2);
		printf("Stepped Backward\n");
		responded = 1;
	}else	if(strncmp((char*)command, (char*)SERVOMOVE, 11) == 0){								//Move the servo to specific angle
		char buff[3];
		memcpy(buff, &command[11], 3);
		printf("Moving Servo to %d Degrees\n", atoi(buff));
		setServo(atoi(buff));
		responded = 1;
	}else if(strncmp((char*)command, (char*)HOMECAMERA, length) == 0){					//Homing the camera
		responded = 1;
		homeCamera();
		printf("Homing Camera\n");
	}else if(strncmp((char*)command, (char*)SETMOTORS, 11) == 0){								//Setting both motors speeds
		char left[5];
		memcpy(left, &command[11], 4);
		left[4] = '\0';
		int lspeed = atoi(left);
		
		char right[5];
		memcpy(right,&command[16], 4);
		right[4] = '\0';
		int rspeed = atoi(right);
		
		printf("Right motor speed %d\nLeft motor speed %d\n", rspeed,lspeed);
		rightMotorSpeed(rspeed);
		leftMotorSpeed(lspeed);
		responded = 1;
	}else	if(strncmp((char*)command, (char*)RIGHTMOTORSPEED, 18) == 0){					//Right motor speed
		char buff[4];
		memcpy(buff, &command[18], 4);
		int speed = atoi(buff);
		printf("Right motor speed %d\n", speed);
		rightMotorSpeed(speed);
		responded = 1;
	} else if(strncmp((char*)command, (char*)LEFTMOTORSPEED, 17) == 0){					//Left motor speed
		char buff[4];
		memcpy(buff, &command[17], 4);
		int speed = atoi(buff);
		printf("Left motor speed %d\n",speed);
		leftMotorSpeed(speed);
		responded = 1;
	}else if(strncmp((char*)command, (char*)DISCONNECT, length) == 0){					//Disconnect
		printf("Disconnecting from nucleo\n");
		disconnect();
		responded = -1;
	}else if(strncmp((char*)command, (char*)PULSE, length) == 0){								//Heartbeat reponse
		responded = 1;
		Green_LED_On();
	}else{
		responded = 1;
		printf("Invalid Command\n");
	}
	
	memset(commandBuffer, 0, BufferSize);																				//clear the bufer for the next command
	rx_Counter = 0;			
}


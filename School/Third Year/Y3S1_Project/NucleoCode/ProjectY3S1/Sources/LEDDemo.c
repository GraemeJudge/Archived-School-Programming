#include "LED.h"
#include "UART.h"
#include "LEDDemo.h"
#include <stdio.h>

void UARTLEDDemo(){

		printf("Give Green LED control input (Y = On, N = off):\n");
		char rxByte = getchar();

		if (rxByte == 'N' || rxByte == 'n'){
			Green_LED_Off();
			printf("   LED: OFF\n\n");
		}
		else if (rxByte == 'Y' || rxByte == 'y'){
			Green_LED_On();
			printf("   LED: ON\n\n");
		}

		
}


/* uart.c-	Implementation of the uart.h file
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			January 23, 2020: Source file created
*				January 28, 2020: usartGpioInit created and bugs fixed
*/

#include "uart.h"
#include "stm32l476xx.h"
#include "SysClock.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdint.h>



//text book page 534
void uartInit(){
		usartGpioInit();

	//using usart 1
	//9600 baud
	//no parity
	//8 data bits
	//1 stop bit
	//no flow control
	
	//disabling the usart (UE)
	USART1 -> CR1 &= ~(uint32_t)0x00000001;
	
	//set data length to 8 bits
	//00 is 8 bits, 01 is 9 bits, 10 is 7 bits
	//M0 and M1 (bit 12 and bit 28
	USART1 -> CR1 &= ~(uint32_t)0x10001000;
	
	//1 stop bit (IN CR2)
	//00 = 1
	//01 = 0.5
	//10 = 2
	//11 = 1.5
	//bit 12 and 13
	USART1 -> CR2 &= ~(uint32_t)0x00003000;
	
	//parity
	//0 is no parity
	//1 means parity is enabled (use ps to set even or odd)
	//PCE bit 10
	USART1 -> CR1 &= ~(uint32_t)0x00000400;
	
	//oversampling  -  over8 (0 = over sampling by 16, 1 = over sampling by 16)
	USART1 -> CR1 &= ~(uint32_t)0x00008000;
	
	
	//baud rate  -  BRR  (section 22.1.2)
	USART1 -> BRR = 0X208d;
	
	
	//enable transmission and recieveing (TE and RE)
	USART1 ->CR1 |= (uint32_t)0x0000000C;
	
	
	//enable the usart (UE)
	USART1 -> CR1 |= USART_CR1_UE;;
	
	//check text for this point onwards
	//check make sure the usart is ready for transmission
	while((USART1->ISR & USART_ISR_TEACK) == 0);
	//check make sure the usart is ready to recieve
	while((USART1->ISR & USART_ISR_REACK) == 0);
}

void usartGpioInit(){
	//TEXTBOOK PAGE 535
	//initalize the gpio port and usart clock to be used when transmitting data
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOBEN;
	
	GPIOB -> MODER &= ~(0xF << (2*6));
	GPIOB -> MODER |= 0xA << (2*6);
	
	GPIOB -> AFR[0] |= 0x77 << (4*6);
	
	GPIOB -> OSPEEDR |= 0xF<<(2*6);
	
	GPIOB -> PUPDR &= ~(0xF << (2*6));
	GPIOB -> PUPDR |= 0x5<<(2*6);
	
	GPIOB -> OTYPER &= ~(0x3<<6);
	
	RCC -> APB2ENR |= RCC_APB2ENR_USART1EN;
	
	RCC -> CCIPR &= ~(RCC_CCIPR_USART1SEL);
	RCC -> CCIPR |= (RCC_CCIPR_USART1SEL_0);	
}


void uartPrintf(char *fmt, ...) {
	va_list myArgs;

	char buffer[MAX_BUFFER_SIZE];
	
	va_start(myArgs, fmt);
	vsnprintf(buffer,MAX_BUFFER_SIZE, fmt, myArgs);
	va_end(myArgs);
	
	uartPutS(buffer);
}


void uartPutC(char c){
	while(!(USART1->ISR & USART_ISR_TXE)); //wait for the port to be ready to send
		
	USART1-> TDR = (uint8_t)c;

}


void uartPutS(char *str){
	
		while(*str){
			uartPutC(*str++);
		}
	
}


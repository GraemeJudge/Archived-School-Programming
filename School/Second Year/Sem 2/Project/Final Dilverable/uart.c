/* uart.c-	Implementation of the uart.h file
*
*  		Copyright 2020 Graeme Judge, Sean Berkvens
*		Change Log:
*  			January 23, 2020: Source file created
*				January 28, 2020: usartGpioInit created and bugs fixed
*				April 27, 2020: Added functionality for using virtual serial port
*/

#include "uart.h"
#include "SysClock.h"
#include <String.h>



//text book page 534
void uartInit(){
		RCC->APB1ENR1 |= RCC_APB1ENR1_USART2EN;  // Enable USART 2 clock		
	// Select the USART1 clock source
	// 00: PCLK selected as USART2 clock
	// 01: System clock (SYSCLK) selected as USART2 clock
	// 10: HSI16 clock selected as USART2 clock
	// 11: LSE clock selected as USART2 clock
	RCC->CCIPR &= ~RCC_CCIPR_USART2SEL;
	RCC->CCIPR |=  RCC_CCIPR_USART2SEL_0;
	
		usartGpioInit();
	//using usart 1
	//9600 baud
	//no parity
	//8 data bits
	//1 stop bit
	//no flow control
	//disabling the usart (UE)
	USART2 -> CR1 &= ~USART_CR1_UE;
	//set data length to 8 bits
	//00 is 8 bits, 01 is 9 bits, 10 is 7 bits
	//M0 and M1 (bit 12 and bit 28
	USART2 -> CR1 &= ~USART_CR1_M;
	//oversampling  -  over8 (0 = over sampling by 16, 1 = over sampling by 16)
	USART2 -> CR1 &= ~USART_CR1_OVER8;	
	//1 stop bit (IN CR2)
	//00 = 1
	//01 = 0.5
	//10 = 2
	//11 = 1.5
	//bit 12 and 13
	USART2 -> CR2 &= ~USART_CR2_STOP;
	//baud rate  -  BRR  (section 22.1.2)
	USART2 -> BRR = 0X208d;	
	
	USART2->CR1  |= (USART_CR1_RE | USART_CR1_TE);  	// Transmitter and Receiver enable
	
	USART2->ICR |= USART_ICR_TCCF;
	USART1->CR3 |= USART_CR3_DMAT | USART_CR3_DMAR;
	
	USART2->CR1  |= USART_CR1_UE; // USART enable   
		
	
	//check text for this point onwards
	//check make sure the usart is ready for transmission
	while((USART2->ISR & USART_ISR_TEACK) == 0);
	//check make sure the usart is ready to recieve
	while((USART2->ISR & USART_ISR_REACK) == 0);
}

void usartGpioInit(){
	//TEXTBOOK PAGE 535
	//initalize the gpio port and usart clock to be used when transmitting data
	RCC->AHB2ENR |=   RCC_AHB2ENR_GPIODEN;
	
	// ********************** USART 2 ***************************
	// PD5 = USART2_TX (AF7)
	// PD6 = USART2_RX (AF7)
	// Alternate function, High Speed, Push pull, Pull up
	// **********************************************************
	// Input(00), Output(01), AlterFunc(10), Analog(11)
	GPIOD->MODER   &= ~(0xF << (2*5));	// Clear bits
	GPIOD->MODER   |=   0xA << (2*5);      		
	GPIOD->AFR[0]  |=   0x77<< (4*5);       	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	GPIOD->OSPEEDR |=   0xF<<(2*5); 					 	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOD->PUPDR   &= ~(0xF<<(2*5));
	GPIOD->PUPDR   |=   0x5<<(2*5);    				
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	GPIOD->OTYPER  &=  ~(0x3<<5) ;  
}


void uartPrintf(char *fmt, ...) {
	va_list myArgs;

	char buffer[MAX_BUFFER_SIZE];
	
	va_start(myArgs, fmt);
	vsnprintf(buffer,MAX_BUFFER_SIZE, fmt, myArgs);
	va_end(myArgs);
	
	uartPutS(buffer);
}


void USARTWrite(uint8_t *buffer, uint32_t nBytes){
		int i;
	// TXE is cleared by a write to the USART_DR register.
	// TXE is set by hardware when the content of the TDR 
	// register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++) {
		while (!(USART2->ISR & USART_ISR_TXE));   	// wait until TXE (TX empty) bit is set
		// Writing USART_DR automatically clears the TXE flag 	
		USART2->TDR = buffer[i] & 0xFF;
		USART_Delay(300);
	}
	while (!(USART2->ISR & USART_ISR_TC));   		  // wait until TC bit is set
	USART2->ISR &= ~USART_ISR_TC;
}


void USART_Delay(uint32_t us) {
	uint32_t time = 100*us/7;    
	while(--time);   
}


uint8_t USART_Read (USART_TypeDef * USARTx) {
	// SR_RXNE (Read data register not empty) bit is set by hardware
	while (!(USARTx->ISR & USART_ISR_RXNE));  // Wait until RXNE (RX not empty) bit is set
	// USART resets the RXNE flag automatically after reading DR
	return ((uint8_t)(USARTx->RDR & 0xFF));
	// Reading USART_DR automatically clears the RXNE flag 
}

void USART_Read_String(char* buffer, int nbytes){
	int counter = 0;
	while(1){
			char byte;
			byte = USART_Read(USART2);
		if(byte == 13){
			return;
		}
			//sprintf((char *)buffer, (char *)byte, 1);
				strncat(buffer, &byte, 1);
		
		counter++;
		if(counter == nbytes){
			return;
		}
	}
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


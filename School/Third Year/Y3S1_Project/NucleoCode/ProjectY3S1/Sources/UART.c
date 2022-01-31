#include "UART.h"
#include "utils.h"
#include "LED.h"
#include "Commands.h"

// Derived from Zhu's Virtual Serial Port demo code
// USART2 connected to ST Link on Nucleo-64 STM32F303RE
//  WPS 30 Apr 2020

// to do
//	- clear comms errors while waiting to read 
//	- clean-up header
//	- tighten structure & eliminate scrap code


// UART Ports:
// ===================================================
// PA.2 = USART2_TX (AF7)  |  PA.3 = USART2_RX (AF7)

//volatile uint32_t rx_Counter = 0;					//points the the current location in the buffer
//uint8_t commandBuffer[BufferSize];				//buffer to hold incoming commands

volatile uint32_t rx_Counter = 0;
uint8_t commandBuffer[BufferSize];	

void UART2_Init(void){
	//Set the USART 2 clock to the system clock (72Mhz)
	FORCE_BITS( RCC->CFGR3, RCC_CFGR3_USART2SW, RCC_CFGR3_USART2SW_SYSCLK );	
	
	//Init the gpio port for the usart (GPIOA)
	UART2_GPIO_Init();																		
	
	//Disable usart2 to set it up
	CLR_BITS(USART2->CR1, USART_CR1_UE);
	//Enable USART 2 clock	
	RCC->APB1ENR |= RCC_APB1ENR_USART2EN ; 									
	//Set data length to 8
	CLR_BITS(USART2->CR1, USART_CR1_M);			
	//Set stop bits
	CLR_BITS(USART2->CR2, USART_CR2_STOP);								
	//Set parity to none
	CLR_BITS(USART2->CR1, USART_CR1_PCE);								
	//Set oversampling to 16
	CLR_BITS(USART2->CR1, USART_CR1_OVER8);								
	//Set baud rate to 9600 (72Mhz + OVER8)/9600 = 7500
	SET_BITS(USART2->BRR, SystemCoreClock/BAUD_RATE);												
	//Enable sending and recieving
	SET_BITS(USART2->CR1, (USART_CR1_TE | USART_CR1_RE));	
	//Enable USART
	SET_BITS(USART2->CR1, USART_CR1_UE);									
	//Set interrupt for recieving
	SET_BITS(USART2->CR1, USART_CR1_RXNEIE);
	//SET_BITS(USART2->CR1, USART_CR1_TXEIE);
	
	NVIC_SetPriority(USART2_IRQn, 0);			// Set Priority to 0
	NVIC_EnableIRQ(USART2_IRQn);					// Enable interrupt of USART2 peripheral

	
	//wait for readiness
	while ( (USART2->ISR & USART_ISR_TEACK) == 0);//Verify that the USART is ready for reception
	while ( (USART2->ISR & USART_ISR_REACK) == 0);//Verify that the USART is ready for transmission
	
	printf("\n    Embedded Nucleo Target USART Port");
	printf("\n**--------------------------------------**");
	printf("\nUSART Running with Interrupts on Recieving\n");
}

// ********************** USART 2 ***************************
// PA.2 = USART2_TX (AF7)
// PA.3 = USART2_RX (AF7)
// Alternate function (01), High Speed, Push pull, Pull up
// **********************************************************
void UART2_GPIO_Init(void) {
	// Enable the peripheral clock of GPIO Port
	RCC->AHBENR |=   RCC_AHBENR_GPIOAEN;
	//Input(00), Output(01), AlterFunc(10), Analog(11)
	SET_BITS(GPIOA->MODER, 10UL<<2 * 2);  	
	//Select alternate function 7 for pin 2 and 3
	SET_BITS(GPIOA->AFR[0], 0x77 << 4 * 2);
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)				 	
	SET_BITS(GPIOA->OSPEEDR, 0xF << 2*2);
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
	SET_BITS(GPIOA->OTYPER, 0x0 << 2*2);
	// GPIO Push-Pull: No pull-x (00), Pull-up (01), Pull-down (10), Reserved (11)	
	SET_BITS(GPIOA->PUPDR, 0x5 << 2*2); 
}

uint8_t USART_Read_Byte (USART_TypeDef * USARTx) {
	volatile uint8_t RxByte;
	// ISR_RXNE (Read data register not empty) bit is set by hardware
	// need to check for comm error and clear here inside wait loop
	while (!(USARTx->ISR & USART_ISR_RXNE)){}  // Wait until RXNE (RX not empty) bit is set
	// Reading USART RDR automatically clears the RXNE flag 		
	// !!!!! KLUDGE !!!!! virtual com port was sending ASCII with msb always set
	//                    mask-off with 0x7F to get valid characters
		RxByte = (uint8_t)(USARTx->RDR) & 0x7F;
		return (RxByte);
}


void USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes) {
	int i;
	// TXE is set by hardware when the content of the TDR register has been transferred into the shift register.
	for (i = 0; i < nBytes; i++) {
		while (!(USARTx->ISR & USART_ISR_TXE));   	// wait until TXE (TX empty) bit is set
		// Writing to USART TDR automatically clears the TXE flag 	
		USARTx->TDR = buffer[i] & 0xFF;
		USART_Delay(300);
	}
	while (!(USARTx->ISR & USART_ISR_TC));   		  // wait until TC bit is set
	USARTx->ISR = USART_ISR_TC;										// WPS - RmW issue?
}   
 

void USART_Delay(uint32_t us) {
	uint32_t time = 100*us/7;    
	while(--time);   
}


void receiveUSART2(){
	if(USART2->ISR & USART_ISR_RXNE) {						// Received data                         
			commandBuffer[rx_Counter] = USART2->RDR;        	// Reading USART_RDR automatically clears the RXNE flag 
			(rx_Counter)++;  
			if((rx_Counter) >= BufferSize )  {
				(rx_Counter) = 0;
			}   
	}
}

void USART2_IRQHandler(){
	receiveUSART2();
}

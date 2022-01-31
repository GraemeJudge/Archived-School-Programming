#include "stm32f303xe.h"
#include <stdio.h>
#include <String.h>

#ifndef __STM32F303RE_NUCLEO64_UART_H
#define __STM32F303RE_NUCLEO64_UART_H

#define BAUD_RATE 9600
#define BufferSize 32

extern volatile uint32_t rx_Counter;					//points the the current location in the buffer
extern uint8_t commandBuffer[BufferSize];	

void 		UART2_Init(void);
void 		UART2_GPIO_Init(void);

void receiveUSART2(void);

void 		USART_Write(USART_TypeDef * USARTx, uint8_t *buffer, uint32_t nBytes);
uint8_t USART_Read_Byte(USART_TypeDef * USARTx);
void 		USART_Delay(uint32_t us);

#endif

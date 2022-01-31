#ifndef __STM32L476G_DISCOVERY_LED_H
#define __STM32L476G_DISCOVERY_LED_H

//************************************
//	Declare LED Functions
//
//************************************

#include "stm32f303xe.h"

void LED_Init(void);

void Red_LED_Off(void);
void Red_LED_On(void);
void Red_LED_Toggle(void);

void Green_LED_On(void);
void Green_LED_Off(void);
void Green_LED_Toggle(void);
#endif // __STM32L476G_DISCOVERY_LED_H //

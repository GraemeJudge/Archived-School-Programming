#ifndef _MOTORS_H
#define _MOTORS_H

#include "stm32f303xe.h"
#include <string.h>
#include <stdlib.h>
#include "UART.h"


void rightMotorInit(void);	

void leftMotorInit(void);

void rightMotorSpeed(int speed);		//in percent
void leftMotorSpeed(int speed);

void setMotorDutyCycle(TIM_TypeDef port, __IO uint32_t channel, int duty);

#endif


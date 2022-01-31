#ifndef __LIMITSWITCHES_H_
#define __LIMITSWITCHES_H_

#include "stm32f303xe.h"
#include "LED.h"

extern volatile int triggered; 			//0 is not triggered, -1 is left side and 1 is right side

void initSwitches(void);
void initLeftSwitch(void);
void initRightSwitch(void);

#endif

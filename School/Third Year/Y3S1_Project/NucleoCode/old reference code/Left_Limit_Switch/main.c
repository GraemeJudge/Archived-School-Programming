#include "source.h"
#include "utils.h"
#include "stm32f303xe.h"
#include "SysClock.h"
#include "LED.h"

//******************************
// Limit Switch Left
//
//
//******************************

int main(void)
{
	System_Clock_Init();
	LED_Init();
	
	EXTI_Init();
}

#include "source.h"
#include "stm32f303xe.h"
#include "LED.h"

//***************************************************************************
//	source.c		-->   External interrupt with interrupt handler incrementing
//										variable
//	
//										Will be used for Limit Switches
//										This code is for Right Limit Switch using PC6 and LED2 
//
//***************************************************************************

volatile uint8_t R; //Our flag for stepper motor


void EXTI_Init(void)
{		

			// GPIO Configuration //
	
	RCC->AHBENR |=   RCC_AHBENR_GPIOCEN;
	
	// GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOC->MODER &= (~3U <<(2*6));

	// GPIO Push-Pull: No pull-up or pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	GPIOC->PUPDR |= (1U << (2*6));
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1)
	
	// Connect External Line to the GPIO pin PC6 to EXTI9_5
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI6;     // SYSCFG external interrupt configuration registers
	SYSCFG->EXTICR[1] |=  SYSCFG_EXTICR2_EXTI6_PC; //to PC 6
	
	// Interrupt Mask Register
	EXTI->IMR   |= EXTI_IMR_IM6;     // 0 = marked, 1 = not masked (i.e., enabled)
	
	// Trigger selection
	 EXTI->RTSR |= EXTI_RTSR_RT6;  			// 0 = trigger disabled, 1 = trigger enabled
																		 //will trigger upon impact

	//EXTI->FTSR |= EXTI_FTSR_FT6;     // 0 = trigger disabled, 1 = trigger enabled
																		//will trigger upon release

	//EXIT Interrupt Enable
	NVIC_EnableIRQ(EXTI9_5_IRQn); 
  NVIC_SetPriority(EXTI9_5_IRQn, 0);
}

void EXTI9_5_IRQHandler(void)
{  
	
	if ((EXTI->PR & EXTI_PR_PIF6) == EXTI_PR_PIF6) {				// cleared by writing a 1 - R-M-W will clear all pending flags
		
		EXTI->PR = EXTI_PR_PIF6;	//write a 1 to the bit to clear
		 
		Green_LED_Toggle();
	
		R++;
		
	}
}

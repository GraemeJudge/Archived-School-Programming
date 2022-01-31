#include "source.h"
#include "stm32f303xe.h"
#include "LED.h"
#include "utils.h"

volatile uint8_t x; //Our flag for stepper motor


void EXTI_Init(void){
	
	// GPIO Configuration
	RCC->AHBENR |=   RCC_AHBENR_GPIOCEN;
	
	// GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	GPIOC->MODER &= ~3U << 0;

	// GPIO Push-Pull: No pull-up or pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)	
	// We do not need to pull down PA.0 because it has already been pulled down externally.
	//GPIOC->PUPDR &= 1 << (5 * 2);
	
	SET_BITS(GPIOC->PUPDR, 1 << (5*2));
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	
	// Connect External Line to the GPIO pin PA0 to EXTI5 
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	
	SYSCFG->EXTICR[1] &= ~SYSCFG_EXTICR2_EXTI5;
	SYSCFG->EXTICR[1] |=  SYSCFG_EXTICR2_EXTI5_PC; //to PC 5
	SYSCFG->EXTICR[1] &= ~(0X000F);
	
	EXTI->RTSR |= EXTI_RTSR_RT5;
	EXTI->FTSR &= EXTI_FTSR_FT5;
	
	EXTI->IMR |= EXTI_IMR_IM5;     // 0 = marked, 1 = not masked (i.e., enabled)
	
	NVIC_EnableIRQ(EXTI9_5_IRQn); 
  NVIC_SetPriority(EXTI9_5_IRQn, 0); 

}

void EXTI9_5_IRQHandler(void) {
	if ((EXTI->PR & EXTI_PR_PIF5) == EXTI_PR_PIF5) {				// cleared by writing a 1 - R-M-W will clear all pending flags
		
		EXTI->PR = EXTI_PR_PIF5;	//write a 1 to the bit to clear
		
		Green_LED_Toggle();
		
		x++;
		
	}
}

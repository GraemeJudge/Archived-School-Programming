#include "encoders.h"
#include "stm32f3xx.h"
#include "utils.h"

int Rcount = 0;
int Lcount = 0;

void TIM2_IRQHandler(void)
{
	uint32_t Capture;
	
	if((TIM2->SR & TIM_SR_CC1IF) != 0)
	{
		//Read CCR1 to get current capture, which will clear CC1if flag
		Capture = TIM2->CCR1;
		Lcount++;	
	}		
	
	if((TIM2->SR & TIM_SR_CC2IF) != 0)
	{
		//Read CCR1 to get current capture, which will clear CC1if flag
		Capture = TIM2->CCR1;
		Rcount++;	
	}		
	
	//OVERFLOW CHECK//
	if((TIM2->SR & TIM_SR_UIF) != 0)
	{
		TIM2->SR &= ~TIM_SR_UIF;
	}
}
//END of IRQhandler

void L_Encoder_timer_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	//Motor drive signal
	SET_BITS(GPIOA->MODER, 2UL << 0 * 2);
	//AF[0] for pin 0-7 [1] for pin 8-15
	SET_BITS(GPIOA->AFR[0], 1UL << 0);									//need to pick alternate function 6 for timer 1 chanel 2	
	SET_BITS(GPIOA->PUPDR, 0 << 0);											//no pull up, no pulldown
	
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 0;
	TIM2 -> ARR = 0xFFFF;

	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;
	
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;
	
	TIM2->CCMR1 &= ~TIM_CCMR1_IC1F;
	
	TIM2->CCER |= TIM_CCER_CC1P;
	
	TIM2->CCMR1 &= ~(TIM_CCMR1_IC1PSC);
	TIM2->CCER |= TIM_CCER_CC1E;
		
	TIM2->DIER |= TIM_DIER_CC1IE;
		
	TIM2->CR1 |= TIM_CR1_CEN;
		
	Encoder_interrupt_P();
}	

void R_Encoder_timer_init(void)
{
	RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
	//Motor drive signal
	SET_BITS(GPIOA->MODER, 2UL << 1 * 2);
	//AF[0] for pin 0-7 [1] for pin 8-15
	SET_BITS(GPIOA->AFR[0], 1UL << 1);									//need to pick alternate function 6 for timer 1 chanel 2	
	SET_BITS(GPIOA->PUPDR, 0 << 1);											//no pull up, no pulldown
	
	
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->PSC = 0;
	TIM2 -> ARR = 0xFFFF;

	TIM2->CCMR1 &= ~TIM_CCMR1_CC2S;
	
	TIM2->CCMR1 |= TIM_CCMR1_CC2S_0;
	
	TIM2->CCMR1 &= ~TIM_CCMR1_IC2F;
	
	TIM2->CCER |= TIM_CCER_CC2P;
	
	TIM2->CCMR1 &= ~(TIM_CCMR1_IC2PSC);
	TIM2->CCER |= TIM_CCER_CC2E;
		
	TIM2->DIER |= TIM_DIER_CC2IE;
		
	TIM2->CR1 |= TIM_CR1_CEN;
		
	Encoder_interrupt_P();
}	
 
//END OF L_Encoder_timer_init//

//Setting Interrupt Priority
void Encoder_interrupt_P(void)
{
	NVIC_SetPriority(TIM2_IRQn, 0);
	NVIC_EnableIRQ(TIM2_IRQn);
}

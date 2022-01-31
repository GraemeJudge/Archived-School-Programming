

#include "servo.h"
#include <stdarg.h>


void initServo(void){

	SET_BITS(RCC->AHB2ENR, RCC_AHB2ENR_GPIOEEN);

	FORCE_BITS(GPIOE->MODER, 3UL << 2 * 8, 2UL << 2 * 8);
	
	FORCE_BITS(GPIOE->AFR[1], 0xF, 1UL);
	
	FORCE_BITS(GPIOE->PUPDR, 3UL << 2 *8 , 0);
	
	initTimer();	
}


void initTimer(void){
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;

		CLR_BITS(TIM1->CR1, TIM_CR1_DIR);
		TIM1-> PSC = 1598;
		TIM1->ARR = 999;
		CLR_BITS(TIM1->CCMR1, TIM_CCMR1_OC1M);
	
		SET_BITS(TIM1->CCR1, 80);	//inital duty cycle 50%
	
		SET_BITS(TIM1->BDTR, TIM_BDTR_MOE);
		SET_BITS(TIM1->CCMR1, TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	
		SET_BITS(TIM1->CCER, TIM_CCER_CC1NE);
	
		CLR_BITS(TIM1->CCER, TIM_CCER_CC1NP);
	
		SET_BITS(TIM1->CR1, TIM_CR1_CEN);
}




int16_t servoMove(uint16_t val){
	int16_t deg = 0;
	
	if(val < 2624){	
		setDutyCycle(3);					//90 degrees counter clockwise
		deg = -90;
	}
	if(val > 2624 && val < 2991){
		setDutyCycle(6);						//45 degrees counter clockwise
		deg = -45;
	}
	if(val > 2991 && val < 3358){
		setDutyCycle(8);						//0 degrees
		deg = 0;
	}
	if(val > 3358 && val < 3725){
		setDutyCycle(10);						//45 degrees clockwise
		deg = 45;
	}
	if(val > 3725){
		setDutyCycle(12);						//90 degrees clockwise
		deg = 90;
	}	
	return deg;
}

void setDutyCycle(uint8_t duty){
	duty *= 10;
	CLR_BITS(TIM1->CCR1, 0xFFFF);
	SET_BITS(TIM1->CCR1, duty);	//inital duty cycle 50%
}
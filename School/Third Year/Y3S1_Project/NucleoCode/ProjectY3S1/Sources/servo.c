#include "servo.h"
#include <stdarg.h>

void initServo(void){
	SET_BITS(RCC->AHBENR, RCC_AHBENR_GPIOBEN);	//enable gpio port b
	//af mode
	FORCE_BITS(GPIOB->MODER, 3UL << (2 * 0), 2UL <<(2 * 0));
	
	//AF[0] for pin 0-7 [1] for pin 8-15
	FORCE_BITS(GPIOB->AFR[0], 0xF, 6UL);	//need to pick alternate function 6 for timer 1 chanel 2
	
	FORCE_BITS(GPIOB->PUPDR, 3UL << (2 * 0), 0);	//no pull up, no pulldown
	
	initTimer();	
}


void initTimer(void){
		SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);

		CLR_BITS(TIM1->CR1, TIM_CR1_DIR);
		TIM1-> PSC = 1598;									//prescalar may need to change it freq = fclk_psc / (PSC + 1) this case = 
		TIM1->ARR = 999;										//PWM period = 
		CLR_BITS(TIM1->CCMR1, TIM_CCMR1_OC2M);
		SET_BITS(TIM1->CCR2, 80);	//Inital duty cycle 50%
		SET_BITS(TIM1->BDTR, TIM_BDTR_MOE);
		SET_BITS(TIM1->CCMR1, TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
		CLR_BITS(TIM1->CCER, TIM_CCER_CC2NP);
		SET_BITS(TIM1->CCER, TIM_CCER_CC2NE);
		SET_BITS(TIM1->CR1, TIM_CR1_CEN);
}


int16_t servoMove(uint16_t val){
	int16_t deg = 0;
	
	if(val < 2624){	
		setDutyCycle(30);					//90 degrees counter clockwise
		deg = -90;
	}
	if(val > 2624 && val < 2991){
		setDutyCycle(60);						//45 degrees counter clockwise
		deg = -45;
	}
	if(val > 2991 && val < 3358){
		setDutyCycle(80);						//0 degrees
		deg = 0;
	}
	if(val > 3358 && val < 3725){
		setDutyCycle(100);						//45 degrees clockwise
		deg = 45;
	}
	if(val > 3725){
		setDutyCycle(120);						//90 degrees clockwise
		deg = 90;
	}	
	return deg;
}

void setServo(int8_t deg){
	if(deg <= 90 && deg >= -90){
		uint8_t ang = ((deg + 90)/2.25)+ 40;
		setDutyCycle(ang);
		//((desired angle + 90 )/ 22.5) + 4 = servo duty cycle	
	}else{
		printf("Didnt move servo, make sure angle is between -90 and 90 degrees\n");
	}
}
void setDutyCycle(uint8_t duty){
	//duty *= 10;
	CLR_BITS(TIM1->CCR2, 0xFFFF);
	SET_BITS(TIM1->CCR2, duty);	//inital duty cycle 50%
}


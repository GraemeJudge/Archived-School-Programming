
#include "Heartbeat.h"

int responded = 0;

void initHB(void){
	SET_BITS(RCC->APB1ENR, RCC_APB1ENR_TIM3EN);

	CLR_BITS(TIM3->CR1, TIM_CR1_DIR);
	
	//psc = 1KHz
	TIM3-> PSC = 720000;									//prescalar may need to change it freq = fclk_psc / (PSC + 1) this case = 
	TIM3->ARR = 1999;										//PWM period = 
	//arr = 2000 so interrupt every 2000/1000 = 2 seconds 4
	
	SET_BITS(TIM3->CCR1, 500);	//Inital duty cycle 50%
	SET_BITS(TIM3->BDTR, TIM_BDTR_MOE);
	SET_BITS(TIM3->CCMR1, TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	CLR_BITS(TIM3->CCER, TIM_CCER_CC1NP);
	SET_BITS(TIM3->CCER, TIM_CCER_CC1NE);
	SET_BITS(TIM3->CR1, TIM_CR1_CEN);
	
	SET_BITS(TIM3->DIER, TIM_DIER_UIE);		//enable interrupt generation
	
	NVIC_EnableIRQ(TIM3_IRQn);						//enable interrupts
		
}

void TIM3_IRQHandler(){
	if((TIM3->SR & TIM_SR_UIF) != 0){
		//Green_LED_Toggle();
		checkConnection();
		TIM3->SR &= ~TIM_SR_UIF;
	} 
}

void checkConnection(void){
	if(0){
		printf("Counted: %d Left\n", (Lcount/2));
		printf("Counted: %d Right\n", (Rcount/2));
		Lcount = 0;
		Rcount = 0;
	}
	if(responded == 0){
		ping();
		return;
	}
	if(responded == -1){
		Green_LED_Off();
		disconnect();
		responded = 0;
		return;
	}
	Green_LED_On();
	responded = 0;
}

void ping(){
	//printf("heartbeat\n");
	responded = -1;
}

void disconnect(void){
	rightMotorSpeed(0);
	leftMotorSpeed(0);
}


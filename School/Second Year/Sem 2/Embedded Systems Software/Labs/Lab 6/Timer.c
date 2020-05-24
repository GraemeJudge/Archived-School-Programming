#include "Timer.h"
#include "LED.h"


static volatile uint32_t pulseWidth = 0;

#define MAX_ECHO 15000

#define TRIG_PIN 6

void initDistanceSensor(){
	initTimer();
	initInterrupts();
}
	


static void initTimer(){	
uint32_t pulseWidth_uS = 200; //should at least 10uS
	uint32_t pulseDelay_uS = 500000;
	
	float dutyCycle = (float)pulseWidth_uS / (float)pulseDelay_uS;
	
	//enable clock on port B
	SET_BITS(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
	
	//set mode to alternate function
	FORCE_BITS(GPIOB->MODER, 3UL << (2*TRIG_PIN), 2UL << (2*TRIG_PIN));

	//set alternate function to AF 2
	FORCE_BITS(GPIOB->AFR[0], 0xF << (4 * TRIG_PIN), 2UL << (4 * TRIG_PIN));
	
	//no pull up, no pull down
	FORCE_BITS(GPIOB->PUPDR, 3UL << (2*TRIG_PIN), 0);
	
	//enable timer 4 clock
	SET_BITS(RCC->APB1ENR1, RCC_APB1ENR1_TIM4EN);
	
	//up counting
	CLR_BITS(TIM4-> CR1, TIM_CR1_DIR);
	
	//prescaler
	//TIM4->PSC = prescaleValue; --> 1kHz clock is 1ms
	TIM4->PSC = 80000-1;
	
	//auto reload
	TIM4->ARR = 5000 - 1; //auto reload every 500 ms 
	
	//clear ch 1 output cmp registers
	CLR_BITS(TIM4->CCMR1, TIM_CCMR1_OC1M);
	
	//Set the duty cycle
	TIM4 -> CCR1 = dutyCycle * (TIM4->ARR + 1);
	//TIM4 -> CCR1 = 500;
	
	//main output enable
	SET_BITS(TIM4->BDTR, TIM_BDTR_MOE);

	//pwm mode
	SET_BITS(TIM4->CCMR1, TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	
	//output polarity active high
	CLR_BITS(TIM4 -> CCER, TIM_CCER_CC1P);
	
	//enable CH1
	SET_BITS(TIM4 -> CCER, TIM_CCER_CC1E);
	
	//enable counter
	SET_BITS(TIM4->CR1, TIM_CR1_CEN);
}

static void initInterrupts(){
	SET_BITS(RCC->AHB2ENR, RCC_AHB2ENR_GPIOAEN); 	//enable clock for port A

	GPIOA->MODER &= ~(3UL);	//clear mode
	GPIOA->MODER |= 2UL;	//alternate function mode
	
	GPIOA->AFR[0] &= ~(0XF);	//clear alternate function selection
	GPIOA->AFR[0] |= 1UL;		//select alternate function
	
	GPIOA->OSPEEDR &= ~3UL;
	GPIOA->OSPEEDR |= 2UL;
	
	GPIOA->PUPDR &= ~3UL;
	
	RCC->APB1ENR1 |= RCC_APB1ENR1_TIM2EN; //ENABLE CLOCK

	TIM2->PSC = 80UL;		//PRESCALAR 1MHz
	TIM2->ARR = 0XFFFF;	//AUTORELOAD AT MAX VALUE
	
	TIM2->CCMR1 &= ~TIM_CCMR1_CC1S;	//CLEAR CAPTURE AND COMPARE SELECTIONS BITS
	TIM2->CCMR1 |= TIM_CCMR1_CC1S_0;	//CC1S[1:0] FOR CHANNEL 1

	TIM2->CCMR1 &= ~TIM_CCMR1_IC1F; //NO FILTERING
	
	TIM2->CCER &= ~(TIM_CCER_CC1P|TIM_CCER_CC1NP); //CLEAR POLARITY
	TIM2->CCER |= TIM_CCER_CC1P;	//ONLY FALLING EDGE CREATES INTERRUPTS
	
	TIM2->SMCR &= ~TIM_SMCR_TS;	//CLEAR TRIGGER SELECTION
	TIM2->SMCR |= 4UL << 4; // T1 EDGE DETECTOR
	TIM2->SMCR &= ~TIM_SMCR_SMS;	//CLEAR SLAVE MODE BIT
	TIM2->SMCR |= 4; // 1000 SLAVE MODE WITH RESET
	TIM2->CCMR1 &= ~(TIM_CCMR1_IC1PSC); //CLEAR INPUT PRESCALAR
	TIM2->CCER |= TIM_CCER_CC1E; //ENABLE CAPTURE FOR CHANNEL 1
	TIM2->DIER |= TIM_DIER_CC1IE; 	//ALLOW TIMER 2 CHANNEL 1 TO GENERATE INTERRUPTS
	TIM2->DIER |= TIM_DIER_CC1DE;
	TIM2->CR1 |= TIM_CR1_CEN;			//ENABLE COUNTING
	
	NVIC_SetPriority(TIM2_IRQn, 0);		//SETS PRIORITY TO 0 (HIGHEST)
	
	NVIC_EnableIRQ(TIM2_IRQn);					//ENABLE THE NVIC
}

void TIM2_IRQHandler(void){
	Green_LED_Toggle();//toggle for debugging 
	
	if((TIM2->SR & TIM_SR_UIF) != 0){
			TIM2->SR &= ~TIM_SR_UIF;
	}
	if((TIM2->SR & TIM_SR_CC1IF) != 0){
		pulseWidth = TIM2->CCR1;
		Red_LED_Toggle();
	}
}


uint32_t getDistanceCM(){
	if(pulseWidth <= MAX_ECHO){
		return(pulseWidth/58);
	}else{
		return(-1);
	}
	
}


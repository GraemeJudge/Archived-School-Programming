#include "motors.h"
#include "utils.h"

#define RIGHT_DIRECTION_A 8
#define RIGHT_DIRECTION_B 9

#define LEFT_DIRECTION_A 8
#define LEFT_DIRECTION_B 9

int leftDir = 0;
int rightDir = 0;

void rightMotorInit(){
	RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
	//PC8 and 9 motor direction bits
	// GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	SET_BITS(GPIOC->MODER, 1ul << RIGHT_DIRECTION_A * 2);
	SET_BITS(GPIOC->MODER, 1ul << RIGHT_DIRECTION_B * 2);
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	SET_BITS(GPIOC->OSPEEDR, 3ul << RIGHT_DIRECTION_A * 2);
	SET_BITS(GPIOC->OSPEEDR, 3ul << RIGHT_DIRECTION_B * 2);
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	SET_BITS(GPIOC->OTYPER, 0x0 << RIGHT_DIRECTION_A);
	SET_BITS(GPIOC->OTYPER, 0x0 << RIGHT_DIRECTION_B);
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	SET_BITS(GPIOC->PUPDR, 0 << RIGHT_DIRECTION_A * 2);	
	SET_BITS(GPIOC->PUPDR, 0 << RIGHT_DIRECTION_B * 2);	
	
	CLR_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_A);
	CLR_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_B);

	//Motor drive signal	
	SET_BITS(GPIOC->MODER, 2UL << 11 * 2);
	//AF[0] for pin 0-7 [1] for pin 8-15
	SET_BITS(GPIOC->AFR[1], 4UL << 12);									//need to pick alternate function 6 for timer 1 chanel 2	
	SET_BITS(GPIOC->PUPDR, 0 << 11);	//no pull up, no pulldown
	
	SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);

	CLR_BITS(TIM8->CR1, TIM_CR1_DIR);
	TIM8-> PSC = 1598;									//prescalar may need to change it freq = fclk_psc / (PSC + 1) this case = 
	TIM8->ARR = 999;										//PWM period = 
	CLR_BITS(TIM8->CCMR1, TIM_CCMR1_OC2M);
	SET_BITS(TIM8->CCR2, 0);	//Inital duty cycle 50%
	SET_BITS(TIM8->BDTR, TIM_BDTR_MOE);
	SET_BITS(TIM8->CCMR1, TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2);
	CLR_BITS(TIM8->CCER, TIM_CCER_CC2NP);
	SET_BITS(TIM8->CCER, TIM_CCER_CC2NE);
	SET_BITS(TIM8->CR1, TIM_CR1_CEN);
}


void leftMotorInit(){
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
	//PC8 and 9 motor direction bits
	// GPIO Mode: Input(00, reset), Output(01), AlterFunc(10), Analog(11, reset)
	SET_BITS(GPIOB->MODER, 1ul << LEFT_DIRECTION_A * 2);
	SET_BITS(GPIOB->MODER, 1ul << LEFT_DIRECTION_B * 2);
	
	// GPIO Speed: Low speed (00), Medium speed (01), Fast speed (10), High speed (11)
	SET_BITS(GPIOB->OSPEEDR, 3ul << LEFT_DIRECTION_A * 2);
	SET_BITS(GPIOB->OSPEEDR, 3ul << LEFT_DIRECTION_B * 2);
	
	// GPIO Output Type: Output push-pull (0, reset), Output open drain (1) 
	SET_BITS(GPIOB->OTYPER, 0x0 << LEFT_DIRECTION_A);
	SET_BITS(GPIOB->OTYPER, 0x0 << LEFT_DIRECTION_B);
	
	// GPIO Push-Pull: No pull-up, pull-down (00), Pull-up (01), Pull-down (10), Reserved (11)
	SET_BITS(GPIOB->PUPDR, 0 << LEFT_DIRECTION_A * 2);	
	SET_BITS(GPIOB->PUPDR, 0 << LEFT_DIRECTION_B * 2);	
	
	CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_A);
	CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_B);

	//Motor drive signal
	SET_BITS(GPIOC->MODER, 2UL << 10 * 2);
	//AF[0] for pin 0-7 [1] for pin 8-15
	SET_BITS(GPIOC->AFR[1], 4UL << 8);									//need to pick alternate function 6 for timer 1 chanel 2	
	SET_BITS(GPIOC->PUPDR, 0 << 10);										//no pull up, no pulldown
	
	SET_BITS(RCC->APB2ENR, RCC_APB2ENR_TIM8EN);

	CLR_BITS(TIM8->CR1, TIM_CR1_DIR);
	TIM8-> PSC = 1598;									//prescalar may need to change it freq = fclk_psc / (PSC + 1) this case = 
	TIM8->ARR = 999;										//PWM period = 
	CLR_BITS(TIM8->CCMR1, TIM_CCMR1_OC1M);
	SET_BITS(TIM8->CCR1, 0);	//Inital duty cycle 50%
	SET_BITS(TIM8->BDTR, TIM_BDTR_MOE);
	SET_BITS(TIM8->CCMR1, TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2);
	CLR_BITS(TIM8->CCER, TIM_CCER_CC1NP);
	SET_BITS(TIM8->CCER, TIM_CCER_CC1NE);
	SET_BITS(TIM8->CR1, TIM_CR1_CEN);
}


void rightMotorSpeed(int speed){
		//printf("Speed %d\n", speed);
	if(speed < 0){
		//printf("right direction is backwards!\n");
		SET_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_B);
		CLR_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_A);
		CLR_BITS(TIM8->CCR2, 0xFFFF);
		SET_BITS(TIM8->CCR2, speed * (-10));
	}else if(speed > 0){
		//printf("right direction is forwards!\n");
		CLR_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_B);
		SET_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_A);
		CLR_BITS(TIM8->CCR2, 0xFFFF);
		SET_BITS(TIM8->CCR2, speed * (10));
	}else if(speed == 0){
		//printf("Stopped!\n");
		CLR_BITS(TIM8->CCR2, 0xFFFF);
		SET_BITS(TIM8->CCR2, 0);
		CLR_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_B);
		CLR_BITS(GPIOC->ODR, 1 << RIGHT_DIRECTION_A);
	}else{
		//printf("Sorry invalid direction for right motor\n");
		CLR_BITS(GPIOC->ODR,1 << RIGHT_DIRECTION_B);
		CLR_BITS(GPIOC->ODR,1 << RIGHT_DIRECTION_A);
	} 
}


void leftMotorSpeed(int speed){
	//printf("Speed %d\n", speed);
	if(speed < 0){
		//printf("left direction is backwards!\n");
		SET_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_B);
		CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_A);
		CLR_BITS(TIM8->CCR1, 0xFFFF);
		SET_BITS(TIM8->CCR1, speed * (-10));
	}else if(speed > 0){
		//printf("left direction is forwards!\n");
		CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_B);
		SET_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_A);
		CLR_BITS(TIM8->CCR1, 0xFFFF);
		SET_BITS(TIM8->CCR1, speed * (10));
	}else if(speed == 0){
		//printf("Stopped!\n");
		CLR_BITS(TIM8->CCR1, 0xFFFF);
		SET_BITS(TIM8->CCR1, 0);
		CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_B);
		CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_A);
	}else{
		//printf("Sorry invalid direction for left motor\n");
		CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_B);
		CLR_BITS(GPIOB->ODR, 1 << LEFT_DIRECTION_A);
	}
}




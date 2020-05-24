#include "ADC.h"


void startADCClock(void){
	RCC->CR |= RCC_CR_HSION;
	while((RCC->CR &= RCC_CR_HSIRDY) == 0);
}


void initADC(void){
	//TEXT PAGE 490
	startADCClock();
	initADCGPIO();
	setUpADC1();
}

void initADCGPIO(void){
	RCC->AHB2ENR |= RCC_AHB2ENR_GPIOAEN;
	
	GPIO_PIN_MODE(GPIOA->MODER, 1, 0x11);
	
	GPIO_PIN_PUPDR(GPIOA->PUPDR, 1, 0x00);
	
	GPIOA->ASCR |= 1UL << 1;	
}

void setUpADC1(void){
	//1 Enable ADC clock bit
	RCC->AHB2ENR |= RCC_AHB2ENR_ADCEN;
	
	//2 Disable ADC1 
	ADC1->CR &= ~(ADC_CR_ADEN);
	
	//3 Enable I/O analog switches voltage booster
	ADC123_COMMON->CCR |= SYSCFG_CFGR1_BOOSTEN;
	
	//4 Enable conversion of internal channels
	ADC123_COMMON->CCR |= ADC_CCR_VREFEN;

	//5 Configure ADC prescaler to select frequency 
	ADC123_COMMON->CCR &= ~ADC_CCR_PRESC;
	
	//6 Select synchronous clock mode
	ADC123_COMMON->CCR |= ADC_CCR_CKMODE_1;
	
	//7 Set all ADCs as independant
	ADC123_COMMON->CCR &= ~ADC_CCR_DUAL;
	
	//8 Call ADCWakeup
	ADCWakeup();
	
	//9 Set resolution
	ADC1->CFGR &= 00;
	
	//10 Select right alignment
	ADC1->CFGR &= ADC_CFGR_ALIGN;
	
	//11 Select 1 in the regular conversion channel conversion seuence
	ADC1->SQR1 &= ~ADC_SQR1_L;
	
	//12 Selet channel number 6
	ADC1->SQR1 |= (ADC_SQR1_SQ1_1 |ADC_SQR1_SQ1_2); 
	
	//13 Set channel 6 as single ended
	ADC1->DIFSEL &= ~ADC_DIFSEL_DIFSEL_6;
	
	//14 Set ADC sampling time
	ADC1->SMPR1 |= (ADC_SMPR1_SMP6_0 | ADC_SMPR1_SMP6_2);
	
	//15 Set ADC as discontinous mode
	ADC1->CFGR &= ~ADC_CFGR_CONT;
	
	//16 Select software trigger
	ADC1->CFGR &= ~ADC_CFGR_EXTEN;
	
	//17 Enable ADC1
	ADC1->CR |= ADC_CR_ADEN;
	
	//18 Wait until ADC1 is ready
	while((ADC1->ISR & ADC_ISR_ADRDY) == 0);	
}


void ADCWakeup (void){
	//Taken from the textbook
	
	int waitTime;
	
	if((ADC1 -> CR & ADC_CR_DEEPPWD) == ADC_CR_DEEPPWD){
		ADC1->CR &= ~(ADC_CR_DEEPPWD);
	}
	
	ADC1->CR |= ADC_CR_ADVREGEN;
	
	
	waitTime = 20 * (80000000/1000000);
	
	while(waitTime != 0){
		waitTime--;
	}
}

uint16_t triggerADCConversion(){
	uint16_t ADCVal; 
	ADC1->CR |= ADC_CR_ADSTART;
	
	while((ADC123_COMMON->CSR &= ADC_CSR_EOC_MST) == 0);
	
	ADCVal = ADC1->DR;
	
	return ADCVal;
}
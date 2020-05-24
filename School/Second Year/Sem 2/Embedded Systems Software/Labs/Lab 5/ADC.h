#include "stm32l476xx.h"
#include "utils.h"

/*
	void startADCClock;

	Starts the clock for the ADC

	Input: 	None
	Output: None
*/
void startADCClock(void);

/*
	void initADC;

	Initalizes the ADC

	Input: 	None
	Output: None
*/
void initADC(void);

/*
	void initADCGPIO;

	Initalizes the GPIO port for the ADC

	Input: 	None
	Output: None
*/
void initADCGPIO(void);

/*
	void setUpADC1;

	Sets up the ADC

	Input: 	None
	Output: None
*/
void setUpADC1(void);

/*
	void ADCWakeup;

	Wakes the ADC up from a deep sleep

	Input: 	None
	Output: None
*/
void ADCWakeup(void);

/*
	void triggerADCConversion;

	Triggers the conversion on the adc to get the value back

	Input: 	None
	Output: uint16_t
				The read ADC value
*/
uint16_t triggerADCConversion(void);
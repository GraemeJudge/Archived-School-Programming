#ifndef _encoders_h
#define _encoders_h

#include "stm32f3xx.h"

// Function Decleration/Definition //

extern int Rcount;
extern int Lcount;

void L_Encoder_timer_init(void);

void R_Encoder_timer_init(void);

void Encoder_interrupt_P(void);

#endif

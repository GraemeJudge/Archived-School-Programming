#include "LED.h"
#include "stm32f303xe.h"
#include "utils.h"
#include "motors.h"

#include "encoders.h"

#include <stdio.h>

extern int responded;


void initHB(void);

void ping(void);

void checkConnection(void);

void disconnect(void);

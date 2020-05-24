#include "stm32l476xx.h"
#include "utils.h"

void initDistanceSensor();

static void initTrigger();

static void initInterrupts();

uint32_t getDistanceCM();
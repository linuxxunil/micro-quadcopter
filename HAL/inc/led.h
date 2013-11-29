#ifndef LED_H
#define LED_H
#include "stm32f10x.h"

void LEDInit(void);
void LEDON(void);
void LEDOFF(void);
void LEDFlash( void );

#endif

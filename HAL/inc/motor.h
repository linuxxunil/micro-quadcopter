#ifndef MOTOR_H
#define MOTOR_H
#include "stm32f10x.h"

void MotorInit(void);
void motorsSetRatio(uint16_t speedMotor1, uint16_t speedMotor2,uint16_t speedMotor3, uint16_t speedMotor4);

#endif

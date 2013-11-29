#include "stm32f10x.h"


#define MOTOR_GPIO_1            GPIO_Pin_0 
#define MOTOR_GPIO_2            GPIO_Pin_1 
#define MOTOR_GPIO_3            GPIO_Pin_2 
#define MOTOR_GPIO_4            GPIO_Pin_3

void MotorInit() {
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;
	uint16_t PrescalerValue = 0;
	
	
  /* Enable TIM10 and GPIOF clock */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA , ENABLE);
  
	
  GPIO_InitStructure.GPIO_Pin = MOTOR_GPIO_1 | MOTOR_GPIO_2 | MOTOR_GPIO_3 | MOTOR_GPIO_4;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	// TIM2 remapping to PA0 PA1 PA2 PA3
  GPIO_PinRemapConfig(GPIO_Remap_TIM2, ENABLE);	
	
  PrescalerValue = (uint16_t) (SystemCoreClock / 24000000) - 1;
  /* Time base configuration */
  TIM_TimeBaseStructure.TIM_Period = 665;
  TIM_TimeBaseStructure.TIM_Prescaler = PrescalerValue;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;

  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	/* Setting */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0x0000;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
 
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
	
  TIM_ARRPreloadConfig(TIM2, ENABLE);

  TIM_Cmd(TIM2, ENABLE);
}

void motorsSetRatio(uint16_t speedMotor1, uint16_t speedMotor2,
												uint16_t speedMotor3, uint16_t speedMotor4)
{
	// setting duty cycle of MOTOR1  
	TIM_SetCompare1(TIM2, speedMotor1);
	// setting duty cycle of MOTOR2
	TIM_SetCompare2(TIM2, speedMotor2);
	// setting duty cycle of MOTOR3
	TIM_SetCompare3(TIM2, speedMotor3);
	// setting duty cycle of MOTOR4
	TIM_SetCompare4(TIM2, speedMotor4);
}
	

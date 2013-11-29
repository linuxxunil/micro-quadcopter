#include "stm32f10x.h"
#include "led.h"
static GPIO_InitTypeDef GPIO_InitStructure;

static void GPIOInit()
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);

  /* Configure PD12, PD13, PD14 and PD15 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void LEDInit( void )
{
	GPIOInit();
}

void LEDOn( void )
{
	GPIO_SetBits(GPIOC,GPIO_Pin_13);
}

void LEDOff( void )
{
	GPIO_ResetBits(GPIOC,GPIO_Pin_13);
}

void LEDFlash( void )
{
	GPIO_ToggleBits(GPIOC,GPIO_Pin_13);
}

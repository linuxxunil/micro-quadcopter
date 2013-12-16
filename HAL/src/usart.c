#include "stm32f10x.h"
#include "usart.h"
#include "led.h"
#include <stdio.h>
#include <stdbool.h>

#define USART_TYPE       				USART1
#define USART_PERIF      				RCC_APB2Periph_USART1
#define USART_GPIO_PERIF				RCC_APB2Periph_GPIOA
#define USART_GPIO_PORT  				GPIOA
#define USART_GPIO_TX    				GPIO_Pin_9
#define USART_GPIO_RX   				GPIO_Pin_10
#define USART_GPIO_IRQ					USART1_IRQn

/* Use embedded function for keil */
/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
  #define GETCHAR_PROTOTYPE int __io_getchar(void)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
  #define GETCHAR_PROTOTYPE int fgetc(FILE *f)
#endif /* __GNUC__ */
 
/* Private functions ---------------------------------------------------------*/

PUTCHAR_PROTOTYPE
{
  /* Write a character to the USART */
  USART_SendData(USART_TYPE, (u8) ch);

  /* Loop until the end of transmission */
  while(USART_GetFlagStatus(USART_TYPE, USART_FLAG_TXE) == RESET);
	return ch;
}

GETCHAR_PROTOTYPE
{
   /* Loop until the end of receive */
   while(USART_GetFlagStatus(USART_TYPE, USART_FLAG_RXNE) == RESET);
  
   /* Read a character to the USART */
   return (USART_ReceiveData(USART_TYPE));
}
/*  Retargets the C library printf function to the USART.  */

void RCC_Configuration(void)
{   
  /* Enable GPIO clock */
  RCC_APB2PeriphClockCmd(USART_PERIF | USART_GPIO_PERIF | RCC_APB2Periph_AFIO, ENABLE);
}

void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
  GPIO_InitStructure.GPIO_Pin = USART_GPIO_TX;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);

  /* Configure USART Rx as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  GPIO_InitStructure.GPIO_Pin = USART_GPIO_RX;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(USART_GPIO_PORT, &GPIO_InitStructure);
}

void NVIC_Configuration(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  /* Configure the NVIC Preemption Priority Bits */  
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);
  
  /* Enable the USARTy Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = USART_GPIO_IRQ;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
}

void USART_Configuration(int baudrate)
{
	USART_InitTypeDef USART_InitStructure;
	
	/* Setting UART Baudrate */
	USART_InitStructure.USART_BaudRate = baudrate;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	
  USART_Init(USART_TYPE, &USART_InitStructure);

	//USART_ITConfig(BULETOOTH_UART1, USART_IT_RXNE, ENABLE);
  USART_ITConfig(USART_TYPE, USART_IT_TXE, DISABLE);
	
  /* Enable USART */
  USART_Cmd(USART_TYPE, ENABLE);
}

static bool isInit = false;
void USARTInit(int baudrate)
{
	if (isInit)
    return;
	
	RCC_Configuration();
	
	//NVIC_Configuration();
	
	GPIO_Configuration();
	
	USART_Configuration(baudrate);
	
	
	isInit = true;
}

/* Use Interrupt */
void USART1_IRQHandler(void)
{
  if(USART_GetITStatus(USART_TYPE, USART_IT_RXNE) != RESET)
  {
  }
	
	if(USART_GetITStatus(USART_TYPE, USART_IT_TXE) != RESET)
  {   
  }
}

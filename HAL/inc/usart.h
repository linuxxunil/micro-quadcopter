#ifndef _USART_H
#define _USART_H
#include "stm32f10x.h"

void USARTInit( int baudrate );
void USARTSendData(uint8_t data) ;
uint8_t USARTReadData( void );


#endif

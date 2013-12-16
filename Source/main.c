/**
  ******************************************************************************
  * @file    GPIO/IOToggle/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "FreeRTOS.h"
#include "task.h"
#include "led.h"
#include "motor.h"
#include "usart.h"
#include<stdio.h>

void vLEDTask( void *pvParameters )
{	
	
	portTickType xLastWakeTime = xTaskGetTickCount();
	
	while(1) 
	{
		//vTaskDelayUntil( &xLastWakeTime, ( 1000 / portTICK_RATE_MS ) );
		
	
		LEDFlash();
		vTaskDelay(1000);
	}
} 
extern void vSystemTask( void *pvParameters );

int main(void)
{
	LEDInit();
	USARTInit(115200);
	
	//MotorInit();

	//LEDOn();

	//motorsSetRatio();

	xTaskCreate( vLEDTask, ( signed portCHAR * ) "LED", 
  					configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	
	xTaskCreate( vSystemTask, ( signed portCHAR * ) "System", 
  					configMINIMAL_STACK_SIZE, NULL, tskIDLE_PRIORITY, NULL );
	
	vTaskStartScheduler();

	while(1);

}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

#endif

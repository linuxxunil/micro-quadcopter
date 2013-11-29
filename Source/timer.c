#include "stm32f10x_it.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "timers.h"

/* The set frequency of the interrupt.  Deviations from this are measured as
the jitter. */
#define timerINTERRUPT_FREQUENCY		( ( unsigned portSHORT ) 20000 )

/* The expected time between each of the timer interrupts - if the jitter was
zero. */
#define timerEXPECTED_DIFFERENCE_VALUE	( configCPU_CLOCK_HZ / timerINTERRUPT_FREQUENCY )

/* The number of interrupts to pass before we start looking at the jitter. */
#define timerSETTLE_TIME			5

volatile unsigned portSHORT usMaxJitter = 0;

void vTimer2IntHandler( void )
{
	static unsigned portSHORT usLastCount = 0, usSettleCount = 0, usMaxDifference = 0;
	unsigned portSHORT usThisCount, usDifference;

	/* Capture the free running timer 3 value as we enter the interrupt. */
	usThisCount = TIM3->CNT;
	
	if( usSettleCount >= timerSETTLE_TIME )
	{
		/* What is the difference between the timer value in this interrupt
		and the value from the last interrupt. */
		usDifference = usThisCount - usLastCount;

		/* Store the difference in the timer values if it is larger than the
		currently stored largest value.  The difference over and above the
		expected difference will give the 'jitter' in the processing of these
		interrupts. */
		if( usDifference > usMaxDifference )
		{
			usMaxDifference = usDifference;
			usMaxJitter = usMaxDifference - timerEXPECTED_DIFFERENCE_VALUE;
		}
	}
	else
	{
		/* Don't bother storing any values for the first couple of
		interrupts. */
		usSettleCount++;
	}

	/* Remember what the timer value was this time through, so we can calculate
	the difference the next time through. */
	usLastCount = usThisCount;

    TIM_ClearITPendingBit( TIM2, TIM_IT_Update );
}

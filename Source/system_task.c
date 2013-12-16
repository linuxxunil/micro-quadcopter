#include <stdio.h>
#include "FreeRTOS.h"
#include "task.h"
#include "mpu6050.h"
#include "common.h"

typedef struct {
  s16 X;
  s16 Y;
  s16 Z;
  s16 OffsetX;
  s16 OffsetY;
  s16 OffsetZ;
  float TrueX;
  float TrueY;
  float TrueZ;
} AcceInfo, GryoInfo;

void MPU6050_Calibrate()
{
	AcceInfo accInfo;
	GryoInfo gryoInfo;
	u16 times = 0xFFFF;
	s16 i,j=0;
	s16 buf[6] ;
	s32 sum[6];
	u16 crcVal = 0;
	u8 array[10] = {0x00};
	s16 base = 8192;
	
  while(1)
	{
			MPU6050_GetRawAccelGyro(buf); 
			
			printf("Accel = %d %d %d ", buf[0], buf[1], buf[2]);
			printf("Gryo  = %d %d %d\r\n", buf[3], buf[4], buf[5]);
			if ( j == 0 ) {
				sum[0] = buf[0];sum[1] = buf[1];
				sum[2] = buf[2];sum[3] = buf[3];
				sum[4] = buf[4];sum[5] = buf[5];
			} else {
				sum[0] += buf[0]; sum[1] += buf[1];
				sum[2] += buf[2]; sum[3] += buf[3];
				sum[4] += buf[4]; sum[5] += buf[5];
			}
			if ( j++ >=100 ) {
				
					DEBUG("Avg Accel = %d %d %d\r\n", sum[0]/j, sum[1]/j, sum[2]/j);
					DEBUG("Avg Gryo  = %d %d %d\r\n", sum[3]/j, sum[4]/j, sum[5]/j);
				j = 0;
			}
			
			vTaskDelay(100);
	}
	
}

void vSystemTask( void *pvParameters )
{	
	int i,j=0;
	int sum = 8192;
	s16 accelGyroBuffer[6]={0x00};
	
	/* Initial */
	MPU6050_Initialize();
	MPU6050_Calibrate();
	
  while ( 1 ) 
	{
			vTaskDelay(1000);
	}
}


#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>
#include "semphr.h"

xSemaphoreHandle xMutex;

static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, true);
}

static void vLEDTask_one(void *pvParameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
		xSemaphoreTake(xMutex, portMAX_DELAY);
		Board_LED_Set(( char * ) pvParameters, false);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(( char * ) pvParameters, true);
		xSemaphoreGive(xMutex);
		vTaskDelayUntil( &xLastWakeTime, 5000);
	}
}

static void vLEDTask_two(void *pvParameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	vTaskDelayUntil( &xLastWakeTime, 2000);
	while (1)
	{
		xSemaphoreTake(xMutex, portMAX_DELAY);
		Board_LED_Set(( char * ) pvParameters, false);
		vTaskDelayUntil( &xLastWakeTime, 1000);
		Board_LED_Set(( char * ) pvParameters, true);
		xSemaphoreGive(xMutex);
		vTaskDelayUntil( &xLastWakeTime, 5000);
	}
}

static void vLEDTask_three(void *pvParameters)
{
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	vTaskDelayUntil( &xLastWakeTime, 4000);
	int x = 1;
	while (1)
	{
		if((x%3) == 0){
			taskENTER_CRITICAL();

			vTaskDelayUntil( &xLastWakeTime, 3000);
			++x;
			taskEXIT_CRITICAL();
	//		++x;
		}
		else if((x%3) != 0)
		{
			xSemaphoreTake(xMutex, portMAX_DELAY);
			Board_LED_Set(( char * ) pvParameters, false);
			vTaskDelayUntil( &xLastWakeTime, 1000);
			Board_LED_Set(( char * ) pvParameters, true);
			xSemaphoreGive(xMutex);
			vTaskDelayUntil( &xLastWakeTime, 5000);
			++x;
		}
	}
}

//static void vLEDTask_three(void *pvParameters)
//{
//	portTickType xLastWakeTime;
//	xLastWakeTime = xTaskGetTickCount();
//	vTaskDelayUntil( &xLastWakeTime, 4000);
//	int x = 1;
//	while (1)
//	{
//		taskENTER_CRITICAL();
////		xSemaphoreTake(xMutex, portMAX_DELAY);
////		Board_LED_Set(( char * ) pvParameters, false);
////		vTaskDelayUntil( &xLastWakeTime, 1000);
////		Board_LED_Set(( char * ) pvParameters, true);
////		xSemaphoreGive(xMutex);
////		vTaskDelayUntil( &xLastWakeTime, 5000);
//		taskEXIT_CRITICAL();
////		vTaskDelayUntil( &xLastWakeTime, 1000);
//	}
//}

int main(void)
{
	prvSetupHardware();

	xMutex = xSemaphoreCreateMutex();

	xTaskCreate(vLEDTask_one, (signed char *) "Red",
				configMINIMAL_STACK_SIZE, 0, 3,
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTask_two, (signed char *) "Green",
				configMINIMAL_STACK_SIZE, 1, 2,
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTask_three, (signed char *) "Blue",
					configMINIMAL_STACK_SIZE, 2, 3,
					(xTaskHandle *) NULL);

	vTaskStartScheduler();

	return 1;
}

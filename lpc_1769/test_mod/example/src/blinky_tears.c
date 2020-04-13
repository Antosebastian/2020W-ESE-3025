#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include <stdio.h>



static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
	Board_LED_Set(0, true);
}

static void vLEDTaskF(void *pvParameters)
{
//	char *pcTaskNumber;
////	portTickType xLastWakeTime;
//	pcTaskNumber = ( char * ) pvParameters;

		while (1) {
			while((( char * ) pvParameters == 0))
			{
			bool LedState = false;
			Board_LED_Set(( char * ) pvParameters, LedState);
			vTaskDelay(configTICK_RATE_HZ);
			LedState = true;
			Board_LED_Set(( char * ) pvParameters, LedState);
			vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ/2);
			}
			while((( char * ) pvParameters == 1))
						{
				bool LedState = true;
						Board_LED_Set(( char * ) pvParameters, LedState);
						vTaskDelay(3 * configTICK_RATE_HZ);
						LedState = false;
						Board_LED_Set(( char * ) pvParameters, LedState);
						vTaskDelay(configTICK_RATE_HZ);
						LedState = true;
						Board_LED_Set(( char * ) pvParameters, LedState);
						vTaskDelay(configTICK_RATE_HZ / 2);
						}
			while((( char * ) pvParameters == 2))
						{
						bool LedState = true;
						Board_LED_Set(( char * ) pvParameters, LedState);
						vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ/2);
						LedState = false;
						Board_LED_Set(( char * ) pvParameters, LedState);
						vTaskDelay(configTICK_RATE_HZ);
						LedState = true;
						Board_LED_Set(2, LedState);
						vTaskDelay(2 * configTICK_RATE_HZ);
						}

		}
}

//static void vLEDTask2(void *pvParameters) {
//
//	while (1) {
//		bool LedState = true;
//		Board_LED_Set(2, LedState);
//		vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ/2);
//		LedState = false;
//		Board_LED_Set(2, LedState);
//		vTaskDelay(configTICK_RATE_HZ);
//		LedState = true;
//		Board_LED_Set(2, LedState);
//		vTaskDelay(2 * configTICK_RATE_HZ);
//	}
//}
//
//static void vLEDTask3(void *pvParameters) {
//
//	while (1) {
//		bool LedState = true;
//		Board_LED_Set(1, LedState);
//		vTaskDelay(3 * configTICK_RATE_HZ);
//		LedState = false;
//		Board_LED_Set(1, LedState);
//		vTaskDelay(configTICK_RATE_HZ);
//		LedState = true;
//		Board_LED_Set(1, LedState);
//		vTaskDelay(configTICK_RATE_HZ / 2);
//	}
//}

int main(void)
{
	prvSetupHardware();

	xTaskCreate(vLEDTaskF, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, 0, (tskIDLE_PRIORITY + 3UL),
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskF, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, 1, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskF, (signed char *) "vTaskLed1",
					configMINIMAL_STACK_SIZE, 2, (tskIDLE_PRIORITY + 2UL),
					(xTaskHandle *) NULL);

	vTaskStartScheduler();

	return 1;
}


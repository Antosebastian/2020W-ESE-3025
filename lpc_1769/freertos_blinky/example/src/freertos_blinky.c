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
	portTickType xLastWakeTime;
	xLastWakeTime = xTaskGetTickCount();
	while (1)
	{
			bool LedState = false;
			Board_LED_Set(( char * ) pvParameters, LedState);
			vTaskDelayUntil( &xLastWakeTime, 1000);
			LedState = true;
			Board_LED_Set(( char * ) pvParameters, LedState);
			vTaskDelayUntil( &xLastWakeTime, 3500);
	}
}

int main(void)
{
	prvSetupHardware();

	xTaskCreate(vLEDTaskF, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, 0, (tskIDLE_PRIORITY + 3UL),
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskF, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, 1, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskF, (signed char *) "vTaskLed1",
					configMINIMAL_STACK_SIZE, 2, (tskIDLE_PRIORITY + 1UL),
					(xTaskHandle *) NULL);

	vTaskStartScheduler();

	return 1;
}



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
		for(pvParameters = 0; pvParameters < 3; pvParameters++)
		{
//			vTaskDelayUntil( &xLastWakeTime, 1000);

		}
	}
}

int main(void)
{
	prvSetupHardware();

	xTaskCreate(vLEDTaskF, (signed char *) "Red",
				configMINIMAL_STACK_SIZE, 0, 1,
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskF, (signed char *) "Green",
				configMINIMAL_STACK_SIZE, 1, 1,
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTaskF, (signed char *) "Blue",
					configMINIMAL_STACK_SIZE, 2, 1,
					(xTaskHandle *) NULL);

	vTaskStartScheduler();

	return 1;
}



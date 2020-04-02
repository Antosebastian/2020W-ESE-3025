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

static void vLEDTask1(void *pvParameters)
{
	bool LedState = false;

		while (1) {
			bool LedState = false;
			Board_LED_Set(0, LedState);
			vTaskDelay(configTICK_RATE_HZ);
			LedState = true;
			Board_LED_Set(0, LedState);


			vTaskDelay(3 * configTICK_RATE_HZ + configTICK_RATE_HZ/2);
		}
}

static void vLEDTask2(void *pvParameters) {

	while (1) {
		bool LedState = true;
		Board_LED_Set(1, LedState);
		vTaskDelay(configTICK_RATE_HZ + configTICK_RATE_HZ/2);
		LedState = false;
		Board_LED_Set(1, LedState);
		vTaskDelay(configTICK_RATE_HZ);
		LedState = true;
		Board_LED_Set(1, LedState);
		vTaskDelay(2 * configTICK_RATE_HZ);
	}
}

static void vLEDTask3(void *pvParameters) {

	while (1) {
		bool LedState = true;
		Board_LED_Set(2, LedState);
		vTaskDelay(3 * configTICK_RATE_HZ);
		LedState = false;
		Board_LED_Set(2, LedState);
		vTaskDelay(configTICK_RATE_HZ);
		LedState = true;
		Board_LED_Set(2, LedState);
		vTaskDelay(configTICK_RATE_HZ / 2);
	}
}

int main(void)
{
	prvSetupHardware();

	xTaskCreate(vLEDTask1, (signed char *) "vTaskLed1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	xTaskCreate(vLEDTask2, (signed char *) "vTaskLed2",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);
//
	xTaskCreate(vLEDTask3, (signed char *) "vTaskLed3",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
					(xTaskHandle *) NULL);

	vTaskStartScheduler();

	return 1;
}


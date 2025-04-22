#include "SoftTimer.h"
#include "Types.h"
#include "C11Wrapper.h"
#include <time.h>
#include <stdio.h>
#include "../event_groups.h"
#include "datalogger.h"
#include "HN990.h"

#define TIM16_INTERVAL_MS 1000
EventGroupHandle_t myEventFlageTimer;

//EventGroupHandle_t myEventFlagsDataLogger;


SoftTimer::SoftTimer(void)//constructor
{
	My_Task_name = (char*)"SoftTimer task";
	activate(My_Task_name, 1000, NULL, 2, NULL);
}

SoftTimer::~SoftTimer(void)//disstructor
{

}
void SoftTimer::init(void)
{
	printf("initializing from SoftTimer....\n");
}
void SoftTimer::run_function(void)
{

	// Convert the interval in milliseconds to FreeRTOS ticks
	const TickType_t delayTicks = pdMS_TO_TICKS(TIM16_INTERVAL_MS);

	while (1)
	{
		EventBits_t receivedFlags = xEventGroupWaitBits(
			myEventFlageTimer,
			EV_START_TIMER,//| EV_FLAG_LOG_DATA | EV_FLAG_LOG_MANUAL_DATA | EV_FLAG_LOG_STOP,
			pdFALSE,       // Clear the flags after they are consumed
			pdFALSE,      // Wait for any of the specified bits
			portMAX_DELAY // Wait indefinitely
		);

		if ((receivedFlags & EV_START_TIMER) == EV_START_TIMER)
		{
			// Post the EV_FLAG_LOG_DATA flag to signal a task periodically
			xEventGroupSetBits(myEventFlagsDataLogger, EV_FLAG_LOG_DATA);
		}

		// Delay for TIM16_INTERVAL_MS before posting the flag again
		vTaskDelay(delayTicks);
	}

}
void SoftTimer::cleanUp(void)
{
	printf("Claening Up from SoftTimer....\n");
}
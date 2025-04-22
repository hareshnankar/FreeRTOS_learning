#include "HMIasKeyboard.h"
#include "Types.h"
#include "C11Wrapper.h"
#include <time.h>
#include <stdio.h>
#include "../event_groups.h"
#include "datalogger.h"
#include "HN990.h"
#include <conio.h>



#define TIM16_INTERVAL_MS 10

//EventGroupHandle_t myEventFlagsDataLogger;


HmiAsKeyboard::HmiAsKeyboard(void)//constructor
{
    printf("HmiAsKeyboard....\n");
	My_Task_name = (char*)"HmiAsKeyboard task";
	activate(My_Task_name, 1000, NULL, 2, NULL);
}

HmiAsKeyboard::~HmiAsKeyboard(void)//disstructor
{

}
void HmiAsKeyboard::init(void)
{
	printf("initializing from HmiAsKeyboard....\n");
}
void HmiAsKeyboard::run_function(void)
{

	// Convert the interval in milliseconds to FreeRTOS ticks
	const TickType_t delayTicks = pdMS_TO_TICKS(TIM16_INTERVAL_MS);

	while (1)
	{
       // printf("waiting for keys to press...\n");
        if (_kbhit())
        {  // Check if a key is pressed without blocking
            char key = _getch();
            if (key == 's')
            {
            
                printf("Start Logging...\n");
                xEventGroupSetBits(myEventFlageTimer, EV_START_TIMER);
            }
            else if (key == 'e')
            {
                printf("Stop Logging...\n");
                xEventGroupClearBits(myEventFlageTimer, EV_START_TIMER);
            }

            vTaskDelay(delayTicks);
        }
	}

}
void HmiAsKeyboard::cleanUp(void)
{
	printf("Claening Up from HmiAsKeyboard....\n");
}

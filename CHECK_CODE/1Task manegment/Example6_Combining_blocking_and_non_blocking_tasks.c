#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h"

#define mainDELAY_LOOP_COUNT 0x1FFFFF // Define a crude delay loop count

/* Print string function to simulate task output */
static void vPrintString(const char* pcString)
{
    printf("%s", pcString); // Output task string to the console
}

/* Continuous Processing Task */
void vContinuousProcessingTask(void* pvParameters)
{
    const char* pcTaskName = (const char*)pvParameters;

    for (;;)
    {
        vPrintString(pcTaskName);
        // Add a small delay to prevent CPU overload
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/* Periodic Task */
void vPeriodicTask(void* pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    const TickType_t xDelay3ms = pdMS_TO_TICKS(100);

    for (;;)
    {
        vPrintString("Periodic task is running\r\n");
        vTaskDelayUntil(&xLastWakeTime, xDelay3ms);
    }
}

/* Strings for continuous tasks */
static const char* pcTextForTask1 = "Task 1 is running\r\n";
static const char* pcTextForTask2 = "Task 2 is running\r\n";

int main(void)
{
    /* Create the continuous tasks with priority 1 */
    xTaskCreate(vContinuousProcessingTask, "Task 1", 1000, (void*)pcTextForTask1, 1, NULL);
    xTaskCreate(vContinuousProcessingTask, "Task 2", 1000, (void*)pcTextForTask2, 1, NULL);

    /* Create the periodic task with priority 2 */
   xTaskCreate(vPeriodicTask, "Task 3", 100, NULL, 2, NULL);

    /* Start the scheduler */
    vTaskStartScheduler();

    /* Should not reach here */
    return 0;
}

#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h" // For printf

#define mainDELAY_LOOP_COUNT 0x1FFFFF // Define a crude delay loop count

/* Print string function to simulate task output */
static void vPrintString(const char* pcString)
{
    printf("%s", pcString); // Output task string to console
}

void vTaskFunction(void* pvParameters)
{
    char* pcTaskName;
    TickType_t xLastWakeTime;
    /* The string to print out is passed in via the parameter. Cast this to a
    character pointer. */
    pcTaskName = (char*)pvParameters;
    /* The xLastWakeTime variable needs to be initialized with the current tick
    count. Note that this is the only time the variable is written to explicitly.
    After this xLastWakeTime is automatically updated within vTaskDelayUntil(). */
    xLastWakeTime = xTaskGetTickCount();
    /* As per most tasks, this task is implemented in an infinite loop. */
    for (;; )
    {
        /* Print out the name of this task. */
        vPrintString(pcTaskName);
        /* This task should execute every 250 milliseconds exactly. As per
        the vTaskDelay() function, time is measured in ticks, and the
        pdMS_TO_TICKS() macro is used to convert milliseconds into ticks.
        xLastWakeTime is automatically updated within vTaskDelayUntil(), so is not
        explicitly updated by the task. */
        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(250));
    }
}



/* Define the strings that will be passed in as the task parameters. These are
defined const and not on the stack to ensure they remain valid when the tasks are
executing. */
static const char* pcTextForTask1 = "Task 1 is running\r\n";
static const char* pcTextForTask2 = "Task 2 is running\r\n";
int main(void)
{
    /* Create the first task at priority 1. The priority is the second to last
    parameter. */
    xTaskCreate(vTaskFunction, "Task 1", 1000, (void*)pcTextForTask1, 1, NULL);
    /* Create the second task at priority 2, which is higher than a priority of 1.
    The priority is the second to last parameter. */
    xTaskCreate(vTaskFunction, "Task 2", 1000, (void*)pcTextForTask2, 2, NULL);
    /* Start the scheduler so the tasks start executing. */
    vTaskStartScheduler();

    /* Will not reach here. */
    return 0;
}


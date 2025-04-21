/* Includes for FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h" // For printf
/* Declare a variable that will be incremented by the hook function. */
volatile uint32_t ulIdleCycleCount = 0UL;

/* Print string and number function */
static void vPrintStringAndNumber(const char* pcString, uint32_t ulNumber)
{
    printf("%s: %u\n", pcString, ulNumber); // Print task name and counter
}

/* Task Function */
void vTaskFunction(void* pvParameters)
{
    char* pcTaskName;
    const TickType_t xDelay250ms = pdMS_TO_TICKS(250);

    /* The string to print out is passed in via the parameter. Cast this to a character pointer. */
    pcTaskName = (char*)pvParameters;

    /* Task implemented as an infinite loop. */
    for (;;)
    {
        /* Print out the name of the task and the idle cycle count. */
        vPrintStringAndNumber(pcTaskName, ulIdleCycleCount);

        /* Delay for a period of 250 milliseconds. */
        vTaskDelay(xDelay250ms);
    }
}



/* Idle hook function */
void vApplicationIdleHook(void)
{
    /* Idle hook must be enabled in FreeRTOSConfig.h by setting configUSE_IDLE_HOOK to 1. */
    ulIdleCycleCount++;
}

/* Main Function */
int main(void)
{
    /* Task parameters */
    char pcTaskName[] = "Task 1";

    /* Create Task 1 */
    xTaskCreate(vTaskFunction, "Task 1", 1000, (void*)pcTaskName, 1, NULL);

    /* Start the scheduler */
    vTaskStartScheduler();

    /* If the scheduler fails to start, this loop will be executed */
    for (;;)
        ;

    return 0; // Should never reach here
}

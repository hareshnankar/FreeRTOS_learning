/* Includes for FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h" // For printf, if needed

/* Function to simulate printing the task name */
static void vPrintString(const char* pcString)
{
    printf("%s", pcString);
}

/* Task 1 Implementation */
void vTask1(void* pvParameters)
{
    const char* pcTaskName = "Task 1 is running\r\n";
    volatile uint32_t ul; /* volatile to prevent optimization */
    for (;;)
    {
        /* Print the task name */
        vPrintString(pcTaskName);

        /* Crude delay loop */
        for (ul = 0; ul < 100000; ul++)
        {
            /* Busy-wait delay */
        }
    }
}

/* Task 2 Implementation */
void vTask2(void* pvParameters)
{
    const char* pcTaskName = "Task 2 is running\r\n";
    volatile uint32_t ul; /* volatile to prevent optimization */
    for (;;)
    {
        /* Print the task name */
        vPrintString(pcTaskName);

        /* Crude delay loop */
        for (ul = 0; ul < 100000; ul++)
        {
            /* Busy-wait delay */
        }
    }
}

/* Main Function */
int main(void)
{
    /* Create Task 1 */
    xTaskCreate(vTask1,/* Task function */
        "Task 1",      /* Task name */
        1000,          /* Stack size */
        NULL,          /* Task parameter */
        1,             /* Task priority */
        NULL);         /* Task handle */

    /* Create Task 2 */
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, NULL);

    /* Start the scheduler */
    vTaskStartScheduler();

    /* If the scheduler fails to start, this loop will be executed */
    for (;;)
        ;

    return 0; // Should never reach here
}

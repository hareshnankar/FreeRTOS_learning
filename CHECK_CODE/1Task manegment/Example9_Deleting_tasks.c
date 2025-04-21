/* Includes for FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h" // For printf

/* Function to simulate printing the task name */
static void vPrintString(const char* pcString)
{
    printf("%s", pcString);
}

/* Task Handle for Task 2 */
TaskHandle_t xTask2Handle = NULL;

/* Task 2 Implementation */
void vTask2(void* pvParameters)
{
    /* Print the name of this task and delete itself. */
    vPrintString("Task 2 is running and about to delete itself\r\n");

    /* Delete the task using its own handle. */
    vTaskDelete(xTask2Handle);
}


/* Task 1 Implementation */
void vTask1(void* pvParameters)
{
    const TickType_t xDelay100ms = pdMS_TO_TICKS(100UL);
    static int taskCreated = 0; // Flag to ensure Task 2 is created only once

    for (;;)
    {
        /* Print out the name of this task. */
        vPrintString("Task 1 is running\r\n");

      
        vPrintString("Creating Task 2\r\n");
        xTaskCreate(vTask2, "Task 2", 1000, NULL, 2, &xTask2Handle);

        /* Delay for 100 milliseconds. */
        vTaskDelay(xDelay100ms);
    }
}


/* Main Function */
int main(void)
{
    /* Create the first task at priority 1. */
    xTaskCreate(vTask1, "Task 1", 1000, NULL, 1, NULL);

    /* Start the scheduler so the tasks start executing. */
    vTaskStartScheduler();

    /* If the scheduler fails to start, this loop will execute. */
    for (;;);

    return 0; // Should never reach here
}

#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h" // For printf

#define mainDELAY_LOOP_COUNT 0x1FFFFF // Define a crude delay loop count

/* Print string function to simulate task output */
static void vPrintString(const char *pcString)
{
    printf("%s", pcString); // Output task string to console
}

void vTaskFunction(void *pvParameters)
{
    char *pcTaskName;
    volatile uint32_t ul; /* volatile to ensure ul is not optimized away */
    /* The string to print out is passed in via the parameter. Cast this to a character pointer. */
    pcTaskName = (char *)pvParameters;

    /* Infinite loop for the task */
    for (;;)
    {
        /* Print out the name of this task */
        vPrintString(pcTaskName);

        /* Crude delay loop */
        for (ul = 0; ul < mainDELAY_LOOP_COUNT; ul++)
        {
            /* Empty loop simulating delay */
        }
    }
}

/* Strings passed as task parameters */
static const char *pcTextForTask1 = "Task 1 is running\r\n";
static const char *pcTextForTask2 = "Task 2 is running\r\n";

int main(void)
{
    /* Create Task 1 */
    xTaskCreate(
        vTaskFunction,    /* Task function */
        "Task 1",         /* Task name for debugging */
        configMINIMAL_STACK_SIZE, /* Use minimal stack size for simulators */
        (void *)pcTextForTask1, /* Pass text to the task */
        1, /* Priority */
        NULL /* No task handle required for this example */
    );

    /* Create Task 2 */
    xTaskCreate(
        vTaskFunction, 
        "Task 2", 
        configMINIMAL_STACK_SIZE, 
        (void *)pcTextForTask2, 
        1, 
        NULL
    );

    /* Start the scheduler */
    vTaskStartScheduler();

    /* If the program reaches here, there was insufficient heap memory */
    for (;;)
    {
        // Infinite loop as fallback
    }
}

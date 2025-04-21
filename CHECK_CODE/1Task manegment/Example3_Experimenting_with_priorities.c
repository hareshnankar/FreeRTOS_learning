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

/* Define the strings that will be passed in as the task parameters. These are
defined const and not on the stack to ensure they remain valid when the tasks are
executing. */
static const char *pcTextForTask1 = "Task 1 is running\r\n";
static const char *pcTextForTask2 = "Task 2 is running\r\n";
int main( void )
{
 /* Create the first task at priority 1. The priority is the second to last 
 parameter. */
 xTaskCreate( vTaskFunction, "Task 1", 1000, (void*)pcTextForTask1, 1, NULL );
 /* Create the second task at priority 2, which is higher than a priority of 1.
 The priority is the second to last parameter. */
 xTaskCreate( vTaskFunction, "Task 2", 1000, (void*)pcTextForTask2, 2, NULL );
 /* Start the scheduler so the tasks start executing. */
 vTaskStartScheduler(); 
 
 /* Will not reach here. */
 return 0;
}


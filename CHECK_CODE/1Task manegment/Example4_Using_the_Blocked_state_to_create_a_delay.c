#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h" // For printf

#define mainDELAY_LOOP_COUNT 0x1FFFFF // Define a crude delay loop count

/* Print string function to simulate task output */
static void vPrintString(const char *pcString)
{
    printf("%s", pcString); // Output task string to console
}

void vTaskFunction( void *pvParameters )
{
char *pcTaskName;
const TickType_t xDelay250ms = pdMS_TO_TICKS( 250 );
 /* The string to print out is passed in via the parameter. Cast this to a
 character pointer. */
 pcTaskName = ( char * ) pvParameters;
 /* As per most tasks, this task is implemented in an infinite loop. */
 for( ;; )
 {
 /* Print out the name of this task. */
 vPrintString( pcTaskName );
 /* Delay for a period. This time a call to vTaskDelay() is used which places
 the task into the Blocked state until the delay period has expired. The 
 parameter takes a time specified in ‘ticks’, and the pdMS_TO_TICKS() macro
 is used (where the xDelay250ms constant is declared) to convert 250 
 milliseconds into an equivalent time in ticks. */
 vTaskDelay( xDelay250ms );
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


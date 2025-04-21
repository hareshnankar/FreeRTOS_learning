/* Includes for FreeRTOS */
#include "FreeRTOS.h"
#include "task.h"
#include "stdio.h" // For printf

/* Declare a variable that holds the handle of Task 2. */
TaskHandle_t xTask2Handle = NULL;


/* Function to simulate printing the task name */
static void vPrintString(const char* pcString)
{
    printf("%s", pcString);
}

/* Task 1 Implementation */
void vTask1(void* pvParameters)
{
    UBaseType_t uxPriority;

    /* Get the priority of the current task. */
    uxPriority = uxTaskPriorityGet(NULL);

    for (;;)
    {
        /* Print out the name of this task. */
        vPrintString("Task 1 is running\r\n");

        /* Increase Task 2's priority. */
        vPrintString("About to raise the Task 2 priority\r\n");
        vTaskPrioritySet(xTask2Handle, (uxPriority + 1));

        /* Task 1 will only execute again when Task 2 lowers its priority. */
    }
}

/* Task 2 Implementation */
void vTask2(void* pvParameters)
{
    UBaseType_t uxPriority;

    /* Get the priority of the current task. */
    uxPriority = uxTaskPriorityGet(NULL);

    for (;;)
    {
        /* Print out the name of this task. */
        vPrintString("Task 2 is running\r\n");

        /* Lower its priority to allow Task 1 to execute. */
        vPrintString("About to lower the Task 2 priority\r\n");
        vTaskPrioritySet(NULL, (uxPriority - 2));
    }
}


int main(void)
{
    /* Create Task 1 with priority 2. */
    xTaskCreate(vTask1, "Task 1", 1000, NULL, 2, NULL);

    /* Create Task 2 with priority 1 and save its handle. */
    xTaskCreate(vTask2, "Task 2", 1000, NULL, 1, &xTask2Handle);

    /* Start the scheduler to begin task execution. */
    vTaskStartScheduler();

    /* If the scheduler fails to start, this loop will execute. */
    for (;;);
}

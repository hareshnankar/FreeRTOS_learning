#include "application.h"
/* Includes for FreeRTOS */
#include "../FreeRTOS.h"
#include "../task.h"
#include "HN990.h"
#include "stdio.h" // For printf, if needed
#include "Datalogger.h"

/* Function to simulate printing the task name */
static void vPrintString(const char* pcString)
{
    printf("%s", pcString);
}
/* Task 1 Implementation */
void StartupTask(void* pvParameters)
{
    const char* pcTaskName = "Start-up task is now running\r\n";

    //creat the instrument 
    P_HN990 = new HN990(); //Used pointer which is declare  as a extern in HN990.H and define HN990.CPP
    P_HN990->InitializeEventGroup();
    P_HN990->createApplicationObjects();

    P_HN990->P_Datalogger->startSession();//using this call we post header evebt 

    for (;;)
    {
      //  printf("we stck here in StartupTask...\n");
    }
}
void Creat_Application(void)
{
    /* Create Task 1 */
    xTaskCreate(StartupTask,/* Task function */
        "StartupTask",      /* Task name */
        1000,          /* Stack size */
        NULL,          /* Task parameter */
        1,             /* Task priority */
        NULL);         /* Task handle */

}
/* Main Function */
int main(void)
{
    //creating an application 
    Creat_Application();
   
    /* Start the scheduler */
    vTaskStartScheduler();
 
    /* If the scheduler fails to start, this loop will be executed */
    for (;;)
    {
        printf("we stck here in main...\n");
    }

    return 0; // Should never reach here
}
#include "HN990.h"
#include "Datalogger.h"
#include "SoftTimer.h"
#include "stdio.h"

extern EventGroupHandle_t myEventFlagsDataLogger;

HN990* P_HN990;

HN990::HN990(void)//constructor
{

}

HN990::~HN990(void)//disstructor
{
	if (P_Datalogger)
	{
		printf("deleting datalogger...\n");
		delete P_Datalogger;
		P_Datalogger = NULL;
	}

}

void HN990::set_status(int value)
{
	status = value;
}

int HN990::get_status(void)
{
	return status;
}

void HN990 :: createApplicationObjects(void)
{
	
	P_SoftTimer = new SoftTimer(); 
	P_Datalogger = new Datalogger();
	//P_Datalogger->startTask();

}
// Declare the shared event group as extern in a header file


// Create it in one place (e.g., HN990.cpp or application.cpp)
void HN990::InitializeEventGroup(void) {
	myEventFlagsDataLogger = xEventGroupCreate();
	if (myEventFlagsDataLogger == NULL) {
		printf("Failed to create event group!\n");
		for (;;); // Halt
	}
}
#ifndef HM990_H // Header guard
#define HN990_H
#include "Datalogger.h"
#include "SoftTimer.h"
#include "../event_groups.h"
extern EventGroupHandle_t myEventFlagsDataLogger;

class HN990
{
private:
		int status;
public:
		HN990();/*Constructor*/
		~HN990();/*Distructor*/
		void set_status(int value);
		int get_status(void);
		void createApplicationObjects(void);
		void InitializeEventGroup(void);

		Datalogger* P_Datalogger;
		SoftTimer* P_SoftTimer;
};

extern HN990* P_HN990;
#endif
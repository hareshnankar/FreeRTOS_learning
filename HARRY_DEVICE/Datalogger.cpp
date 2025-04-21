#include "Datalogger.h"
#include "Types.h"
#include "C11Wrapper.h"
#include <time.h>
#include <stdio.h>
#include "../event_groups.h"
#include "HN990.h"

#define MAX_LINE_SIZE          360u  

EventGroupHandle_t myEventFlagsDataLogger;

char line[360 + 1u];

Datalogger::Datalogger(void)//constructor
{
	printf("datalogger construvctor called..\n");
	My_Task_name = (char *)"Datalogger task";
	activate(My_Task_name, 1000, NULL, 2, NULL);
	printf("after ........\n");
	// Create the event group
	//myEventFlagsDataLogger = xEventGroupCreate();

	//if (myEventFlagsDataLogger == NULL)
	//{
	//	// Handle event group creation failure
	//	for (;;)
	//	{
	//		printf("failed to create event group....\n");
	//	}
	//}
}
//void Datalogger::startTask() {
//	// Now the object is fully constructed, so it's safe to activate the task.
//	activate(My_Task_name, 5000, NULL, 3, NULL);
//}

Datalogger::~Datalogger(void)//disstructor
{

}
void Datalogger::init(void)
{
	printf("initializing from datalogger....\n");
}
void Datalogger::run_function(void)
{
	static int logging_started = 0;
	const TickType_t delayTicks = pdMS_TO_TICKS(1000);
	while (1)
	{
		//xEventGroupSetBits(myEventFlagsDataLogger, EV_FLAG_LOG_DATA);
		EventBits_t receivedFlags = xEventGroupWaitBits(
			myEventFlagsDataLogger,
			EV_FLAG_HEADER_INFO | EV_FLAG_LOG_DATA,//| EV_FLAG_LOG_DATA | EV_FLAG_LOG_MANUAL_DATA | EV_FLAG_LOG_STOP,
			pdTRUE,       // Clear the flags after they are consumed
			pdFALSE,      // Wait for any of the specified bits
			portMAX_DELAY // Wait indefinitely
		);

		if ((receivedFlags & EV_FLAG_HEADER_INFO) == EV_FLAG_HEADER_INFO)
		{
			setHeaderInfo();
			logging_started = 1;
		}

		if (((receivedFlags & EV_FLAG_LOG_DATA) == EV_FLAG_LOG_DATA ) && logging_started == true )
		{
			char text[MAX_LINE_SIZE];
			memset(text, 0x00, sizeof(text));
			//printf("logging the data...\n");
			prepareDummyDataLine(text);
			snprintf(line, (rsize_t)MAX_LINE_SIZE, "%s", text);
		}
		vTaskDelay(delayTicks);

	}

}
void Datalogger::cleanUp(void)
{
	printf("Claening Up from datalogger....\n");

}
void Datalogger::set_status(int value)
{
	status = value;
}

int Datalogger::get_status(void)
{
	return status;
}

void Datalogger::setHeaderInfo(void)
{
	//eDataLogError_t logError = (eDataLogError_t)E_DATALOG_ERROR_NONE;
	char text[MAX_LINE_SIZE];
	memset(line, 0x00, sizeof(line));
	memset(text, 0x00, sizeof(text));

	// instrument information
	headerPrepareInstrumentInfo(text);
	snprintf(line, (rsize_t)MAX_LINE_SIZE, "%s", text);
	//logError = writeToCache();
	headerPrepareColumnHeader(text);
	snprintf(line, (rsize_t)MAX_LINE_SIZE, "%s", text);

	//logError = writeToCache();
	
	//printf("setHeaderInfo from datalogger....\n");
}
void Datalogger::GetDummyTime(sTime_t *time_)
{

	time_t now;
	struct tm timeinfo;
	char buffer[26]; // Buffer for formatted time string
	time(&now);
	localtime_s(&timeinfo, &now);
	asctime_s(buffer, sizeof(buffer), &timeinfo); // Safe version of asctime



	time_->hours = timeinfo.tm_hour;

	time_->minutes = timeinfo.tm_min;

	time_->seconds = timeinfo.tm_sec;

	time_->milliseconds = 0;

	time_->day= timeinfo.tm_mday;
	time_->month = timeinfo.tm_mon;
	time_->year = timeinfo.tm_year;


}

void Datalogger::headerPrepareInstrumentInfo(char* text)
{
	sTime_t start_time;
	sTime_t end_time;
	sTime_t System_time;
	sTime_t System_date;

	//1. Instrument name 
	char file_name[50] = "PM990";

	//2.Instrument Serial Number
	char Instrument_Serial_Number[50] = "1234567890";

	//3. Start Time – log start time

	GetDummyTime(&start_time);


	//4. End Time – log End time
	GetDummyTime(&end_time);


	//5. Interval – Log Interval
	logInterval_t interval = FIVE_SEC_I;

	//6. Duration – Log duration
	logDuration_t log_duration = ONE_DAY_D;

	//7. Required Number of Data Points
	uint32_t  Required_Number_of_Data_Points = 8;

	//8. Number of Measurements
	uint32_t  Number_of_Measurements = 12;

	//9. Log Status (PENDING, RUNNING, END, PAUSED) //Indicate Running
	uint32_t  Log_Status = 2;

	GetDummyTime(&System_date);

	//11. system time  – system time time
	GetDummyTime(&System_time);


	Dec_point_formate log_formate = SCIENTFIC;



	/* arrenge that info in text */
	/*important note : remaimber that you need to remove \n\n from begning and replace single \n with , when you are satified with output*/

	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\r\n%cInstrumentName=%s%c", QUOTECHAR, file_name, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%cSerialNumber=%s%c", QUOTECHAR, Instrument_Serial_Number, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%02u:%02u:%02u.%03u%c", QUOTECHAR, C_STARTTIME, start_time.hours, start_time.minutes, start_time.seconds, start_time.milliseconds, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%02u:%02u:%02u.%03u%c", QUOTECHAR, C_ENDTIME, end_time.hours, end_time.minutes, end_time.seconds, end_time.milliseconds, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%u%c", QUOTECHAR, C_INTERVAL, interval, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%u%c", QUOTECHAR, C_DURATION, log_duration, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%u%c", QUOTECHAR, C_MESURNO, Required_Number_of_Data_Points, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%u%c", QUOTECHAR, C_LOGSTATUS, Required_Number_of_Data_Points, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%02u/%02u/%04u%c", QUOTECHAR, C_SYSTEMDATE, System_date.day, System_date.month, System_date.year, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n%c%s%02u:%02u:%02u.%03u%c", QUOTECHAR, C_SYSTEMTIME, System_time.hours, System_time.minutes, System_time.seconds, System_time.milliseconds, QUOTECHAR);


	//printf("%s", text);

}

void Datalogger::headerPrepareColumnHeader(char* text)
{
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "\n\n%c%s (hh:mm:ss)%c", QUOTECHAR, C_TIMESTAMP, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, C_MOISTURM2SENS, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, C_DEWPOINT, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, C_MOISTURMISP2SENS, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, C_PRESSURE, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, C_SENSTEMP, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, C_OXYPER, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, C_BORADTMP, QUOTECHAR);

	printf("%s", text);

}
void Datalogger::prepareDummyDataLine(char* text)
{
	// Clear the text buffer.
	text[0] = '\0';

	// Dummy values for each column.
	// For example:
	// Timestamp: dummy time string in (hh:mm:ss) format
	// Then some sensor readings as dummy strings.
	const char* dummyTimestamp = "12:34:56";
	const char* dummyMoistureM2 = "45.6";        // For C_MOISTURM2SENS
	const char* dummyDewPoint = "22.3";           // For C_DEWPOINT
	const char* dummyMoisturMISP2 = "50.0";         // For C_MOISTURMISP2SENS
	const char* dummyPressure = "1013";           // For C_PRESSURE (e.g., in hPa)
	const char* dummySenstemp = "36.2";           // For C_SENSTEMP (temperature)
	const char* dummyOxyper = "8.5";              // For C_OXYPER (oxygen percent or another unit)
	const char* dummyBoradTmp = "25.0";           // For C_BORADTMP

	// Build the CSV string. Here we use a series of snprintcatf() calls
	// (assumed to work like snprintf() with concatenation)
	snprintcatf(text, (size_t)MAX_LINE_SIZE, "%c%s%c", QUOTECHAR, dummyTimestamp, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, dummyMoistureM2, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, dummyDewPoint, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, dummyMoisturMISP2, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, dummyPressure, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, dummySenstemp, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, dummyOxyper, QUOTECHAR);
	snprintcatf(text, (size_t)MAX_LINE_SIZE, ",%c%s%c", QUOTECHAR, dummyBoradTmp, QUOTECHAR);

	// Optionally print the dummy data line
	printf("\n %s", text);
}

void Datalogger::startSession(void)
{
	// Set the EV_FLAG_HEADER_INFO flag
	printf("Starting a sesion by setting EV_FLAG_HEADER_INFO....\n");
	xEventGroupSetBits(myEventFlagsDataLogger, EV_FLAG_HEADER_INFO);
	// Task can terminate itself or continue looping

}
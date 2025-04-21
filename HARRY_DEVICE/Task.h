#pragma once
#ifndef TASK_H // Header guard
#define TASK_H
#include "../FreeRTOS.h"
#include "../task.h"
typedef	enum
{
	E_TASK_STATE_DORMANT = 0,
	E_TASK_STATE_CREATED,
	E_TASK_STATE_INITIALISING,
	E_TASK_STATE_RUNNING,
	E_TASK_STATE_SUSPENDED,
	E_TASK_STATE_STOPPING,
	E_TASK_STATE_TERMINATED,
	E_TASK_STATE_FAILED

} eTaskState_t;
class Task
{
private:
	static void task_runner(void* p_arg);
	
public:
	Task();/*Constructor*/
	virtual ~Task();/*Destructor*/
	void set_status(eTaskState value);
	eTaskState_t get_status(void);
	virtual void init(void);
	virtual void run_function(void);
	virtual void cleanUp(void);

	void activate(
		const char* const pcName,
		const uint16_t usStackDepth,
		void* const pvParameters,
		UBaseType_t uxPriority,
		TaskHandle_t* const pxCreatedTask);
protected :
	eTaskState_t My_Task_Status;
	char* My_Task_name;

};

#endif
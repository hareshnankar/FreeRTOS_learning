#include "Task.h"
#include "stdio.h"


Task::Task(void)//constructor
{
	My_Task_name = NULL;
	My_Task_Status = E_TASK_STATE_DORMANT;
}

Task::~Task(void)//destructor
{

}

eTaskState_t Task::get_status(void)
{
	return My_Task_Status;
}
void Task::init(void)
{
	// Do  nothing by default
}
void Task::run_function(void)
{
	// Do  nothing by default
}
void Task::cleanUp(void)
{
	// Do  nothing by default
}
void Task::activate(
	const char* const pcName,
	const uint16_t usStackDepth,
	void* const pvParameters,
	UBaseType_t uxPriority,
	TaskHandle_t* const pxCreatedTask)
{
	/* Create Task 1 */
	BaseType_t taskCreated = xTaskCreate((TaskFunction_t)Task::task_runner,    /* Task function */
		pcName,         /* Task name for debugging */
		usStackDepth, /* Use minimal stack size for simulators */
		this, /* Pass text to the task */
		uxPriority, /* Priority */
		pxCreatedTask /* No task handle required for this example */
	);
	if (taskCreated != pdPASS) {
		printf("Failed to create task: %s\n", pcName);
	}
}
void Task::task_runner(void *p_arg)
{
	Task *thisTask_ptr = (Task*)p_arg;
	thisTask_ptr->My_Task_Status = E_TASK_STATE_INITIALISING;
	thisTask_ptr->init();
	thisTask_ptr->My_Task_Status = E_TASK_STATE_RUNNING;
	thisTask_ptr->run_function();
	thisTask_ptr->My_Task_Status = E_TASK_STATE_STOPPING;
	thisTask_ptr->cleanUp();
	//thisTask_ptr->My_Task_Status = E_TASK_STATE_DORMANT;
}



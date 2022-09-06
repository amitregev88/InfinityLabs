/******************************************************************************/
/*	Project:	Scheduler												  	  */
/*	File:		tasker.c													  */
/*	Date: 		24.06.2022													  */
/*	Name: 		Sapir 														  */
/*	Reviewer:	Vered														  */
/*	Version: 	1.00														  */
/******************************************************************************/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

#include "tasker.h"
#include "pqueue.h"

struct task
{
	op_func_ty func;
	void *param;
	ilrd_uid_ty uid;
	time_t interval;
	time_t time_to_run;
};

/******************************************************************************/
enum {FALSE = 0, TRUE = 1};

/******************************************************************************/
task_ty *TaskCreate(int (*op_func_ty)(void *param) 
												 , void *param, time_t interval)
{
	task_ty *task = NULL;
	
	assert(0 != interval);
	
	task = (task_ty*) malloc (sizeof(task_ty));
	
	if (NULL == task)
	{
		return NULL;
	}
	
	task->func = op_func_ty;
	task->param = param;
	task->uid = UIDCreate();
	
	if (TRUE == UIDIsEqual(BadUID, task->uid))
	{
		free(task);
		task = NULL;
		
		return NULL;
	}
	
	task->interval = interval;
	task->time_to_run = interval + time(NULL);
	
	return task;
}
/******************************************************************************/
void TaskDestroy(task_ty *task)
{
	assert(NULL != task);
	
	free(task);
	task = NULL;
}
/******************************************************************************/
int TaskExecute(task_ty *task)
{
	assert(NULL != task);
	
	return (task->func(task->param));
}

/******************************************************************************/
ilrd_uid_ty GetUID(const task_ty *task)
{
	assert(NULL != task);
	
	return (task->uid);
}

/******************************************************************************/
time_t TaskGetTimeToRun(const task_ty *task)
{
	assert(NULL != task);
	
	return (task->time_to_run);
}

/******************************************************************************/
time_t TaskSetTimeToRun(task_ty *task)
{
	assert(NULL != task);
	
	task->time_to_run = task->interval + time(NULL);
	
	return task->time_to_run;
}

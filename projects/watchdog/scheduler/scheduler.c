/******************************************************************************/
/*	Project:	Scheduler												  	  */
/*	File:		scheduler.c													  */
/*	Date: 		24.06.2022													  */
/*	Name: 		Sapir 														  */
/*	Reviewer:	Vered														  */
/*	Version: 	1.00														  */
/******************************************************************************/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/
#include <time.h> /*time_t */
#include <unistd.h>/*sleep*/	

#include "pqueue.h"
#include "tasker.h"

#include "scheduler.h"


#define EMPTY 0

typedef enum {TASK_FAILURE = -1,
			  TASK_SUCCESS = 0,
			  TASK_REPEAT = 1} task_status_ty;
			  
typedef enum {RUN_FAILED = -2,
			  RUN_TASKFAIL = -1,
			  RUN_SUCCESS = 0, 
			  RUN_STOPPED = 1} run_status_ty;

enum {FALSE = 0, TRUE = 1};
enum {SUCCESS = 0, FAIL = 1};

struct scheduler
{
	pque_ty *pque;
	int is_stop;
};

/**************************Internal Functions**********************************/
int IsMatch(const void *task, void *task_to_remove);
static int IsHigherPriority(const void *task, void *new_task);
/******************************************************************************/

scheduler_ty *SchdCreate(void)
{
	scheduler_ty *scheduler = (scheduler_ty*)malloc(sizeof(scheduler_ty));
	
	if (NULL == scheduler)
	{
		return NULL;
	}
	
	scheduler->pque = PQCreate(IsHigherPriority);
	
	if (NULL == scheduler->pque)
	{
		free(scheduler);
		scheduler = NULL;
		
		return NULL;
	}
	
	scheduler->is_stop = FALSE;
	
	return scheduler;
}

/******************************************************************************/
static int IsHigherPriority(const void *task, void *new_task)
{
	
	if ((task_ty *)TaskGetTimeToRun(task) <= (
										task_ty *)TaskGetTimeToRun(new_task))
	{
		return TRUE;
	}
	
	return FALSE;
}

/******************************************************************************/
void SchdDestroy(scheduler_ty *scheduler)
{
	assert(NULL != scheduler);

	SchdClear(scheduler);
	PQDestroy(scheduler->pque);
	scheduler->pque = NULL;
	
	free(scheduler);
	scheduler = NULL;
}

/******************************************************************************/
ilrd_uid_ty SchdAdd(scheduler_ty *scheduler, time_t interval, 
											   op_func_ty task_ptr, void *param)
{
	task_ty *new_task = NULL;
	int status = FAIL;
	
	assert(NULL != scheduler);

	new_task = TaskCreate(task_ptr, param, interval);
	
	if (NULL == new_task)
	{
		return BadUID;
	}
	
	status = PQEnqueue(scheduler->pque, new_task);
	
	if (FAIL == status)
	{
		
		return BadUID;
	}
		
	return GetUID(new_task);
}

/******************************************************************************/
int SchdRemove(scheduler_ty *scheduler, ilrd_uid_ty task)
{
	task_ty *task_to_remove = NULL;

	assert(NULL != scheduler);
	assert(FALSE == UIDIsEqual(BadUID, task));
	
	task_to_remove = PQErase(scheduler->pque, IsMatch, &task);
	
	if (NULL == task_to_remove)
	{
		TaskDestroy(task_to_remove);
		task_to_remove = NULL;
		
		return FAIL;
	}
	
	TaskDestroy(task_to_remove);
	task_to_remove = NULL;
	
	return SUCCESS;
}

/******************************************************************************/
int IsMatch(const void *task, void *task_to_remove)
{
	assert(NULL != task);
	assert(NULL != task_to_remove);
	
	return (UIDIsEqual(GetUID((task_ty*)task), *(ilrd_uid_ty*)task_to_remove)); 
}
/******************************************************************************/
int SchdRun(scheduler_ty *scheduler)
{
	task_ty *task_to_run = NULL;
	time_t run_time = {0};
	time_t curr_time = {0};
	task_status_ty status = TASK_SUCCESS;
	run_status_ty run_status = RUN_SUCCESS;
	int enqueue_status = FAIL;
	int sleep_status = 0;
	
	assert(NULL != scheduler);
		
	scheduler->is_stop = FALSE;
	
	while (FALSE == SchdIsEmpty(scheduler) && (FALSE == scheduler->is_stop)
		   && (RUN_SUCCESS == run_status))		
	{
		task_to_run = PQPeek(scheduler->pque);
		run_time = TaskGetTimeToRun(task_to_run);
		sleep_status = (run_time -curr_time);
		
		while (0 < sleep_status)
		{
			sleep_status = sleep(run_time - time(NULL)); 
		}
		
		task_to_run = PQDequeue(scheduler->pque);
		
		status = TaskExecute(task_to_run);
				
		if (TASK_FAILURE == status)
		{
			TaskDestroy(task_to_run);
			task_to_run= NULL;
			
			run_status =  RUN_TASKFAIL;
		}
		
		if (TASK_SUCCESS == status)
		{
			TaskDestroy(task_to_run);
			task_to_run= NULL;
		}
		
		if (TASK_REPEAT == status)
		{
			TaskSetTimeToRun(task_to_run);
			enqueue_status = PQEnqueue(scheduler->pque, task_to_run);
			
			if (FAIL == enqueue_status)
			{
				TaskDestroy(task_to_run);
				task_to_run= NULL;
				
				run_status =  RUN_FAILED; 
			}	
		}		
	}
	
	if (TRUE == scheduler->is_stop)
	{
		return RUN_STOPPED;
	}
	
	return run_status;
	
}
/******************************************************************************/
void SchdStop(scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	
	scheduler->is_stop = TRUE;
}
/******************************************************************************/
size_t SchdSize(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	
	return PQSize(scheduler->pque);
}

/******************************************************************************/
int SchdIsEmpty(const scheduler_ty *scheduler)
{
	assert(NULL != scheduler);
	
	return PQIsEmpty(scheduler->pque);
}

/******************************************************************************/
void SchdClear(scheduler_ty *scheduler)
{
	task_ty *task_to_clear = NULL;
	assert(NULL != scheduler);
	
	while (FALSE == PQIsEmpty(scheduler->pque))
	{
		task_to_clear = PQDequeue(scheduler->pque);
		TaskDestroy(task_to_clear);
		task_to_clear = NULL;
	}
}

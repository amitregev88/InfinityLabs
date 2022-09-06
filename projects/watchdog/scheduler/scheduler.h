/**************************************************************************/
/*	Project:   Scheduler	                         					  */
/*  Name:      HRD25        		                                   	  */
/*	Date:      22.06.2022 						                          */
/*  File:	   Scheduler.h                                      		  */
/*	Version:   1.0											              */
/*	Reviewer:  Rina                                                    	  */
/**************************************************************************/
#ifndef __ILRD__SCHEDULER_H__
#define __ILRD__SCHEDULER_H__

#include <time.h>    /* time_t */
#include <stddef.h>  /*size_t  */	

#include "uid.h"

typedef struct scheduler scheduler_ty;

/****************************************************************************
* Type Description:  Pointer to a task function. 
*Arguments: void * to an outparameter.
*Return value: FAILURE = -1,
			  SUCCESS = 0,
			  REPEAT = 1.  
*****************************************************************************/
typedef int (*op_func_ty)(void *param);

/****************************************************************************
* Function Description:  Creates a new scheduler_ty.
*Arguments: None.
*Return value: 	Scheduler handler.
				Returns NULL in case of failure.
*Notes:  Needs to use SchdDestroy() at the end of use.
*Time complexity: O(1)
*****************************************************************************/
scheduler_ty *SchdCreate(void);
  
/****************************************************************************
* Function Description:  Removes the scheduler handler.
*Arguments: A scheduler handler to release.
*Return value: None.
*Notes:	Must be a valid pointer to a scheduler handler, otherwise
		behaviour is undefined.
*Time complexity: O(n)
*****************************************************************************/
void SchdDestroy(scheduler_ty *scheduler);

/****************************************************************************
* Function Description: Adds a new task to the scheduler. 
*Arguments: A scheduler handler, run intervals, pointer to the task to perform,
			extra void *param (optional).
*Return value: Returns the UID of the added task.
				Returns BadUID in case of failure.
*Notes:	Undefined behaviour if scheduler is invalid.
		Undefined behaviour if interval is 0. 			 	
		
*Time complexity: O(n). n = number of elements in the scheduler.
*****************************************************************************/
ilrd_uid_ty SchdAdd(scheduler_ty *scheduler, time_t interval, 
											op_func_ty task_ptr, void *param);

/****************************************************************************
* Function Description: Removes the task from the scheduler.  
*Arguments: Scheduler handler, task to remove.
*Return value: 	0 if removing succeeded.
			 	1 if the task to remove was not found.
*Notes:	Must be valid scheduler handler and task, otherwise behaviour is
		undefined.
*Time complexity: O(n). n = number of tasks in the scheduler.
*****************************************************************************/
int SchdRemove(scheduler_ty *scheduler, ilrd_uid_ty task);
  
/****************************************************************************
* Function Description:  Starts the scheduler.
*Arguments: Scheduler handler.
*Return value: FAIL = -2,
			  TASKFAIL = -1,
			  SUCCESS = 0, 
			  STOPPED = 1.
*Notes: Must be a valid scheduler, otherwise undefined behaviour. 
		In case of failure, run stop.
*Time complexity: O(n). n = number of performed tasks.
*****************************************************************************/
int SchdRun(scheduler_ty *scheduler);
  
/****************************************************************************
* Function Description: Stops the scheduler from running. 
*Arguments: Scheduler handler.
*Return value: None.
*Notes:	Must be a valid scheduler, otherwise undefined behaviour.
*Time complexity: O(1)
*****************************************************************************/
void SchdStop(scheduler_ty *scheduler);
  
/****************************************************************************
* Function Description:  Gets the number of tasks in the scheduler.
*Arguments: Scheduler handler.
*Return value: The number of tasks.
*Notes: Must be a valid scheduler, otherwise undefined behaviour.
*Time complexity: O(n)
*****************************************************************************/
size_t SchdSize(const scheduler_ty *scheduler);

/****************************************************************************
* Function Description: Checks if the scheduler has no tasks waiting. 
*Arguments: Scheduler handler.
*Return value: 	TRUE(1) if scheduler has no tasks.
				FALSE(0) otherwise.
*Notes:	Scheduler must be valid, otherwise undefined behaviour.
*Time complexity: O(1)
*****************************************************************************/
int SchdIsEmpty(const scheduler_ty *scheduler);
  
/******************************************************************************
* Function Description:	Clears all the tasks in the scheduler. 	` 
*Arguments: Scheduler handler.
*Return value:	None.
*Notes:	Scheduler must be valid, otherwise undefined behaviour.
*Time complexity: O(n). n = number of elements in the scheduler.
******************************************************************************/
void SchdClear(scheduler_ty *scheduler);

 #endif     /* __ILRD__SCHEDULER_H__              							  */ 
/*****************************************************************************/

/****************************************************************************/
/*	Project:	Scheduler API												*/
/*	File:		tasker.h													*/
/*	Date: 		23/06/2022													*/
/*	Name: 		HRD25														*/
/*	Reviewer:	Rina														*/
/*	Version: 	2.00														*/
/****************************************************************************/
#ifndef __ILRD_TASKER_H__
#define __ILRD_TASKER_H__

#include "scheduler.h"

typedef struct task task_ty;
			  
/*******************************Function Prototypes****************************/
/*******************************************************************************
* Function Description: Creates a new task.
*Arguments: Operation function, param (optional), interval.
*Return value: pointer to a task.
			   In case of failure ,returns NULL.
*Notes: need to TaskDestroy(). In case of interval = 0, undefined behavior.
*Time complexity: O(1).
*****************************************************************************/
task_ty *TaskCreate(op_func_ty func,  void *param, time_t interval);

/****************************************************************************
* Function Description: Removes the task.
*Arguments: A pointer to task.
*Return value: None
*Notes: Task must be valid.
*Time complexity: O(1)
*****************************************************************************/
void TaskDestroy(task_ty *task);

/****************************************************************************
* Function Description: Get the UID of the task given.
*Arguments: A pointer to task.
*Return value: UID of the task.
*Notes:  Task must be valid.
*Time complexity: O(1)
*****************************************************************************/
ilrd_uid_ty GetUID(const task_ty *task);

/****************************************************************************
* Function Description: Execute the task given from scheduler.
*Arguments: A pointer to task.
*Return value: 
	    	  FAILURE = -1,
			  SUCCESS = 0,
			  REPEAT = 1.
*Notes: Task must be valid.
*Time complexity: O(1).
*****************************************************************************/
int TaskExecute(task_ty *task);

/****************************************************************************
* Function Description: Gets task's time to run.
*Arguments: A pointer to task.
*Return value: The time until execution in seconds.
*Notes: Task must be valid.
*Time complexity: O(1).
*****************************************************************************/
time_t TaskGetTimeToRun(const task_ty *task);

/****************************************************************************
* Function Description: Sets the task next execution time.
*Arguments: A pointer to task.
*Return value: Return the next time to run.
*Notes: The task must to be valid.
*Time complexity: O(1).
*****************************************************************************/
time_t TaskSetTimeToRun(task_ty *task);

#endif /*	ifndef __TASKER_H__												*/
/*********************************End Of Header******************************/

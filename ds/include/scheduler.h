/*************************************************************
* OL124  project Scheduler
* 
* scheduler.h
* scheduler.c
* scheduler_test.c
* 
*Version 1.1 - only create, add, run - updated for now
******************************************************************/

#ifndef OL124_SCHEDULER_H
#define OL124_SCHEDULER_H

#include <stddef.h> /* size_t */
#include "uid.h" /* uid_ty */


typedef int (*task_ptr_ty)(void *param);
typedef struct scheduler scheduler_ty;


/***********************************************************************************
*--SchedulerCreate-- Create scheduler - return pointer to scheduler 
**************************************************************************************/
scheduler_ty *SchedulerCreate();

/*************************************************************************************
* --SchedulerAdd-- Add task to the scheduler return uid to this task. 
if fail return invalid uid
*
**************************************************************************************/
uid_ty SchedulerAdd(scheduler_ty *scheduler, size_t interval_in_sec, task_ptr_ty task_func, void* param);

/*************************************************************************************
*--SchedulerRun-- Run task. return 0 for success, 1 for failiure
**************************************************************************************/
int SchedulerRun(scheduler_ty *scheduler);

/*************************************************************************************
*--SchedulerStop-- Stop task. return 0 for success, 1 for failiure
**************************************************************************************/
int SchedulerStop(scheduler_ty *scheduler, task_ty *to_stop);

/*************************************************************************************
*--SchedulerRemove-- Remove task
**************************************************************************************/
void SchedulerRemove(scheduler_ty *scheduler, task_ty *to_remove);

/*************************************************************************************
* --SchedulerIsEmpty-- returns 1 in case is empty or 0 otherwise
**************************************************************************************/
int SchedulerIsEmpty(const scheduler_ty *scheduler);

/*************************************************************************************
* --SchedulerSize-- returns the size of the Scheduler
**************************************************************************************/
size_t SchedulerSize(const scheduler_ty *scheduler);

/*************************************************************************************
* --SchedulerClear-- remove all tasks in scheduler.
**************************************************************************************/
void SchedulerClear(scheduler_ty *scheduler);

/*************************************************************************************
*--SchedulerDestroy-- Delete scheduler 
**************************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler);

#endif /* OL124_SCHEDULER_H */

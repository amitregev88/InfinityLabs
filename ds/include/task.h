/*************************************************************
* OL124  project Scheduler //// TASK
* 
* task.h
* task.c
*  
*Version 1.1 - only create, add, run - updated for now
******************************************************************/

#ifndef OL124_SCHEDULER_TASK_H
#define OL124_SCHEDULER_TASK_H

#include <stddef.h> /* size_t */
#include "uid.h" /* uid_ty */
#include "scheduler.h"
#include <time.h>


typedef struct scheduler_task
{
    /* data */
    uid_ty UID;
    void *param;
    task_ptr_ty task_func;
    time_t time_of_act;
    size_t interval;
}task_ty;



/***********************************************************************************
*--- TaskSetUID --- Sets the UID into the task->interval field 
**************************************************************************************/
int TaskSetUID(task_ty *task);

/***********************************************************************************
*--- TaskGetUID --- Gets the UID of the task
**************************************************************************************/
uid_ty TaskGetUID(task_ty *task);

/***********************************************************************************
*--- TaskSetParam --- Sets the void *param into the task->param field for callback function
**************************************************************************************/
void TaskSetParam(task_ty *task, void *param);

/***********************************************************************************
*--- TaskGetParam --- Gets the void *param from the task->param field 
**************************************************************************************/
void *TaskGetParam(task_ty *task);
/***********************************************************************************
*--- TaskSetInterval --- Sets the interval into the task->interval field 
**************************************************************************************/
void TaskSetInterval(task_ty *task, size_t interval);

/***********************************************************************************
*--- TaskGetInterval ---Gets the interval of task  from the task->interval field 
**************************************************************************************/
size_t TaskGetInterval(task_ty *task);

/***********************************************************************************
*--- TaskSetAction --- Sets the run function to the task->task_ptr_ty 
**************************************************************************************/
void TaskSetAction(task_ty *task, task_ptr_ty action_func);

/***********************************************************************************
*--- TaskSetRunTime ---  set the time of the task 
**************************************************************************************/
void TaskSetRunTime(task_ty *task, time_t current_time);
/***********************************************************************************
--- TaskGetRunTime --- Gets the next run time 
**************************************************************************************/
time_t TaskGetRunTime(task_ty *task);

/***********************************************************************************
*--- TaskGetAction --- runs the action function
**************************************************************************************/
int TaskRunAction(task_ty *task);


#endif /* OL124_SCHEDULER_TASK_H */

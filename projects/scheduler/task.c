/*************************************************************
* OL124  project Scheduler
* 
* scheduler.h
* scheduler.c
* scheduler_test.c
* 
*Version 1.1 - only create, add, run - updated for now
******************************************************************/

#include <stddef.h> /* size_t */
#include "uid.h" /* uid_ty */
#include "pqueue.h"
#include "task.h"
#include "scheduler.h"
#include <assert.h>


/***********************************************************************************
*--- TaskSetUID --- Sets the UID into the task->interval field 
**************************************************************************************/
int TaskSetUID(task_ty *task)
{
    
    assert(NULL != task);

    task->UID = GetUID();
   
    return (UIDIsSame(UID_INVALID, task->UID));
 
}

/***********************************************************************************
*--- TaskGetUID --- Gets the UID of the task
**************************************************************************************/
uid_ty TaskGetUID(task_ty *task)
{
    
    assert(NULL != task);

    return (task->UID);
 
}

/***********************************************************************************
*--- TaskSetParam --- Sets the void *param into the task->param field 
**************************************************************************************/
void TaskSetParam(task_ty *task, void *param)
{
    assert(NULL != task);

    task->param = param;
}

/***********************************************************************************
*--- TaskGetParam --- Gets the void *param from the task->param field 
**************************************************************************************/
void *TaskGetParam(task_ty *task)
{
    assert(NULL != task);

    return task->param;
}




/***********************************************************************************
*--- TaskSetInterval --- Sets the interval into the task->interval field 
**************************************************************************************/
void TaskSetInterval(task_ty *task, size_t interval)
{
    assert(NULL != task);
    assert(interval > 0);

    task->interval = interval;
}

/***********************************************************************************
*--- TaskGetInterval --- Sets the interval into the task->interval field 
**************************************************************************************/
size_t TaskGetInterval(task_ty *task)
{
    assert(NULL != task);

    return (task->interval);

}

/***********************************************************************************
*--- TaskSetAction --- Sets the run function to the task->task_ptr_ty 
**************************************************************************************/
void TaskSetAction(task_ty *task, task_ptr_ty action_func)
{
    assert(NULL != task);
    assert(NULL != action_func);

    task->task_func = action_func;
}


/***********************************************************************************
*--- TaskSetRunTime --- Sets the next run time 
**************************************************************************************/
void TaskSetRunTime(task_ty *task, time_t current_time)
{
    assert(NULL != task);
    assert(-1 != current_time);

    task->time_of_act = current_time + task->interval;

}
/***********************************************************************************
*--- TaskGetRunTime --- Gets the next run time 
**************************************************************************************/
time_t TaskGetRunTime(task_ty *task)
{
    assert(NULL != task);
    return task->time_of_act;

}

/***********************************************************************************
*--- TaskGetAction ---runs the action function
***************************************************************************************/

int TaskRunAction(task_ty *task)
{
    assert(NULL != task);

    return (task->task_func(TaskGetParam(task)));

}
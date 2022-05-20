/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 05.17.22
* OL124 Scheduler Project (base on Priority Queue)
*************************************************************************************/

#include <stddef.h> /* size_t */
#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include <time.h>
#include "scheduler.h"
#include "task.h"
#include "pqueue.h"
#include "uid.h" 


struct scheduler 
{
    pqueue_ty *pq;
    size_t stop;
    
};

int TimeCmp(const void* a, const void* b)
{
    return ((int)TaskGetRunTime((task_ty *)b) - (int)TaskGetRunTime((task_ty *)a));
}
    

/***********************************************************************************
*--SchedulerCreate-- Create scheduler - return pointer to scheduler 
**************************************************************************************/
scheduler_ty *SchedulerCreate()
{
    scheduler_ty *schd = NULL;
    
     schd = malloc(sizeof(scheduler_ty));
   
    if (schd == NULL)
    {
        return NULL;
    }

    schd->pq = PQCreate(TimeCmp);
    if (schd->pq == NULL)
    {
        /*clean up*/
        free(schd);
        return NULL;
    }

    return schd;

}



/*************************************************************************************
* --SchedulerAdd-- Add task to the scheduler return uid to this task. 
if fail return invalid uid
*
**************************************************************************************/
uid_ty SchedulerAdd(scheduler_ty *scheduler, size_t interval_in_sec, task_ptr_ty task_func, void* param)
{
    
    task_ty *new_task = NULL;

    assert(NULL != scheduler);
    assert(interval_in_sec > 0);
    assert(NULL != task_func);
  
    new_task = malloc (sizeof(task_ty));
    if (NULL == new_task)
    {
        return UID_INVALID;
    }

  
    TaskSetUID(new_task);
     
     
    TaskSetParam(new_task, param);

    TaskSetInterval(new_task, interval_in_sec);

    TaskSetRunTime(new_task, time(NULL));

    TaskSetAction(new_task, task_func);
    
    if (PQEnQueue(scheduler->pq, new_task) == 1)
    {
        /*clean up*/
        free(new_task);
        return UID_INVALID;
    }

    return (TaskGetUID(new_task));

}



/*************************************************************************************
*--SchedulerRun-- Run task. return 0 for success, 1 for failiure
**************************************************************************************/
int SchedulerRun(scheduler_ty *scheduler)
{

    time_t current_time = 0;
    int time_to_sleep = 0;

    assert(NULL != scheduler);

    while(scheduler->stop != 1)
    {
        task_ty *task = NULL;

        task = PQDeQueue(scheduler->pq);

        current_time = time(NULL);
        if (-1 == current_time)
        {
            return 1;
        }
        
        time_to_sleep = (int)(TaskGetRunTime(task) - current_time);
        if(time_to_sleep > 0)
        {
            sleep(time_to_sleep);
        }

        TaskRunAction(task);

        current_time = time(NULL);
        if (-1 == current_time)
        {
            return 1;
        }

        TaskSetRunTime(task, current_time + TaskGetInterval(task));

        PQEnQueue(scheduler->pq, task);

    }
    scheduler->stop = 0;
    return 0;
/*
 Dequeue next_task
time_to_sleep = current_time - next_task_time
sleep(time_to_sleep)
run task_func
update next_task_time
enqueue next_task

*/

}

/*************************************************************************************
*--SchedulerStop-- Stop task.
**************************************************************************************/
void SchedulerStop(scheduler_ty *scheduler)
{
    assert(NULL != scheduler);
    scheduler->stop = 1;

}

/*************************************************************************************
*--SchedulerRemove-- Remove task with uid from scheduler
**************************************************************************************/
void SchedulerRemove(scheduler_ty *scheduler, uid_ty uid)
{


}

/*************************************************************************************
*--SchedulerDestroy-- Delete scheduler 
*************************************************************************************/
void SchedulerDestroy(scheduler_ty *scheduler)
{

 
 
 free(scheduler)

}

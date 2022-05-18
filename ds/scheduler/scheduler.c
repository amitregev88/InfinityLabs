/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 05.17.22
* OL124 Scheduler Project (base on Priority Queue)
*************************************************************************************/

#include <assert.h>	/* assert */
#include <stdlib.h>	/* malloc */
#include <assert.h>	/* assert */
#include "scheduler.h"
#include "pqueue.h"
#include "sortlist.h"
#include "uid.h"


struct scheduler 
{
	uid_ty uid;                 /* UID of the task (calling function) */
	task_ptr_ty *func;         /* pointer to function (task) */
};

struct compare 
{
    /* TODO */
};



/***********************************************************************************
*--SchedulerCreate-- Create scheduler - return pointer to scheduler 
**************************************************************************************/
scheduler_ty *SchedulerCreate()
{
    scheduler_ty *new_task =  NULL;
    
    uid_ty new_uid;

    new_uid = GetUID();
    if (new_uid == UID_INVALID)
    {
        return NULL;
    }

    new_task = (scheduler_ty *)malloc (scheduler_ty);
    if(NULL != new_task)
    {
        return NULL;
    }


    PQCreate(/*compare*/) = 

/*Creates Queue - return pointer to Que */
pqueue_ty *PQCreate(int (*cmp)(const void *, const void *));


}

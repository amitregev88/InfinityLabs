/*************************************************************
* OL124  project Scheduler //// TASK
*
* Amit Regev 
*  
*Scheduler 
******************************************************************/

/*************************************************************************************
* 
* 
* OL124 PQUEUE Test
*   
*************************************************************************************/


#include <stdio.h> /* printf */
#include "scheduler.h"
#include "task.h"


typedef struct 
{
    scheduler_ty *sched;
    
    uid_ty uid_task;
        
}task_remove_ty;


int TaskOne(void *a)
{
    printf("%s\n", (char *)a);
    return 0;
}

int TaskTwo(void *a)
{
    printf("%s\n", (char *)a);
    return 0;
}

int TaskThree(void *a)
{
    printf("%s\n", (char *)a);
    return 0;
}

int StopScheduler(void *a)
{

    static size_t count = 0;

    ++count;
    
    
    if (count > 0)
    {
        SchedulerStop((scheduler_ty *)a);
        printf("scheduler stop\n");
    }

    return 0;
}


int TaskRemove(void *a)
{
    task_remove_ty *iter = (task_remove_ty *)a;

    SchedulerRemove(iter->sched, iter->uid_task);
   
   return 0;    
}



int main()
{
    scheduler_ty *sched = SchedulerCreate();
/*
    uid_ty taskuid1;

    uid_ty taskuid2;

    uid_ty taskuid3;

    uid_ty taskuid4;

    uid_ty taskuid5;
*/

    char str1[] = "Task 1";

    char str2[] = "Task 2";

    char str3[] = "Task 3";

    task_remove_ty iter;

    /*taskuid1 =*/ SchedulerAdd(sched, 3, TaskOne, str1);

   /* taskuid2 = */SchedulerAdd(sched, 7, TaskTwo, str2);

  /*  taskuid3 =*/ SchedulerAdd(sched, 10, TaskThree, str3);

  /*  taskuid4 =*/ SchedulerAdd(sched,  31, TaskRemove, &iter);

    /*iter.sched = sched;
    iter.uid_task = taskuid1;*/

    /*taskuid5 = */SchedulerAdd(sched, 100, StopScheduler, sched);

    printf("Testing of SchedulerRemove function - task 1 will be removed after 31 sec without to stop the scheduler\n");

    SchedulerRun(sched);

    SchedulerDestroy(sched);

    return 0;
}


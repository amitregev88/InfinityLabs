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




#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)

int TaskOne(void *a)
{

    printf("task 1\n");
    return 0;

}

int TaskTwo(void *a)
{

    
    printf("task 2\n");

    return 0;

}

int TaskThree(void *a)
{

    printf("task 3\n");

    return 0;

}

int StopScheduler(void *a)
{

    static size_t count = 0;

    ++count;
    
    
    if (count > 0)
    {
        SchedulerStop((scheduler_ty *)a);

    }


     

    return 0;

}



int main()
{

    scheduler_ty *sched = SchedulerCreate();

    uid_ty taskuid1;

    uid_ty taskuid2;

    uid_ty taskuid3;

    uid_ty taskuid4;

   
    taskuid1 = SchedulerAdd(sched, 5, TaskOne, NULL);

    taskuid2 = SchedulerAdd(sched, 10, TaskTwo, NULL);

    taskuid3 = SchedulerAdd(sched, 15, TaskThree, NULL);

    taskuid4 = SchedulerAdd(sched, 30, StopScheduler, sched);

    SchedulerRun(sched);


    return 0;


}


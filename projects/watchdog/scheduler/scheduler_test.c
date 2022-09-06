/******************************************************************************/
/*	Project:	Scheduler 													  */
/*	File:		scheduler_test.c											  */
/*	Date: 		24.06.2022													  */
/*	Name: 		Sapir 														  */
/*	Reviewer:	Vered														  */
/*	Version: 	1.00														  */
/******************************************************************************/
#include <stdio.h> /*printf, puts*/

#include "scheduler.h"
#include "tasker.h"


#define MAX_COUNTER 5


typedef enum {TASK_FAILURE = -1,
			  TASK_SUCCESS = 0,
			  TASK_REPEAT = 1} task_status_ty;
			  
typedef enum {RUN_FAILED = -2,
			  RUN_TASKFAIL = -1,
			  RUN_SUCCESS = 0, 
			  RUN_STOPPED = 1} run_status_ty;

enum {FALSE = 0, TRUE = 1};
enum {SUCCESS = 0, FAIL = 1};
/*******************************Function Declarations**************************/

static void AllTest(void);
static void TestSchdCreate(void);
static void TestSchdAdd(void);
static void TestSchdSchdRemove(void);
static void TestSchdSize(void);
static void TestSchdIsEmpty(void);
static void TestSchdClear(void);
static void TestSchdRun(void);

/******************************************************************************/
task_status_ty TaskToAdd(void *counter);
task_status_ty StopFunc(void *scheduler);
task_status_ty IsEven(void *number);
task_status_ty Count(void *number);
/******************************************************************************/
static int status = 0;

/*******************************Function definitions***************************/

int main()
{
	AllTest() ;
	
	return 0;	
}

/******************************************************************************/
static void AllTest(void)
{
	/*TestSchdCreate();
	TestSchdAdd();*/
	TestSchdSchdRemove();
	/*TestSchdSize();
	TestSchdIsEmpty();
	TestSchdClear();
	TestSchdRun();*/
	
	if (SUCCESS == status)
  	{
  		puts("All tests passed\n");
  	}
  	
}

/******************************************************************************/
static void TestSchdCreate(void)
{
	scheduler_ty *scheduler = SchdCreate();
	
	if (NULL == scheduler)
	{
		puts( "Test SchdCreate failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	SchdDestroy(scheduler);
}

/******************************************************************************/
static void TestSchdAdd(void)
{
	scheduler_ty *scheduler = SchdCreate();
	ilrd_uid_ty task_uid = {0};
	size_t counter = 0;
	time_t interval	= 1; 
	
	task_uid = SchdAdd(scheduler, interval, TaskToAdd, &counter);
	
	if(TRUE == UIDIsEqual(BadUID, task_uid))
	{
		puts( "Test TestSchdAdd failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	if (TRUE == SchdIsEmpty(scheduler))
	{
		puts( "Test SchdIsEmpty failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	SchdDestroy(scheduler);
}

/******************************************************************************/
static void TestSchdSchdRemove(void)
{
	scheduler_ty *scheduler = SchdCreate();
	ilrd_uid_ty task_uid = {0};
	int remove_res = FAIL;
	int fail = 1;
	size_t counter = 0;
	time_t interval	= 2; 
	
	task_uid = SchdAdd(scheduler, interval, TaskToAdd, &counter);
	
	remove_res = SchdRemove(scheduler, task_uid);
	
	if (FALSE == SchdIsEmpty(scheduler))
	{
		puts( "Test SchdIsEmpty failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	if (fail == remove_res)
	{
		puts( "Test SchdRemove failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	SchdDestroy(scheduler);
}

/******************************************************************************/
static void TestSchdRun(void)
{
	scheduler_ty *scheduler = SchdCreate();

	size_t counter = 0;
	size_t number = 3;
	time_t interval	= 2; 
	time_t interval2 = 1; 
	run_status_ty run_status = RUN_FAILED;
	
	SchdAdd(scheduler, interval, TaskToAdd, &counter);
	run_status = SchdRun(scheduler);
		
	if (RUN_SUCCESS != run_status)
	{
		puts( "Test SchdRun SUCCEEDED case failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
	    		   
	   	++status;
	}


	SchdAdd(scheduler, interval2, StopFunc, scheduler);
	run_status = SchdRun(scheduler);
	
	if (RUN_STOPPED != run_status)
	{
		puts( "Test SchdRun STOPPED case failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	SchdAdd(scheduler, interval, IsEven, &number);
	run_status = SchdRun(scheduler);

	if (RUN_TASKFAIL != run_status)
	{
		puts( "Test SchdRun TASKFAIL case failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
	    
	 	++status;
	}
		
	SchdDestroy(scheduler);
}
/******************************************************************************/
static void TestSchdSize(void)
{
	scheduler_ty *scheduler = SchdCreate();

	size_t counter = 0;
	size_t i = 0;
	time_t interval	= 2; 
	
	for (i = 0; MAX_COUNTER > i; ++i)
	{
		SchdAdd(scheduler, interval, TaskToAdd, &counter);
	}

	if(MAX_COUNTER != SchdSize(scheduler))
	{
		puts( "Test TestSchdSize failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	SchdDestroy(scheduler);
}

/******************************************************************************/
static void TestSchdIsEmpty(void)
{
	scheduler_ty *scheduler = SchdCreate();

	size_t counter = 0;
	size_t i = 0;
	time_t interval	= 1; 
	
	if (FALSE == SchdIsEmpty(scheduler))
	{
		puts( "Test SchdIsEmpty failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	for (i = 0; MAX_COUNTER > i; ++i)
	{
		SchdAdd(scheduler, interval, TaskToAdd, &counter);

	}

	if (TRUE == SchdIsEmpty(scheduler))
	{
		puts( "Test SchdIsEmpty failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
       	++status;
	}
	
	SchdDestroy(scheduler);
}

/******************************************************************************/
static void TestSchdClear(void)
{
	scheduler_ty *scheduler = SchdCreate();
	
	size_t counter = 0;
	size_t i = 0;
	time_t interval	= 1; 
	
	for (i = 0; MAX_COUNTER >= i; ++i)
	{
		SchdAdd(scheduler, interval, TaskToAdd, &counter);
	}
	
	SchdClear(scheduler);
	
	if (FALSE == SchdIsEmpty(scheduler))
	{
		puts( "Test SchdClear failed\n");
		printf("Failed %s %d",__FILE__,__LINE__);
        	
    	++status;
	}
	
	SchdDestroy(scheduler);
}

/******************************************************************************/
task_status_ty TaskToAdd(void *counter)
{
	size_t i = 0;
	size_t loop = 5;
	
	for (i = 0;loop > i; ++i)
	{
		printf("counter = %lu\n", *(size_t*)counter);
		++*(size_t*)counter;
	}
	
	return TASK_SUCCESS;
}

/******************************************************************************/
task_status_ty StopFunc(void *scheduler)
{
	SchdStop((scheduler_ty*)scheduler);

	return TASK_SUCCESS;
}

/******************************************************************************/
task_status_ty IsEven(void *number)
{
	size_t even = 2;
	
	if (0 != *(size_t*)number % even)
	{
		return TASK_FAILURE;
	}

	return TASK_REPEAT;
}
/******************************************************************************/
task_status_ty Count(void *number)
{
	size_t i = 0;
	size_t loop = 5;
	size_t max_num = 3;
	
	if (max_num > *(size_t*)number)
	{
		return TASK_REPEAT;
	}
	
	for (i = 0;loop > i; ++i)
	{
		printf("task counter %lu\n", i );
	}
	
	return TASK_SUCCESS;	
}



/* gd prod.c watchdog.c ../scheduler/scheduler.c ../../ds/priority_queue_heap/pqueue.c ../../ds/heap/heap.c ../../ds/dynamic_vector/ ../../ds/uid/uid.c -g -o watchdog.out -I  ../../ds/include/ -lpthread  */

/****************************************************************************/
/*	Project:	Watcgdog													*/
/*	Date: 		28/08/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:																*/
/*	Version: 	1.00														*/
/****************************************************************************/

/******************************************************************************************************/
/*                                             includes                                               */
/******************************************************************************************************/
#define _POSIX_C_SOURCE 199309L
#include <stdio.h>  /*sprintf */
#include <string.h> /* strlen*/
#include <stdlib.h> /*setenv, getenv */
#include <errno.h>
#include <signal.h>    /*sigprocmask ,kill, sigemptyset, sigaddset .*/
#include <semaphore.h> /*sem_init */
#include <pthread.h>   /*pthread_create*/
#include <unistd.h>    /* getppid, fork*/

#include "wd.h"
#include "scheduler.h"
/******************************************************************************************************/
/*                                             macros                                                 */
/******************************************************************************************************/
#define WATCHDOG_PATH "/home/amit/git/projects/watchdog/watchdog.out"
/******************************************************************************************************/
/*                                             enums                                                  */
/******************************************************************************************************/
enum {SUCCESS = 0, FAILURE = 1};
enum {FALSE = 0, TRUE = 1};
/******************************************************************************************************/
/*                                             forward declaration                                    */
/******************************************************************************************************/
typedef struct
{
    size_t interval;
    size_t max_of_failures;
    char **argv;
    size_t wd_exist;
} mmy_args_ty;

typedef struct
{
    size_t max_of_failures;
    char **argv;
    pid_t wd_pid_env;
    size_t wd_exist;
    scheduler_ty *sched;
}sched_signal_data_ty;

typedef void* (*thread_routine_ty)(void *);
typedef int (*task_routine_ty)(void *);
/******************************************************************************************************/
/*                                              functions  declaration                                */
/******************************************************************************************************/
static char **AllocArgv(char **argv);
static void *PreapeThreadNRunWD(mmy_args_ty *data);
static int DisableEnableMasking(sigset_t *signalset, size_t set_mask);
static void SignalArrived(int param);
static void LetMeDie(int param);
static int CheckIfAliveNSendPing(sched_signal_data_ty *data);
static int ForkNExec(char** argv, pid_t *pid);
int WatchDog(size_t max_checks, time_t interval, char **argv, size_t wd_status);
int DoNotResuscitate(void);
/******************************************************************************************************/
/*                                             global variables                                       */
/******************************************************************************************************/
volatile size_t g_counter_failures = 0;
volatile size_t g_should_stop = 0;
volatile size_t g_wd_exist = 0;
volatile size_t g_is_other_ready = 0;
pthread_t g_wd_thread;
/******************************************************************************************************/
/*                                             make me immortal function definition                   */
/******************************************************************************************************/

int MMI(const size_t max_misses, const time_t interval, char *argv[])
{
    mmy_args_ty info;
    sigset_t signalmask = {0};

    info.wd_exist = TRUE;
    info.interval = interval;
	info.max_of_failures = max_misses;
    info.argv = argv;
	        
    /* masking SIGUSR1 and SIGUSR2*/ 
    DisableEnableMasking(&signalmask, TRUE);

    /*create thread for comunicate with WatchDog proceess and will revive him if needed */
    pthread_create(&g_wd_thread, NULL,(thread_routine_ty)PreapeThreadNRunWD, &info);

    /* waiting for WD thread to be created */
    while(!g_is_other_ready)
    {
        /* busy wait */
    }
    
    return SUCCESS;
}
/******************************************************************************************************/
/*                                             AllocArgv function definition                          */
/******************************************************************************************************/
static char **AllocArgv(char **argv)
{
    size_t counter_args = 0;
    size_t i = 0;
    size_t j = 0;

    char **argv_wd = NULL;

    while(NULL != argv[i])
    {
        ++counter_args;
        ++i;
    }

    argv_wd = (char **) malloc(counter_args * sizeof(char));

    argv_wd[0] = (char *) malloc ((strlen("wd_path") + 1) * sizeof(char));
    
    argv_wd[0] = "wd_path";

    for (i = 0, j = 0; j < counter_args; ++i, ++j)
    {
        argv_wd[i + 1] = (char *) malloc(strlen(argv[j]) + 1);
        
        memcpy(argv_wd[i], argv[j], strlen(argv[j] + 1));
    }

    return argv_wd;
}
/*******************************************************************************************************/
/*                                             PreapeThreadNRunWD function definition                  */
/*******************************************************************************************************/
static void *PreapeThreadNCallWD(mmy_args_ty *data)
{
    sigset_t signalunmask = {0};
    struct sigaction handler1;
    struct sigaction handler2;
    
    /*clear sa_mask field of sigaction struct */
    sigemptyset(&handler1.sa_mask);
    sigemptyset(&handler2.sa_mask);

    /*define handler function to SIGUSR1 and SIGUSR2*/ 
    handler1.sa_handler = SignalArrived;
    handler2.sa_handler = LetMeDie;
    
    /*init sigaction strucr for handler1 and handler2*/
    sigaction(SIGUSR1, &SignalArrived, NULL);
	sigaction(SIGUSR2, &LetMeDie, NULL);

    /*unmask signals for WD thread */
    DisableEnableMasking(&signalunmask, FALSE);

    /*preapre args for WD app from argv*/
    data->argv = AllocArgv(data->argv);

    WatchDog(data->interval, data->max_of_failures, data->argv, data->wd_exist);

    return NULL;
}
/*******************************************************************************************************/
/*                                             PreapeThreadNRunWD function definition                  */
/*******************************************************************************************************/
int WatchDog(size_t max_checks, time_t interval, char **argv, size_t wd_status)
{
	scheduler_ty *sched = NULL;
    char wd_pid[10] = {0};
    pid_t dest_pid;
    sched_signal_data_ty signal_info = {0};
    
    /* create scheduler */
    scheduler_ty *scheduler = SchedulerCreate();

    /* checks if this first time calling to WatchDog function  */
    if (NULL == getenv("WD_PID"))
    {
        /*char to int*/
        sprintf(wd_pid, "%d", getpid());
        setenv("WD_PID", wd_pid, 1);
        signal_info.wd_exist = FALSE;
        atomic_store(&g_is_other_ready, 0);
        atomic_store(&g_counter_failures, max_checks + 1);
    }

    dest_pid = atoi(getenv("WD_PID"));
    
    signal_info.wd_pid_env = dest_pid;
    signal_info.argv = argv;
    signal_info.max_of_failures = max_checks;
    signal_info.sched = scheduler;
    signal_info.wd_exist = wd_status;

    SchedulerAdd(scheduler,interval,(task_routine_ty)CheckIfAliveNSendPing, &signal_info);

    SchedulerRun(sched);

	return SUCCESS;
}
/*******************************************************************************************************/
/*                                             DisableEnableMasking function definition                */
/*******************************************************************************************************/
static int DisableEnableMasking(sigset_t *signalset, size_t set_mask)
{
    sigemptyset(&signalset);
	sigaddset(&signalset, SIGUSR1);
	sigaddset(&signalset, SIGUSR2);
    
    if (set_mask == 0)
    {
	    sigprocmask(SIG_UNBLOCK, &signalset, NULL);
    }
    else
    {
	    sigprocmask(SIG_BLOCK, &signalset, NULL);
    }

    return SUCCESS;
}
/*******************************************************************************************************/
/*              SignalArrived -  SIGUSR1 handler - function definition                                 */
/*******************************************************************************************************/
static void SignalArrived(int param)
{
	atomic_store(&g_counter_failures, 0);
	atomic_store(&g_is_other_ready, 1);

    printf("process ID --> %d\n", getpid());
    fflush(stdout);
}
/*******************************************************************************************************/
/*              LetMeDie -  SIGUSR2 handler - function definition                                      */
/*******************************************************************************************************/
static void LetMeDie(int param)
{
	atomic_store(&g_should_stop, 1);
}
/*******************************************************************************************************/
/*              CheckIfAliveNSendPing - function definition                                            */
/*******************************************************************************************************/
static int CheckIfAliveNSendPing(sched_signal_data_ty *data)
{
    /*check if dnr function is called*/
    if (atomic_load(&g_should_stop))
    {
        SchedulerStop(data->sched);
        return SUCCESS;
    }

    /*updae signal counter variable*/
    atomic_fetch_add(&g_counter_failures, 1);

    /*checks if g_counter is less or equal than  max possible failures and other process is ready */
    if ((atomic_load(&g_counter_failures) <= data->max_of_failures) && g_is_other_ready)
	{
		/* sending a signal */
		kill(data->wd_pid_env, SIGUSR1);
		printf("process ID ->> %d, sending a signal to process ID: %d\n",getpid(), data->wd_pid_env);

		/*data->wd_exist = FALSE;*/ /*for kill current process */
	}

    /*checks if wd isn't exist or g_counter is greater than  max possible failures*/    
    if (FALSE == data->wd_exist ||  data->max_of_failures > data->max_of_failures)
    {
        
        /*checks if wd is exist*/       
        if (data->wd_exist == TRUE)
		{
			printf("process ID ->> %d, killed by process ID: %d\n", data->wd_pid_env, getpid());

			/* kill another process */
			kill(data->wd_pid_env, SIGKILL);
		}
		
		data->wd_exist == TRUE;
		
		ForkNExec(data->argv, &data->wd_pid_env);
    }

    return SUCCESS;
}
/*******************************************************************************************************/
/*             ForkNExec - function definition                                                         */
/*******************************************************************************************************/
static int ForkNExec(char** argv, pid_t *pid)
{
	char curr_pid[10];
	
	/* reset the g_counter_failures to 0 */
	atomic_store(&g_counter_failures, 0);

	/* waiting for signal from child process */
	atomic_store(&g_is_other_ready, 0);

	sprintf(curr_pid, "%d", getpid());
	setenv("WD_PID", curr_pid, 1);

	/*update pid_wd_env in the struct*/
    *pid = fork();

	/*incase is a child process */
	if (0 == *pid)
	{
		execv(argv[0], argv);
	    printf("process ID ->> %d, created by process ID: %d\n", getpid(), *pid);
	}
		
	/*incase  parent process - waitng for signal from the child process */
	wait(NULL);

	return SUCCESS;
}
/*******************************************************************************************************/
/*             DoNotResuscitate - function definition                                                  */
/*******************************************************************************************************/
int DoNotResuscitate(void)
{
	kill(atoi(getenv("WD_PID")), SIGUSR2);

	pthread_join(&g_wd_thread, NULL);

	return SUCCESS;
}
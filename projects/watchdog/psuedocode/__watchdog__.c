
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
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>  /*sprintf */
#include <string.h> /* strlen*/
#include <stdlib.h> /*setenv, getenv */
#include <errno.h>
#include <signal.h>    /*sigprocmask ,kill, sigemptyset, sigaddset .*/
#include <semaphore.h> /*sem_init */
#include <pthread.h>   /*pthread_create*/
#include <unistd.h>    /* getppid, fork*/
#include <stdatomic.h> /*atomic_store*/

#include "wd.h"
#include "./scheduler/scheduler.h"
/******************************************************************************************************/
/*                                             macros                                                 */
/******************************************************************************************************/
#define WATCHDOG_PATH "./wd_app"
#define MAX_DIGITS 20
/******************************************************************************************************/
/*                                             enums                                                  */
/******************************************************************************************************/
enum
{
    SUCCESS = 0,
    FAILURE = 1
};
enum
{
    FALSE = 0,
    TRUE = 1
};
/******************************************************************************************************/
/*                                             forward declaration                                    */
/******************************************************************************************************/
typedef struct
{
    size_t interval;        /* mmi-->thread_func --> wd_func */
    size_t max_of_failures; /* mmi->thread_func --> wd_func*/
    char **argv;            /* mmi->thread_func --> AllocArgv ->wd_func  */
} mmi_args_ty;

typedef struct
{
    size_t max_of_failures; /*wd_func --> task_func*/
    char **argv;            /*wd_func --> task_func*/
    scheduler_ty *sched;    /*wd_func --> task_func*/
} sched_signal_data_ty;

typedef void *(*thread_routine_ty)(void *);
typedef int (*task_routine_ty)(void *);
/******************************************************************************************************/
/*                                              functions  declaration                                */
/******************************************************************************************************/
static char **AllocArgv(mmi_args_ty *info);
static void *PreapeThreadNCallWD(mmi_args_ty *data);
static int DisableEnableMasking(sigset_t *signalset, size_t set_mask);
static void SignalArrived(int sig_num, siginfo_t *infom, void *param);
static void LetMeDie(int sig_num, siginfo_t *infom, void *param);
static int CheckIfAliveNSendPing(sched_signal_data_ty *data);
static int ForkNExec(char **argv);
static int SetHandlers(void);
static void SetFlagsAccordingToParentStatus(size_t max_of_misses);
int WatchDog(char **argv, size_t max_checks, time_t interval);
int DoNotResuscitate(void);
/******************************************************************************************************/
/*                                             global variables                                       */
/******************************************************************************************************/
volatile size_t g_counter_failures = 0;
volatile size_t g_should_stop = 0;
volatile pid_t g_other_pid = 0;
volatile size_t g_is_other_ready = 0;
pthread_t g_wd_thread;
/******************************************************************************************************/
/*                                             make me immortal function definition                   */
/******************************************************************************************************/

int MMI(const size_t max_misses, const time_t interval, char *argv[])
{
    mmi_args_ty info;
    sigset_t signalmask = {0};

    info.interval = interval;
    info.max_of_failures = max_misses;
    info.argv = argv;

    /* masking SIGUSR1 and SIGUSR2*/
    DisableEnableMasking(&signalmask, TRUE);

    /*create thread for comunicate with WatchDog proceess and will revive him if needed */
    pthread_create(&g_wd_thread, NULL, (thread_routine_ty)PreapeThreadNCallWD, &info);

    /* waiting for WD thread to be created */
    while (!g_is_other_ready) /*TODO time out*/
    {
        /* busy wait */
    }

    return SUCCESS;
}
/******************************************************************************************************/
/*                                             AllocArgv function definition                          */
/******************************************************************************************************/
static char **AllocArgv(mmi_args_ty *info)
{
    size_t counter_args = 0;
    size_t i = 0;

    char **argv_wd = NULL;

    while (NULL != info->argv[i])
    {
        ++counter_args;
        ++i;
    }

    argv_wd = (char **)malloc(counter_args * sizeof(char *));

    argv_wd[0] = WATCHDOG_PATH;

    argv_wd[1] = (char *)malloc(sizeof(char) * MAX_DIGITS);
    sprintf(argv_wd[1],"%lu", info->max_of_failures);

    argv_wd[2] = (char *)malloc(sizeof(char) * MAX_DIGITS);
    sprintf(argv_wd[2],"%lu", info->interval);

    
    for (i = 0; i < counter_args; ++i)
    {
        argv_wd[i + 3] = info->argv[i];
    }

    return argv_wd;
}
/*******************************************************************************************************/
/*                                             PreapeThreadNRunWD function definition                  */
/*******************************************************************************************************/
static void *PreapeThreadNCallWD(mmi_args_ty *data)
{
    char **alloc_argv = NULL;
    int i = 0;

    /*preapre args for WD app from argv*/
    alloc_argv = AllocArgv(data);

    WatchDog(alloc_argv, data->max_of_failures, data->interval);

    free(alloc_argv[1]);
    free(alloc_argv[2]);  
    free(alloc_argv);

    return NULL;
}
/*******************************************************************************************************/
/*                                             PreapeThreadNRunWD function definition                  */
/*******************************************************************************************************/
int WatchDog(char **argv, size_t max_checks, time_t interval)
{
    scheduler_ty *sched = NULL;
    sigset_t signalunmask = {0};
    sched_signal_data_ty signal_info = {0};
    scheduler_ty *scheduler = NULL;


    SetHandlers();

    /*unmask signals for WD thread */
    DisableEnableMasking(&signalunmask, FALSE);

    signal_info.argv = argv;
    signal_info.max_of_failures = max_checks;
    signal_info.sched = sched;

    /* create scheduler */
    scheduler = SchedulerCreate();

    SchedulerAdd(scheduler, interval, (task_routine_ty)CheckIfAliveNSendPing, &signal_info);

    SetFlagsAccordingToParentStatus(max_checks);

    SchedulerRun(scheduler);

    SchedulerDestroy(scheduler);

    return SUCCESS;
}
/*******************************************************************************************************/
/*                               DisableEnableMasking function definition                              */
/*******************************************************************************************************/
static int DisableEnableMasking(sigset_t *signalset, size_t set_mask)
{
    sigemptyset(signalset);
    sigaddset(signalset, SIGUSR1);
    sigaddset(signalset, SIGUSR2);

    if (set_mask == 0)
    {
        sigprocmask(SIG_UNBLOCK, signalset, NULL);
    }
    else
    {
        sigprocmask(SIG_BLOCK, signalset, NULL);
    }

    return SUCCESS;
}
/*******************************************************************************************************/
/*              SignalArrived -  SIGUSR1 handler - function definition                                 */
/*******************************************************************************************************/
static void SignalArrived(int sig_num, siginfo_t *infom, void *param)
{
    param = param;
    infom = infom;
    sig_num = sig_num;

    __atomic_store_n(&g_counter_failures, 0, __ATOMIC_SEQ_CST);
    __atomic_store_n(&g_is_other_ready, 1, __ATOMIC_SEQ_CST);

    printf("process ID --> %d\n", getpid());
    fflush(stdout);
}
/*******************************************************************************************************/
/*              LetMeDie -  SIGUSR2 handler - function definition                                      */
/*******************************************************************************************************/
static void LetMeDie(int sig_num, siginfo_t *infom, void *param)
{
    param = param;
    infom = infom;
    sig_num = sig_num;

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
    __atomic_fetch_add(&g_counter_failures, 1, __ATOMIC_SEQ_CST);

    /*checks if g_counter is less or equal than  max possible failures and other process is ready */
    if ((atomic_load(&g_counter_failures) <= data->max_of_failures) && g_is_other_ready)
    {
        /* sending a signal */
        kill(g_other_pid, SIGUSR1);
        printf("process ID ->> %d, sending a signal to process ID: %d\n", getpid(), g_other_pid);
        /* check if errno updated to no pid */
       /* g_other_pid = 0; */    /*for kill current process */
    }

    /*checks if wd isn't exist or g_counter is greater than  max possible failures*/
    if (0 == g_other_pid || g_counter_failures > data->max_of_failures)
    {
        /*checks if wd is exist*/
        if (0 != g_other_pid)
        {
            printf("process ID ->> %d, killed by process ID: %d\n", g_other_pid, getpid());

            /* kill another process */
            kill(g_other_pid, SIGKILL);
        }

        ForkNExec(data->argv);
    }

    return SUCCESS;
}
/*******************************************************************************************************/
/*             ForkNExec - function definition                                                         */
/*******************************************************************************************************/
static int ForkNExec(char **argv)
{
    char curr_pid[10];
    pid_t pid;

    /* reset the g_counter_failures to 0 */
    __atomic_store_n(&g_counter_failures, 0, __ATOMIC_SEQ_CST);

    /* waiting for signal from child process */

    __atomic_store_n(&g_is_other_ready, 0, __ATOMIC_SEQ_CST);

    /*update pid_wd_env in the struct*/
    pid = fork();


    /*incase is a child process */
    if (0 == pid)
    {
        /*char to int*/
        sprintf(curr_pid, "%d", getppid());
        setenv("WD_PID", curr_pid, 1);
        printf("process ID ->> %d, created by process ID: %d\n", getpid(), g_other_pid);
        execvp(argv[0], argv);
    }
    
    /*update the g_other_pid to WD_PID*/
    __atomic_store_n(&g_other_pid, pid, __ATOMIC_SEQ_CST);

    /*incase  parent process - waitng for signal from the child process */
    /*wait(NULL);*/

    return SUCCESS;
}
/*******************************************************************************************************/
/*             DoNotResuscitate - function definition                                                  */
/*******************************************************************************************************/
int DoNotResuscitate(void)
{
    kill(atoi(getenv("WD_PID")), SIGUSR2);

    pthread_join(g_wd_thread, NULL);

    return SUCCESS;
}
/*******************************************************************************************************/
/*             SetHandlers - function definition                                                       */
/*******************************************************************************************************/
static int SetHandlers(void)
{
    struct sigaction handler1;
    struct sigaction handler2;

    /*clear sa_mask field of sigaction struct */
    sigemptyset(&handler1.sa_mask);
    sigemptyset(&handler2.sa_mask);

    /*define handler function to SIGUSR1 and SIGUSR2*/
    handler1.sa_sigaction = SignalArrived;
    handler2.sa_sigaction = LetMeDie;
    handler1.sa_flags = SA_SIGINFO;
    handler2.sa_flags = SA_SIGINFO;


    /*init sigaction strucr for handler1 and handler2*/
    sigaction(SIGUSR1, &handler1, NULL);
    sigaction(SIGUSR2, &handler2, NULL);

    return SUCCESS;
}
/*******************************************************************************************************/
/*             SetFlagsAccordingToParentStatus - function definition                                   */
/*******************************************************************************************************/
static void SetFlagsAccordingToParentStatus(size_t max_of_misses)
{
    /*if parent is not exist*/
    if (NULL == getenv("WD_PID"))
    {
        __atomic_store_n(&g_counter_failures, max_of_misses, __ATOMIC_SEQ_CST);
        __atomic_store_n(&g_is_other_ready, 0, __ATOMIC_SEQ_CST);
        __atomic_store_n(&g_other_pid, 0, __ATOMIC_SEQ_CST);
    }
    else
    {
        __atomic_store_n(&g_counter_failures, 0, __ATOMIC_SEQ_CST);
        __atomic_store_n(&g_is_other_ready, 1, __ATOMIC_SEQ_CST);
        __atomic_store_n(&g_other_pid, atoi(getenv("WD_PID")), __ATOMIC_SEQ_CST);
    }
}


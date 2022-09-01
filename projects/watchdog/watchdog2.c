
/* gd prod.c watchdog.c ../scheduler/scheduler.c ../../ds/priority_queue_heap/pqueue.c ../../ds/heap/heap.c ../../ds/dynamic_vector/ ../../ds/uid/uid.c -g -o watchdog.out -I  ../../ds/include/ -lpthread  */


#include <stdio.h>  /*sprintf */
#include <string.h> /*strcmp*/
#include <stdlib.h> /*setenv, getenv , unsetenv*/
#include <errno.h>
#include <signal.h>    /*sigprocmask ,kill*/
#include <semaphore.h> /*sem_init */
#include <time.h>
#include <pthread.h>   /*pthread_create*/
#include <unistd.h>    /* getppid, fork*/

#include "watchdog.h"
#include "scheduler.h"

#define WATCHDOG_PATH "/home/amit/git/projects/watchdog/watchdog.out"

enum
{
    SUCCESS = 0,
    FAILURE = 1
};

typedef struct
{
    size_t interval;

    size_t max_of_failures;

    char **argv;

    
} communicate_info_ty;

volatile int g_counter_failures = 0;
volatile int g_should_wait_for_ret_val = 1;
sem_t g_signal_arrived;

/*int MakeMeImmortal(size_t interval, size_t max_of_failures, const char **argv)*/

int MMI(const size_t max_misses, const time_t interval, char *argv[])
{

    pthread_t pingpong_thread;
    sigset_t signalmask = {0};
    char *watchdog_path_exe = WATCHDOG_PATH;
    char *client_path_exe = NULL;
    int status = 0;
    communicate_info_ty signal;
    

    signal.interval = interval;
    signal.max_of_failures = max_misses;
    signal.argv = argv;

    status = sem_init(&g_signal_arrived, 0, 0);
    if (status)
    {
        perror("sem_init failed\n");
        return FAILURE;
    }
       
        /* masking SIGUSR1 and SIGUSR2*/

        sigemptyset(&signalmask);
		sigaddset(&signalmask, SIGUSR1);
		sigaddset(&signalmask, SIGUSR2);
		sigprocmask(SIG_BLOCK, &signalmask, NULL);
      

        /*create thread*/

        status = pthread_create(&pingpong_thread, NULL,KeepAlive, &signal);
        if(status)
        {
            perror("pthread_create faild\n");
        }


        /*waiting for signal from child process */

        sem_timedwait(&g_signal_arrived); /* 1. TODO*/

        /*if time out... -> return FAILURE */
    
    return SUCCESS;
}


void *KeepAlive(void *param)
{
    int status = 0;
    char str_pid[10];
    
    sigset_t signalmask = {0};
    uid_ty uid_task;
    pid_t my_pid = getpid();
    pid_t my_parent_pid = getppid();
    pid_t wd_pid;
    struct sigaction handler;
    size_t interval = ((communicate_info_ty *)param)->interval;
    size_t max_failures = ((communicate_info_ty *)param)->max_of_failures;
    char **argv = ((communicate_info_ty *)param)->argv;
    scheduler_ty *sched = NULL;


    /* set a signal handler function for SIGUSR1 */

    handler.sa_sigaction = ResetFlagComu;
    handler.sa_flags = 0; 

    /*unmasking SIGUSR1 and SIGUSR2  */

    sigemptyset(&signalmask);
	sigaddset(&signalmask, SIGUSR1);
	sigaddset(&signalmask, SIGUSR2);
	sigprocmask(SIG_UNBLOCK, &signalmask, NULL);

    

    /* function handler - reset the g_counter_failures*/
    void ResetFlagComu(int sig_num, siginfo_t *infom, void *param)
    {

        __atomic_store_8(&g_counter_failures, 0, __ATOMIC_SEQ_CST);
    }

    int TaskSendSignal(void *param)
    {
        int status = 0;

        communicate_info_ty info;
        info.max_of_failures = ((communicate_info_ty *)param)->max_of_failures;
        info.sched = ((communicate_info_ty *)param)->sched;
        
        if (g_counter_failures == info.max_of_failures)
        {

            SchedulerStop(info.sched);

            status = kill(SIGUSR1, SIGTERM);
            if (status)
            {
                perror("kill func failed\n");
                return FAILURE;
            }

            unsetenv("WD_PID");
        }

        atomic_fetch_add_explicit(&g_counter_failures, 1, __ATOMIC_SEQ_CST);

        return SUCCESS;
    }

    void SwapPtr(char **p1, char **p2)
    {
        char *tmp = NULL;

        tmp = *p1;
        *p1 = *p2;
        *p2 = tmp;
    }


    int WatchDog()
    {


    status = sigaction(SIGUSR1, &ResetFlagComu, NULL);
    if (status)
    {
        perror("sigaction failed\n");
        return FAILURE;
    }



    if (NULL == getenv("WD_PID")) /*check if parent process is not exist*/
    {

        switch (wd_pid = fork())
        {

        case -1: /*incase fork is fail*/

            perror("fork faild\n");
            return FAILURE;

            break;

        case 0: /*child process*/

            execv(argv[0], pass_data);

            break;

        default: /*parent process */

            sprintf(str_pid, "%d", my_pid); /*int to str*/
            setenv("WD_PID", str_pid, 1);   /*set env */

            break;
        }
    }

    sched = SchedulerCreate();
    assert(sched != NULL);

    /*  adding task to scheduler (sending a signal)*/
    uid_task = SchedulerAdd(sched, interval,(task_ptr_ty)TaskSendSignal, param);

    
    
    
    while(1)
    {

    /*check if the current process is child*/
    if (my_parent_pid == getenv("WD_PID"))
    {

        /*send the first signal*/

        status = SchedulerRun(sched);

        if (status)
        {
            kill(my_parent_pid, SIGKILL);
        }
    }
    else /*incase the current process is parent*/
    {
       
        /*sem_wait(&g_sema);/*wait for signal from the child  /* timeout*/

        status = SchedulerRun(sched);

        if (status)
        {
            kill(my_parent_pid, SIGKILL);
        }

    }
    sem_destroy(&g_sema);
    }
        

}





    }
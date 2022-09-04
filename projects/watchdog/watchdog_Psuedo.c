/*


global variebls:

g_counter

g_is_other ready

g_should_run

enum {FALSE = 0 , TRUE = 1}
enum {SUCCESS = 0 , FAILURE = 1}



struct1 -> pass all data are needed from mmi function to preparation_for_wd_func and wd functions  
{
    char **argv1 - preparation_for_wd_func --> AllocArgv

    thread_created_flag --> preparation_for_wd_func-->watchdog()-->schedulerAdd-->Task-->ForkNExec

    interval --> preparation_for_wd_func-->watchdog()-->schedulerAdd

    max_missess --> preparation_for_wd_func-->watchdog()-->schedulerAdd--> Task

    scheduler pointer - watchdog()-->schedulerAdd-->Task



}




int MMI(const max_misses, const time_t interval, char *argv[])
{
    1. disable_enable_masking(*sig_set_t , int set) ---> enable

    2. create thread -> preparation_for_WD(struct 1)

    3. busy wait- waiting for thread_created_flag change to 1.
}


2. preparation_for_WD(struct 1)

    2.1 sigaction for sigusr1 + sigusr2

    2.2 disable_enable_masking(*sig_set_t , int set) ---> disable

    2.3 char **AllocArgv (const char **argv)
        2.3.1. dynamic alloction for **argv
        2.3.2 dynamic allocaton for each argument
        2.3.2 copy the orignal argv[i] to argv dynamic alloc
        2.3.3 update the struct filed argv to dynamic allocation Argv; 
        2.3.4 return ARGV

    2.4 int WatchDog Function( interval , max_misses ,  wd_status )

        2.4.1 create a scheduler
        2.4.2 check if WD_function run in the first time (getenv(WD_PID) == NULL)
                2.4.2.1 thread_created_flag = 0
                2.4.2.2 g_other_is_ready = 0
                2.4.2.3 g_couner = max_checks +1 
                2.4.2.4 wd_status = 0
    

    2.5 scheudlerAdd(scheduler, interval, task , struct1 )

        int Task(void *param)
        {
        2.5.1 if _gshould_run




        }

    2.5 scheudlerRun(scheduler)   



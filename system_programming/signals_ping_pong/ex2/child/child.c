#define _POSIX_C_SOURCE  199309L
#include <stdio.h> /*printf , fflush*/
#include <signal.h>
#include <unistd.h> /*get pid*/
#include <sys/types.h> /*getppid*/
/*#include <stdlib.h>*/
/*#include <sys/signalfd.h>*/
/*#include <siginfo.h>*/


static int volatile g_sig_arrived = 0;



void signal_handler_child(int signum, siginfo_t *sinfo, void *param)
{
    (void)signum;
    (void)sinfo;
    (void)param;
    
    g_sig_arrived = 1;

}


int main()
{
    
    pid_t pid_parent = getppid();

    struct sigaction sa;

    sa.sa_sigaction =  signal_handler_child;
    sa.sa_flags = SA_SIGINFO;

    sigemptyset(&sa.sa_mask);

     

    sigaction(SIGUSR1, &sa, NULL);

    while (1)
    {
        
        while (g_sig_arrived == 0)
        {
            sleep(100);
        }
        
        g_sig_arrived = 0;
        printf("child - process ID : %d\n",  getpid());
        fflush(stdout);

        sleep(1);
        kill(pid_parent, SIGUSR2);
    }

    return 0;
}


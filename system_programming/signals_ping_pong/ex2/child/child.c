#define _POSIX_C_SOURCE  199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/types.h> 

/*#include <siginfo.h>*/

static int sig_arrived = 0;



void signal_handler_child(int signum, siginfo_t *sinfo, void *param)
{
    sig_arrived = 1;
    printf("child - process ID : %d\n",  getpid());

}


int main()
{
    
    pid_t pid_parent = getppid();

    struct sigaction sa;

    sa.sa_sigaction =  signal_handler_child;
    sa.sa_flags = SA_SIGINFO;
     

    sigaction(SIGUSR1, &sa, NULL);

    while (1)
    {
        
        while (sig_arrived == 0)
        {
            sleep(100);
        }

        sig_arrived = 0;
        sleep(1);
        kill(pid_parent, SIGUSR2);
        

    }

    return 0;
}


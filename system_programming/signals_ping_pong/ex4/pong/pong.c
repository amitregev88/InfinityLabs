#define _POSIX_C_SOURCE  199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/types.h> 

/*#include <siginfo.h>*/

static int sig_arrived = 0;



void signal_handler_pong(int signum, siginfo_t *sinfo, void *param)
{
    sig_arrived = 1;
    printf("pong - process ID : %d\n",  getpid());

    /*kill(getppid(),SIGUSR1); */
}


int main(int argc, char **argv)
{
    struct sigaction sa;
    pid_t ping_pid = atoi(argv[1]);

    sa.sa_sigaction =  signal_handler_pong;
    sa.sa_flags = SA_SIGINFO;
     

    sigaction(SIGUSR1, &sa, NULL);

    while (1)
    {
        
        kill(ping_pid, SIGUSR2);
        
        while (sig_arrived == 0)
        {
            sleep(100);
        }

        sig_arrived = 0;
    }

    return 0;
}


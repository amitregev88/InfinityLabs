#define _POSIX_C_SOURCE  199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/signalfd.h>


/*#include <siginfo.h>*/

static int sig_arrived = 0;
pid_t ping_pid = getpid();

void signal_handler_ping(int signum, siginfo_t *sinfo, void *param)
{

    sinfo->si_pid = ping_pid;

    printf("Pong\n");
    sig_arrived = 1;
    
    
    /*kill(getppid(),SIGUSR1); */
}


int main(int argc, char** argv)
{
    struct sigaction sa;
    sa.sa_sigaction =  signal_handler_ping;
     

    sigaction(SIGUSR1, &sa, NULL);

    while (1)
    {
        while (sig_arrived == 0)
        {
            sleep(10);
        }

        sig_arrived = 0;

        kill(atoi(argv[1]), SIGUSR2);
    }

    return 0;
}


#define _POSIX_C_SOURCE  199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/types.h> 

/*#include <siginfo.h>*/

static int g_sig_arrived = 0;
pid_t pong_pid;


void signal_handler_ping(int signum, siginfo_t *sinfo, void *param)
{
    
    (void)signum;
    (void)param;
    g_sig_arrived = 1;
    pong_pid = sinfo->si_pid;

    
}


int main()
{
    struct sigaction sa;

    sa.sa_sigaction =  signal_handler_ping;
    sa.sa_flags = SA_SIGINFO;

    sigemptyset(&sa.sa_mask);
     

    sigaction(SIGUSR2, &sa, NULL);

    while (1)
    {
        while (g_sig_arrived == 0)
        {
            sleep(100);
        }

        g_sig_arrived = 0;
        printf("ping - process ID : %d\n", getpid());
        fflush(stdout);
        sleep(1);
        kill(pong_pid, SIGUSR1);
    }

    return 0;
}


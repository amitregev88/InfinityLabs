#define _POSIX_C_SOURCE  199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>

/*#include <siginfo.h>*/

static int sig_arrived = 0;

void signal_handler1(int signum, siginfo_t *, void *)
{
    sig_arrived = 1;
    /*kill(getppid(),SIGUSR1); */
}


int main()
{
    struct sigaction sa;
    sa.sa_sigaction =  signal_handler1;
     

    sigaction(SIGUSR1, &sa, NULL);

    while (1)
    {
        while (sig_arrived == 0)
        {
            puts("Pong\n");
            sleep(100);
        }

        sig_arrived = 0;

        kill(sa.sa, SIGUSR2);
    }

    return 0;
}


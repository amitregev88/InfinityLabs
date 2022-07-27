#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/signalfd.h>
#include <siginfo.h> 

static int sig_arrived = 0;

void signal_handler1(int sig)
{
    sig_arrived = 1;
    /*kill(getppid(),SIGUSR1); */
}




int main()
{
    struct sigaction sa;

    sigaction(SIGUSR1, &sa, NULL);

    while (1)
    {
        while (sig_arrived == 0)
        {
            puts("Pong\n");
            sleep(100);
        }

        sig_arrived = 0;

        kill(sa->pid, SIGUSR2);
    }

    return 0;
}


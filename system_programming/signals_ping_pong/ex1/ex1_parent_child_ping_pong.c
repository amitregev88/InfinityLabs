#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/types.h>  

static int sig_arrived = 0;


void signal_handler_child(int sig_num, siginfo_t *infom, void *param)
{
    printf("ping\n");
    sig_arrived = 1;
}

void signal_handler_parent(int sig_num, siginfo_t *infom, void *param)
{
    printf("pong\n");
    sig_arrived = 1;
}


int main()
{
    pid_t pid = 0;

    struct sigaction parent_handler;
    struct sigaction child_handler;

    parent_handler.sa_sigaction = signal_handler_parent;
    child_handler.sa_sigaction = signal_handler_child;


    sigaction(SIGUSR1, &parent_handler, NULL);
    sigaction(SIGUSR2, &child_handler, NULL);


    pid = fork();
    if (pid == -1)
    {
        perror("error fork\n");
        return 1;
    }

    while (1)
    {
        
        if (pid == 0)
        {
            while(sig_arrived == 0)
            {
                sleep(10);
            }
            
            sig_arrived = 0;
            kill(getppid(), SIGUSR1);
        }

        else
        {      
            kill(pid, SIGUSR2);
            while(sig_arrived == 0)
            {
                sleep(10);
            }
            sig_arrived= 0;

        }
    }

    return 0;
}


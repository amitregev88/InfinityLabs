#define _POSIX_C_SOURCE 199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/types.h>  
#include <string.h>

static int sig_arrived = 0;


void handler_func(int sig_num, siginfo_t *infom, void *param)
{  
    (void) sig_num; 
    (void) infom;
    (void) param;
    sig_arrived = 1;
}


int main()
{
    pid_t pid = 0;

    struct sigaction handler;
    handler.sa_sigaction = handler_func;
    handler.sa_flags=0;
  
    sigemptyset(&handler.sa_mask);

    
    if (sigaction(SIGUSR1, &handler, NULL)<0)
    {
        printf("error sigaction\n");

    }

    if (sigaction(SIGUSR2, &handler, NULL)<0)
    {
        printf("error sigaction\n");

    }
    
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

            if(sig_arrived)
            {
                printf("ping\n");
                fflush(stdout);
                sig_arrived = 0;
            }

            sleep(1);
            
            kill(getppid(), SIGUSR1);

        }

        else
        {      
            kill(pid, SIGUSR2);
            while(sig_arrived == 0)
            {
                sleep(10);
            }

            if(sig_arrived)
            {
                printf("pong\n");
                fflush(stdout);
                sig_arrived = 0;
            }
            
            sleep(1);
            

        }
    }

    return 0;
}


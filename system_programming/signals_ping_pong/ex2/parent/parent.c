#define _POSIX_C_SOURCE  199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/types.h> 

/*#include <siginfo.h>*/

static int sig_arrived = 0;
pid_t parent_pid;
pid_t child_pid;


void signal_handler_parent(int signum, siginfo_t *sinfo, void *param)
{
    sig_arrived = 1;
    printf("parent - process ID : %d\n", getpid());

}


int main()
{
    struct sigaction sa;

    char *args[3] = {"../child/child.Debug.out", "&",NULL};
    sa.sa_sigaction =  signal_handler_parent;
    sa.sa_flags = 0; /*not necessary*/
     

    sigaction(SIGUSR2, &sa, NULL);

    child_pid = fork();

    if (child_pid == -1)
    {
        perror("error fork\n");
        return 1;
    }

        
    if(child_pid ==0)
    {
        
        execvp(args[0],args);
    }

            
    sleep (1); /*waiting for child process will be create*/

    while (1)
    {
        
        sig_arrived = 0;
        sleep(1);
        kill(child_pid, SIGUSR1);
        
        while (sig_arrived == 0)
        {
            sleep(100);
        }

    }

    return 0;
}


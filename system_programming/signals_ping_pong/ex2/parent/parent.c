#define _POSIX_C_SOURCE  199309L
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/signalfd.h>
#include <sys/types.h> 

/*#include <siginfo.h>*/

static int volatile g_sig_arrived = 0;
pid_t parent_pid;
pid_t child_pid;


void signal_handler_parent(int signum, siginfo_t *sinfo, void *param)
{
    (void)param;
    (void)sinfo;
    (void)signum;

    g_sig_arrived =1;

}


int main(void)
{
    struct sigaction sa;

    char *args[3] = {"../child/child.Debug.out", "&",NULL};
    sa.sa_sigaction =  signal_handler_parent;
    sa.sa_flags = 0;

    sigemptyset(&sa.sa_mask);
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
        
        g_sig_arrived = 0;
        sleep(1);
        kill(child_pid, SIGUSR1);
        
        while (g_sig_arrived == 0)
        {
            sleep(100);
        }
        
        printf("parent - process ID : %d\n", getpid());
        fflush(stdout);

    }

    return 0;
}


#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>




int main() 
{

    pid_t pid = fork();        
    if (pid == -1) 
    {
        perror("error fork\n");
        return 1;
    }

    while(1)
    {

        if (pid == 0) 
        {
            printf("Pong\n");
            sleep(1);
            kill(SIGUSR1); 
        }

        else 
        {
            printf("Ping "); 
            /*waitpid(pid, NULL, 0);*/
            sleep(1);
            kill(SIGUSR2);      
        }

    }

    return 0;
    
}


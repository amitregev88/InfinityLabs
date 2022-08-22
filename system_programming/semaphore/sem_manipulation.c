
#include <stdio.h> /*stdin, getline*/
#include <string.h> /* strerror*/
#include <stdlib.h> /*free*/
#include <errno.h> 
#include <semaphore.h>

sem_t semaphore;

void ExitProgIfFail(int status);
int Sem_Manipulation();


int main(void)
{

    Sem_Manipulation();
    
    return 0;        
}

 
void ExitProgIfFail(int status)
{
    strerror(status);
    exit(status);
}

int Sem_Manipulation()
{
    char **sem_act = NULL;
    char *command_line = NULL;
    int val = 0;
    size_t buffer_size = 0;

    if(0 != sem_init(&semaphore,0,0))
    {
        perror("sem_init failed\n");
        ExitProgIfFail(errno);
    }

    while(1)
    {
        printf("enter command: D - decrease, I - increase, V - getValue, X - Exit\n");

        if (getline(&command_line, &buffer_size, stdin) == -1)
        {
			if (!feof(stdin))
   			{				
                puts("getline function error\n");
                free(command_line);
      			ExitProgIfFail(errno);
			}
        }

        switch (*command_line)
        {
        case 'D':

            if(sem_getvalue(&semaphore,&val))
            {
                ExitProgIfFail(errno);
            }

            if (0 == val)
            {
                puts("worng command\n");
                break;
            }
            
            if (0 != sem_wait(&semaphore))
            {
                ExitProgIfFail(errno);
            }
            break;

        case 'I':

            if (0 != sem_post(&semaphore))
            {
                ExitProgIfFail(errno);
            }
            break;

        case 'V':

            if(sem_getvalue(&semaphore,&val))
            {
                ExitProgIfFail(errno);
            }
            /*printf("%d\n", val);*/
            break;

        case 'X':
            /*sem_close(&semaphore);*/
            exit(0);
            break;

        
        default:
            break;
        }

        sem_getvalue(&semaphore,&val);
        printf("%d\n", val);
        
    }
}


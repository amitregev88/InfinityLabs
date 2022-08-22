
#include <stdio.h> /*stdin, getline*/
#include <string.h> /* strerror*/
#include <stdlib.h> /*free*/
#include <errno.h> 
#include <sys/msg.h>
#include <sys/sem.h> /*semget*/
#include <sys/shm.h>
#include <sys/ipc.h> /*ftok*/
#include <sys/types.h>



int semid = 0;


void ExitProgIfFail(int status);
int Sem_Manipulation();


int main(int argc, char** argv)
{
    key_t key;
    int semid = 0;
    union semnum
    
    
    if(argc < 2)
    {
       puts("Error - enter a path\n");
       return 1;
     
    }

    key = ftok(argv[1], 'E');  
    if(-1 == key)
    {
        perror("ftok");
        exit(1); 
    }

    semid = semget(key,1,0666 | IPC_CREAT);
    if(-1 ==semid)
    {
        perror("semget");
        exit(1); 
    }

    if (semctl(semid, 0, SETVAL, arg) == -1) 
    {
        perror("semctl");
        exit(1); 
    }

    }

       
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


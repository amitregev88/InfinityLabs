
#include <stdio.h> /*stdin, getline*/
#include <string.h> /* strerror*/
#include <stdlib.h> /*free*/
#include <errno.h> 
#include <sys/msg.h>
#include <sys/sem.h> /*semget*/
#include <sys/shm.h>
#include <sys/ipc.h> /*ftok*/

#define MAX_ARGS 10
#define DELIMS " \t\r\n\a"

union semun 
{
    int val;    /* Value for SETVAL */

    struct semid_ds *buf;    /* Buffer for IPC_STAT, IPC_SET */
    unsigned short  *array;  /* Array for GETALL, SETALL */
    struct seminfo  *__buf;  /* Buffer for IPC_INFO (Linux-specific) */     
};



static void ExitProgIfFail(int status);
static int Sem_Manipulation(int semid, struct sembuf *sops);


int main(int argc, char** argv)
{
    key_t key;
    int semid = 0;
    union semun sema ;
    struct sembuf sops = {0,0,0};
    char * fname = NULL;
    FILE *fp = NULL;
        
    /*TODO chacker fail functions*/
    if(argc < 2)
    {
        fname = "filename";
    }
    else
    {
        fname = argv[1];
    }

    fp = fopen(fname, "w+");


   /* create semaphore function */
    key = ftok(fname, 'E');  
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

    sema.val = 1;

    if (semctl(semid, 0, SETVAL, sema) == -1) 
    {
        perror("semctl");
        exit(1); 
    }

     
    Sem_Manipulation(semid,&sops);

    return 0;        
}
 
static void ExitProgIfFail(int status)
{
    
    /*semctl(semid, 0, IPC_RMID);*/
    strerror(status);
    exit(status);
}

static int Sem_Manipulation(int semid, struct sembuf *sops)
{
        
    char *command_line = NULL;
    int val = 0;
    size_t buffer_size = 0;
    char *arguments = 0;
    char **args = NULL;
    int i;
    int num = 1; 

    args = malloc (sizeof(char *) * MAX_ARGS);
    if(!args)
    {
        return 1;
    }

    sops->sem_num = 0; /*sema indx*/
    sops->sem_op = 0; /**/
    sops->sem_flg = 0; 


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

        arguments = strtok(command_line,DELIMS);

        for(i = 0;arguments != NULL;++i)
        {
            args[i] = arguments;
            arguments = strtok(NULL,DELIMS);
        }

        args[i] = NULL;   

        if (args[1])
        {
            num = atoi(args[1]);
            
        }

        if (args[2])
        {
            sops->sem_flg = SEM_UNDO;
        }
    

        switch (*command_line)
        {
        case 'D':
    
            sops->sem_op -= num;
            break;

        case 'I':

            sops->sem_op += num;
            break;

        case 'V':

            printf("Semaphore value is %d\n", sops->sem_op);
            
            break;

        case 'X':
            
            
            break;

        
        default:
            break;
        }

        
    }
}


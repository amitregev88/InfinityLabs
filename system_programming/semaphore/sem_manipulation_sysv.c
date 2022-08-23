
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

static void ExitProgIfFail(void *status);
static void Sem_Manipulation(int semid, struct sembuf *sops);
static void SemaphoreCreate(char *file_name);


int main(int argc, char** argv)
{
    char * fname = NULL;
        
    if(argc < 2)
    {
        fname = "filename";
    }
    else
    {
        fname = argv[1];
    }

    SemaphoreCreate(fname);
    
    return 0;
}

static void SemaphoreCreate(char *file_name)
{    
    key_t key;
    int semid = 0;
    union semun sema ;
    struct sembuf sops = {0,0,0};
    FILE *fp = NULL;
    int status = 0;

    fp = fopen(file_name, "w+");
    
    ExitProgIfFail(fp);

    key = ftok(file_name, 'E');

    ExitProgIfFail((void *)key);  

    semid = semget(key,1,0666 | IPC_CREAT);

    ExitProgIfFail((void *)semid);  

    sema.val = 1;

    status = semctl(semid, 0, SETVAL, sema);
    ExitProgIfFail((void *)status); 
    
    Sem_Manipulation(semid,&sops);
       
}
 
static void ExitProgIfFail(void *status)
{
    if(NULL == status)
    {
        puts("error open file\n");
        /*semctl(semid, 0, IPC_RMID);*/
        exit(1);
        return;
    }

    if(0 != (int)status)
    {
        strerror((int)status);
        /*semctl(semid, 0, IPC_RMID);*/
        exit((int)status);
    }

    return;
}

static void Sem_Manipulation(int semid, struct sembuf *sops)
{
        
    char *command_line = NULL;
    size_t buffer_size = 0;
    char *arguments = 0;
    char **args = NULL;
    int i;
    int num = 1;
    int status = 0;
    int is_running = 1;

    args = malloc (sizeof(char *) * MAX_ARGS);
    if(!args)
    {
        puts("malloc failed\n");
        return;
    }

    sops->sem_num = 0; /*sema indx*/
    sops->sem_op = 0; /**/
    sops->sem_flg = 0; 

    while(is_running)
    {
        puts("enter command: D - decrease, I - increase, V - getValue, X - Exit\n");
        fflush(stdout);

        if (getline(&command_line, &buffer_size, stdin) == -1)
        {
			status = feof(stdin);
   			
            if (status == -1)
            {
                free(command_line);
      		    ExitProgIfFail((void *)status);
            }
        }

        arguments = strtok(command_line, DELIMS);

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

            is_running = 0;     
            break;

        default:
        break;

        }
    }

    semctl(semid, 0, IPC_RMID);

}


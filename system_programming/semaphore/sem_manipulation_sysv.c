/****************************************************************************
*	Project:	Semaphore             										*
*	File:		sem_manipulation.c											*
*	Date: 		22/08/2022													*
*	Name: 		Amit Regev													*
*	Reviewer:	Vered Szer											        *
*	Version: 	1.00														*
****************************************************************************/
#define _GNU_SOURCE /*getline*/

#include <stdio.h> /*stdin, getline*/
#include <string.h> /* strerror, getline*/
#include <stdlib.h> /*free*/



#include <errno.h> 

#include <sys/sem.h> /*semget*/
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
static void SemManipulation(int semid);
static int SemaphoreCreate(char *file_name);
static void ChangeSemVal(struct sembuf *sops, int sem_id, int val);


int main(int argc, char** argv)
{
    char * fname = NULL;
    int sems_id = 0;
        
    if(argc < 2)
    {
        fname = "filename";
    }
    else
    {
        fname = argv[1];
    }

    sems_id = SemaphoreCreate(fname);
    SemManipulation(sems_id);
    
    return 0;
}

static int SemaphoreCreate(char *file_name)
{    
    key_t key;
    int semid = 0;
    FILE *fp = NULL;
    int status = 0;
    union semun sema ;

    fp = fopen(file_name, "w+");
    
    ExitProgIfFail(fp == NULL);

    fclose(fp);

    key = ftok(file_name, 'E');

    ExitProgIfFail(key == -1);  

    semid = semget(key,1,0666 | IPC_CREAT);

    ExitProgIfFail(semid == -1);  

    sema.val = 1;

    status = semctl(semid, 0, SETVAL, sema);
    ExitProgIfFail(status == -1); 


    return semid; 
}
 

static void SemManipulation(int semid)
{
    char *command_line = NULL;
    size_t buffer_size = 0;
    char *arguments = 0;
    char **args = NULL;
    int i = 0;
    int sem_val = 1;
    int status = 0;
    int is_running = 1;
    struct sembuf sops = {0,0,0};

    args = (char **)malloc (sizeof(char *) * MAX_ARGS);
    ExitProgIfFail(args == NULL); 

    sops.sem_num = 0; /*sema indx*/
    sops.sem_op = 0; /**/
    sops.sem_flg = 0; 

    while(is_running)
    {
        puts("enter command: D - decrease, I - increase, V - getValue, X - Exit\n");
        fflush(stdout);

        status  = getline(&command_line, &buffer_size, stdin);       
            
      	ExitProgIfFail(status == -1);
        
        arguments = strtok(command_line, DELIMS);

        for(i = 0;arguments != NULL;++i)
        {
            args[i] = arguments;
            arguments = strtok(NULL,DELIMS);
        }

        args[i] = NULL;   

        if (args[1])
        {
            sem_val = atoi(args[1]);      
        }

        if (args[2] && !strcmp(args[2], "UNDO"))
        {
            sops.sem_flg = SEM_UNDO;
        }

        switch (*command_line)
        {
        case 'D':
    
            ChangeSemVal(&sops, semid, -sem_val);
            break;

        case 'I':

            ChangeSemVal(&sops, semid, sem_val);
            break;

        case 'V':

            printf("Semaphore value is %d\n", semctl(semid,0,GETVAL));
            fflush(stdout);
            
            break;

        case 'X':

            is_running = 0;     
            break;

        default:
        break;

        }
    }

    
    semctl(semid, 0, IPC_RMID);
    free(command_line);

}

static void ExitProgIfFail(int status)
{
    if(status)
    {
        strerror(errno);
        /*semctl(semid, 0, IPC_RMID);*/
        exit(status);
    }

    return;
}

static void ChangeSemVal(struct sembuf *sops, int sem_id, int val)
{
    sops->sem_op = val;
    semop(sem_id,sops,1);
}

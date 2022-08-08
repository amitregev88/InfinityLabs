
#include <semaphore.h>
#include <stdio.h> /*stdin, getline*/
#include <stdlib.h> /*free*/


sem_t semaphore;



int main()
{
    char **sem_act = NULL, *command_line = NULL;
    int val = 0;
    size_t buffer_size = 0;

    if(sem_init(&semaphore,0,0) != 0)
    {
        perror("sem_init failed\n");
    }

    while (1)
    {
        printf("enter command: D - decrease, I - increase, V - getValue, X - Exit\n");
        if (getline(&command_line, &buffer_size, stdin) == -1)
        {
			if (!feof(stdin))
   			{				
                puts("getline function error\n");
                free(command_line);
      			return 1;
			}
        }

        /*TODO sem action*/

        switch (*command_line)
        {
        case 'D':
            sem_wait(&semaphore);
            break;

        case 'I':

            sem_post(&semaphore);
            break;

        case 'V':

            sem_getvalue(&semaphore,&val);
            /*printf("%d\n", val);*/
            break;

        case 'X':
            /*sem_close(&semaphore);*/
            return 0;
            break;

        
        default:
            break;
        }

        sem_getvalue(&semaphore,&val);
        printf("%d\n", val);        
    }

        return 0;


        
}
    





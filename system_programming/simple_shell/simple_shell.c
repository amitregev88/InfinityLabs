/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 21/7/22 
* OL124 simple shell project
***************************************************************/
#define  _GNU_SOURCE

#include <stdio.h>/*printf, getline*/
#include <string.h>/*strcmp*/
#include <unistd.h> /* fork, execvp */
#include <stdlib.h> /* free*/
#include <sys/wait.h> /* wait */

#define KEEP_RUNNING 1
#define MAX_ARGS 10
#define DELIMS " \t\r\n\a"

int main(void)
{
    char *command_line = NULL;
    size_t buffer_size = 0; 
    char **args = NULL;
    char *arguments = 0;
    pid_t pid;
    int i = 0;
    int status = 0;

    while(KEEP_RUNNING)
    {
        printf("$ ");
        if (getline(&command_line, &buffer_size, stdin) == -1)
        {
			if (!feof(stdin))
   			{				
                free(command_line);
      			return 1;
			}
        }

        args = malloc (sizeof(char *) * MAX_ARGS);
        if(!args)
        {
            free(command_line);
            return 1;
        }

        arguments = strtok(command_line,DELIMS);
        while(arguments != NULL)
        {
            args[i] = arguments;
            ++i;
            arguments = strtok(NULL,DELIMS);

        }
        args[i] = NULL;   
        
        if(!strcmp(args[0], "exit"))
        {
            free(args);
            free(command_line);
            return 0;
        }

        pid = fork();
        if (pid == -1) /* failed to fork */
		{
            free(args);
      		free(command_line);
            return 1;
   		}
           
        else if(pid == 0)   /*fork child*/
        {             
            if (execvp(args[0],args) == -1)
			{
                free(args);
				free(command_line);
      			return 1;
			}		    
        }

        else if (pid > 0) /*fork parent*/
        {
            if(-1 == wait(&status))
            {
                free(command_line);
                free(args);

                return 1;

            }             
        }                      
    }

    return 0;
}
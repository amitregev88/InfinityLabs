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
#include <stdlib.h> /*malloc, free*/
#include <sys/wait.h> /* wait */

/*
1. while (1)

2. getline -> stdin
3. if (strcmp - exit) -> exit

4. args = strtok(getline)
5 while args != null
    arr[i] =args
    args = strtok(NULL)
    i++

6. fork
6.1 child process -> exevp()
6.2 parent -> wait 
*/

#define KEEP_RUNNING 1
#define MAX_ARGS 10
#define DELIMS " \t\r\n\a"


int main(int argc, char **argv)
{

    char *command_line = NULL;
    size_t buffer_size = 0; 
    char **args = NULL;
    char *arguments = 0;
    pid_t pid;
    int i = 0;
    FILE* input_stream = stdin;
    int file_input_flag = 0;


    if (argc == 2)
    {
        input_stream = fopen(argv[1], "r");
        if(!input_stream)
        {
            printf("fopen failed\n");
            return 1;
        }
        
        else
        {
            file_input_flag = 1;
        }   

    }



    args = malloc (sizeof(char *) * MAX_ARGS);
    if(!args)
    {
        printf("malloc failed\n");
        return 1;
    }

    while(KEEP_RUNNING)
    {
        printf("$ ");
        if (getline(&command_line, &buffer_size, input_stream) == -1)
        {
			if (!feof(input_stream))
   			{				
                free(args);
      			return 1;
			}
        }

        arguments = strtok(command_line,DELIMS);
        
        for(i= 0;arguments != NULL;++i)
        {
            args[i] = arguments;
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
            perror("fork failed");
            return 1;
   		}
           
        if(pid == 0)   /*child process*/
        {             
            if (execvp(args[0],args) == -1)
			{
                free(args);
				free(command_line);
      			return 1;
			}		    
        }
        /*parent process*/

        waitpid(-1, NULL, 0);

        if (file_input_flag)
        {
            fclose(input_stream);
        }
   
    }

    return 0;
}
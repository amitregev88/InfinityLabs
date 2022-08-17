/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 21/7/22 
* OL124 simple shell project
***************************************************************/

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

static void ExitShell(char *buffer, char **args, int status);
static int IsBuildinCommand(char *command);
static void RunShell(FILE *command_file);
static void ForkAndExec(char *cmd, char *args[]);


int main(int argc, char **argv)
{

    FILE* input_stream = stdin;
    int file_input_flag =0;

    if (argc > 4)
    {
        input_stream = fopen(argv[1], "r");
        if(!input_stream)
        {
            printf("fopen failed\n");
            return 1;
        }

        file_input_flag =1;

    }

    RunShell(input_stream);


    if (file_input_flag)
    {
        fclose(input_stream);
    }

    return 0;

}

    
static void RunShell(FILE *command_file)
{
    char *command_line = NULL;
    char *arguments = 0;
    size_t buffer_size = 0; 
    char **args = NULL;
    int i;


    args = malloc (sizeof(char *) * MAX_ARGS);
    if(!args)
    {
        printf("malloc failed\n");
        return;
    }

    while(KEEP_RUNNING)
    {
        printf("$ ");
        if (getline(&command_line, &buffer_size, command_file) == -1)
        {
			if (!feof(command_file))
   			{				
                
                puts("error to read line\n");
                free(args);
      			exit(1);
			}
        }

        if(IsBuildinCommand(command_line))
        {

            ExitShell(command_line,args,0);            

        }


        arguments = strtok(command_line,DELIMS);
        
        for(i= 0;arguments != NULL;++i)
        {
            args[i] = arguments;
            arguments = strtok(NULL,DELIMS);
        }

        args[i] = NULL;   

        ForkAndExec(command_line,args);

    }
    ExitShell(command_line,args,0);
}


static void ForkAndExec(char *cmd, char *args[])
{
    pid_t child_pid = 0;
        
    child_pid =fork();

    if (child_pid == -1) /* failed to fork */
	{
        perror("fork failed");
        return;
   	}
           
    if(child_pid == 0)   /*child process*/
    {             
        if (execvp(args[0],args) == -1)
		{
      			perror("execvp failed");
                ExitShell(cmd,args,1);
		}		    
    }
    /*parent process*/

    waitpid(-1, NULL, 0);

   
}


static int IsBuildinCommand(char *command)
{

    if(strcmp(command, "exit\n") == 0)
    {

        return 1;
    }

    return 0;


}

static void ExitShell(char *buffer, char **args, int status)
{

	free(buffer);
	free(args);

	exit(status);
}

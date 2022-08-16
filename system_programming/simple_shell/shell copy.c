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
#define BUFFER_SIZE 100
#define DELIMS " \t\r\n\a"


static int Readline(char *command_list, char buffer[BUFFER_SIZE])
{
    char *command_line = NULL;
    char *arguments = 0;
    int i;
    char buffer[BUFFER_SIZE];
    char args[MAX_ARGS];

    if (fgets(buffer,BUFFER_SIZE,stdin))
    {
		if (!feof(buffer))
   		{	
      		return -1;
		}
    }

    arguments = strtok(command_line,DELIMS);
        
    for(i= 0;arguments != NULL;++i)
    {
        args[i] = arguments;
        arguments = strtok(NULL,DELIMS);
    }

    if (IsBuildinCommand(command_line))
    {
        return 2;
    }
    


    return 0;

}


int IsBuildinCommand(char *command)
{

    if(!strcmp(command, "exit"))
    {

        return 1;
    }

    return 0;


}


void RunShell(char *command_list)
{
    char buff[50];
    
    while(KEEP_RUNNING)
    {
        printf("$ ");


        
        switch (Readline(command_list,buff))
        {
        case -1:
            puts("en")
            break;
        
        case 0:

            break;
        

    args = malloc (sizeof(char *) * MAX_ARGS);
    if(!args)
    {
        printf("malloc failed\n");
        return 1;
    }
            break;
        }
        if () 
        {
            printf("readline error\n");
        }

        else 
    }


        




}


static int RunCommand()
{
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

}

int main(int argc, char **argv)
{

    char **args = NULL;
    pid_t pid;
    int i = 0;
    int file_input_flag = 0;
    FILE* input_stream = stdin;


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

    RunShell()




    if (file_input_flag)
    {
        fclose(input_stream);
    }
   


    return 0;
}
#include<stdio.h> /*printf*/
#include<unistd.h> /*sleep*/
#include <pthread.h> /*pid_t*/

#include "utility.h"

int main() 
{
   int pipefd_ping[2];
   int pipefd_pong[2];
   int ret = 0;
   pid_t is_parent;
   char buffer[2][5] = {"Ping", "Pong"};
   char read_message[20];
   ret = pipe(pipefd_ping);
   ReturnErnoIfFail(ret == 0, "pipe() failed",-1);

   ret = pipe(pipefd_pong);
   ReturnErnoIfFail(ret == 0, "pipe() failed",-1);

   
   is_parent = fork();
   ReturnErnoIfFail(is_parent != -1, "fork failed", -1);

    if (is_parent) 
    {
        while(1)
        {
            printf("Writing to pipe - Message 1 is %s\n", buffer[0]);
            write(pipefd_ping[1], buffer[0], sizeof(buffer[0]));
            
            sleep(1);
            read(pipefd_pong[0],read_message , sizeof(read_message));
            printf("Reading from pipe - Message 2 is %s\n\n", read_message);
        }

    }

    else /*in case is child process */
    {

        while(1)
        {
            read(pipefd_ping[0], read_message, sizeof(read_message));
            printf("Reading from pipe - Message 1 is %s\n", read_message);
            sleep(1);
            printf("Writing to pipe - Message 2 is %s\n", buffer[1]);
            write(pipefd_pong[1], buffer[1], sizeof(buffer[0]));
        }

    }

   return 0;
}
#include <fcntl.h>   /*open*/
#include <sys/types.h>
#include <string.h> /*strlen*/
#include <unistd.h>
#include <stdio.h> /*printf*/


#include "../include/utility.h"

int main()
{
    const char *fifo_ping = "/tmp/FIFO_PING";
    const char *fifo_pong = "/tmp/FIFO_PONG";
    int fd_read;
    int fd_write;
    char msg1[6] = "pong\n";
    char buff_read[6];

    fd_write = open(fifo_pong, O_WRONLY);
    ReturnErnoIfFail(fd_write > 0,"open() failed\n", -1);


    fd_read = open(fifo_ping, O_RDONLY);
    ReturnErnoIfFail(fd_read > 0, "open() failed\n", -1);
 
    while (1)
    {
        read(fd_read,buff_read, 5);
        sleep(1);      
        printf("%s",buff_read);
        write(fd_write, msg1, strlen(msg1));
    }
    

    close(fd_read);
    close(fd_write);


    return 0;
}

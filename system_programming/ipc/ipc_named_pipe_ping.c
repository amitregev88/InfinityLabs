#include <fcntl.h>   /*open*/
#include <sys/stat.h>/*mkfifo*/
#include <sys/types.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>


#include "../include/utility.h"

int main()
{
    const char *fifo_ping = "/tmp/FIFO_PING";
    const char *fifo_pong = "/tmp/FIFO_PONG";
    int fd_read;
    int fd_write;
    char msg1[6] = "ping\n";
    char buff_read[6];


    mkfifo(fifo_ping, S_IRUSR | S_IWUSR);

    mkfifo(fifo_pong, S_IRUSR | S_IWUSR);

    fd_read = open(fifo_pong, O_RDONLY);
    ReturnErnoIfFail(fd_read > 0, "open() failed\n", -1);

    fd_write = open(fifo_ping, O_WRONLY);
    ReturnErnoIfFail(fd_write > 0,"open() failed\n", -1);


    while (1)
    {
        write(fd_write, msg1, strlen(msg1));

        read(fd_read, buff_read, 6);

        sleep(1);      

        printf("%s\n",buff_read);
        
    }
    

    close(fd_read);
    close(fd_write);

    unlink(fifo_ping);
    unlink(fifo_pong);


    return 0;
}

#include <stdio.h> /*printf*/
#include <sys/msg.h> /*key_t*/
#include <sys/mman.h> /*shm_open*/
#include <fcntl.h>           /* For O_* constants */


#include "../include/utility.h"

int main(void)
{
    
    int fd;
    char *data;
    
    fd = shm_open("/tmp/blabla",O_RDONLY ,0666);
    ReturnErnoIfFail(fd != -1, "shm_open faied", -1);

    ftruncate(fd,sizeof(int));/*page size*/

    data =  mmap(NULL,sizeof(int),PROT_READ, MAP_SHARED, fd, 0);

    printf("receiver pid : %d mapped  address: %p\n",getpid(), data);

    munmap(data,sizeof(int));

    close(fd);

    shm_unlink("/tmp/blabla");
    return 0;

}
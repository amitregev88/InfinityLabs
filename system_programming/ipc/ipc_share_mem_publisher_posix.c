#define  _XOPEN_SOURCE  500
#define _POSIX_C_SOURCE 200809L

#include <stdio.h> /*printf*/
#include <sys/msg.h> /*key_t*/
#include <sys/mman.h> /*shm_open*/
#include <fcntl.h> /* For O_* constants */


#include "../include/utility.h"

int main(void)
{
    
    key_t key;
    int shm_id;
    int fd;
    char *data = "hi"; 
    
    fd = shm_open("/tmp/blabla",O_CREAT ,0777);
    ReturnErnoIfFail(fd != -1, "shm_open faied", -1);

    ftruncate(fd,sizeof(int));/*page size*/

    data =  mmap(NULL,sizeof(int),PROT_READ | PROT_WRITE , MAP_SHARED, fd, 0);

    printf("sender pid : %d mapped  address %p\n",getpid(), data);

    munmap(data,sizeof(int));

    close(fd);
    
    return 0;

}
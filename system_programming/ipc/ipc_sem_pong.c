#include <stdio.h> /*printf*/
/*#include <unistd.h> *//*sleep*/
#include <fcntl.h> /*O_CREAT*/
#include <semaphore.h> /*sem_open, sem_wait, sem_post*/

#include "utility.h"

int main(void)
{
    sem_t *sem_ping = sem_open("sem_ping", O_CREAT, 0777, 0);
    sem_t *sem_pong = sem_open("sem_pong", O_CREAT, 0777, 0);
    int ret = 0;

    while(1)
    {
        ret = sem_wait(sem_ping);
        ExitErnoIfFail(ret == 0, "sem_wait() failed", -1);
        printf("Hello from Pong process\n");
        sem_post(sem_pong);
        ExitErnoIfFail(ret == 0, "sem_post() failed", -1);
        /*sleep(1);*/
    }


    sem_close(sem_pong);
    sem_unlink(sem_pong);

    return 0;

}
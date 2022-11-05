#include <stdlib.h> /* null */
#include <stdio.h> /* printf */
#include <string.h> /* memcpy */

#include <sys/ipc.h> /* shmget */
#include <sys/shm.h> /* shmget */

#include "utility.h"

int SharedPong(void);

int main()
{

    return SharedPong();
}

int SharedPong(void)
{
    key_t key = 0;
    int shmid = 0;
    void *shm_add = NULL;
    char ping[10] = {0};
    key = ftok("/tmp/lala",12);

    shmid = shmget(key,100,IPC_CREAT);

    ExitErnoIfFail(shmid != -1,"shmget failed", -1);

    shm_add = shmat(shmid,NULL,0777);

    ExitErnoIfFail(shm_add != (void *) -1,"shmget failed", -1);
    
    memcpy(ping,shm_add,10);

    printf("%s\n",ping);

    return 0;

}


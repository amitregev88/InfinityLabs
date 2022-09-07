/*gd watchdog_app.c watchdog.c ../scheduler/scheduler.c ../scheduler/task.c ../../ds/priority_queue_heap/pqueue.c ../../ds/heap/heap.c ../../ds/dynamic_vector/dynamic_vector.c ../../ds/uid/uid.c -g -o wd_app -I  ../../ds/include/ -lpthread*/

/*gcc -g watchdog_app.c watchdog.c ./scheduler/dlist.c ./scheduler/pqueue.c ./scheduler/scheduler.c ./scheduler/sorted_list.c ./scheduler/tasker.c ./scheduler/uid.c -I ./scheduler/ -pthread -o wd_app*/




#include <stdlib.h> /*atoi*/
#include "wg_private_api.h"
#include <stdio.h>
#include <unistd.h> /*getpid*/

int main(int argc, char *argv[])
{  
   
    (void)argc;
    
    printf("WATCHDOG PROCESS ---> PID:%d\n",getpid());
    
    WatchDog(atoi(argv[1]), atoi(argv[2]), argv + 3);

    return 0;

}static int SetHandlers(void)

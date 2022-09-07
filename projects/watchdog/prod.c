/*gd prod.c watchdog.c ../scheduler/scheduler.c ../scheduler/task.c ../../ds/priority_queue_heap/pqueue.c ../../ds/heap/heap.c ../../ds/dynamic_vector/dynamic_vector.c ../../ds/uid/uid.c -g -o product -I  ../../ds/include/ -lpthread*/

/*gcc -g  watchdog.c ./scheduler/dlist.c ./scheduler/pqueue.c ./scheduler/scheduler.c ./scheduler/sorted_list.c ./scheduler/tasker.c ./scheduler/uid.c prod.c -I ./scheduler -pthread -o product*/

#include <stdio.h> /*printf*/
#include <unistd.h> /*sleep*/
#include <unistd.h> /*getpid*/
#include "wd.h"


int main(int argc, char *argv[])
{
    (void)argc;
    MMI(5, 3, argv);

    printf("PRODUCT APP IS RUNNING --> PID:%d\n",getegid());

    puts("DNR WILL CALLED in 12 sec\n");
  
    sleep(12);

    DNR();

    return 0;

}




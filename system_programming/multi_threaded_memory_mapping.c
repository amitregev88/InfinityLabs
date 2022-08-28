/****************************************************************************
*	Project:	Multi threaded memory mapping           								*												*
*	Date: 		28/08/2022													*
*	Name: 		Amit Regev													*
*	Reviewer:												                *
*	Version: 	1.00														*
****************************************************************************/

#include <stdio.h>  /*printf*/
#include <stdlib.h> /*malloc , free*/
#include <errno.h> 


#include <pthread.h>    /*pthread_create, pthread_join */

#define NUM_OF_THREADS 2

void *ThreadRoutine(void *param);
static void ExitProgIfFail(int status);

 int g_num = 10;

int main(void)
{
    pthread_t threads[NUM_OF_COMSUMERS];
    int status = 0;
    int i = 0;
    int *heap = (int *) malloc(sizeof(int) * 2);
    ExitProgIfFail(NULL != heap);


    for (i = 0; i < NUM_OF_COMSUMERS; ++i)
	{
		status = pthread_create(&threads[i],NULL, &ThreadRoutine,(void *)i);
        ExitProgIfFail(status == 0);
    }


    for (i = 0; i < NUM_OF_COMSUMERS; ++i)
	{
		status = pthread_join(threads[i],NULL);
        ExitProgIfFail(status == 0);
    }

    puts("\n\nHello from the main thread\n");

    printf("\naddress of variable on main thread's stack  --> %p \n", &status);

    printf("\naddress of variable on the heap from the main thread --> %p \n", &heap);

    printf("\naddress of global variable from the main thread  --> %p \n", &g_num);


    free(heap);


    return 0;

}

void *ThreadRoutine(void *param)
{
    int thread_stack = 1;

    int *heap = (int *)malloc(sizeof(int)* 2);
    ExitProgIfFail(NULL != heap);


    printf("\n\nHello from thread No %d\n", (int)param);

    printf("\naddress of variable on tread's stack  --> %p \n", &thread_stack);

    printf("\naddress of variable on the heap from thread routine --> %p \n", &heap);

    printf("\naddress of global variable from tread routine  --> %p \n", &g_num);

    free(heap);
      
   
    return NULL;

}


static void ExitProgIfFail(int status)
{
    if(!status)
    {
        perror(NULL);
        exit(status);
    }

    return;
}

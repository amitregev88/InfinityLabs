/****************************************************************************
*	Project:	producer consumer             								*											*
*	Date: 		24/08/2022													*
*	Name: 		Amit Regev													*
*	Reviewer:												                *
*	Version: 	1.00														*
****************************************************************************/

#include <stdio.h>  /*printf*/
#include <stdlib.h>  /*exit*/
#include <assert.h>
#include <errno.h>

#include <pthread.h>
#include <semaphore.h>
#include "dlinked_list.h"

#define NUM_OF_PRODUCERS 3
#define NUM_OF_CONSUMERS 4

#define SIZE_ARR 10 

typedef struct 
{
    dlist_ty *list;
    pthread_mutex_t mutex_list_lock;
    sem_t semaphore;
    int thread_id;
    
}sync_ty;

static int *Produce(int data);
static int SumArr(int *arr);
static void ExitProgIfFail(int status);


void *ProducerAct(void *param)
{
    
    int num_of_iterations  = 8; 
    int status = 0;
    int *data = NULL;
    static int num = 0;
    int *res = NULL;


    while(num_of_iterations)
    {
        --num_of_iterations;
        ++num;

        res = Produce(num);
        ExitProgIfFail(res != NULL);

        status = pthread_mutex_lock(&((sync_ty *)param)->mutex_list_lock);
        ExitProgIfFail(status == 0);
        
        DListPushFront(((sync_ty *)param)->list,(void *)res);
        
        
        status = pthread_mutex_unlock(&((sync_ty *)param)->mutex_list_lock);
        ExitProgIfFail(status == 0);


        status = sem_post(&((sync_ty *)param)->semaphore);
        ExitProgIfFail(status == 0);


        printf("Producer No %d --> sum of array %d \n",((sync_ty *)param)->thread_id, SumArr(res));

        
         
    }

    return NULL;
}

void *ConsumerAct(void *param)
{
    int num_of_iterations  = 2; 
    int status = 0;
    int *data = NULL;

    while(num_of_iterations)
    {
        --num_of_iterations;

        status = sem_wait(&((sync_ty *)param)->semaphore);
        ExitProgIfFail(status == 0);

        status = pthread_mutex_lock(&((sync_ty *)param)->mutex_list_lock);
        ExitProgIfFail(status == 0);

        if(!DListIsEmpty(((sync_ty *)param)->list))
        {
            data = (int *)DListPopBack(((sync_ty *)param)->list);
            ExitProgIfFail(data != NULL);
        }
        
        status = pthread_mutex_unlock(&((sync_ty *)param)->mutex_list_lock);
        ExitProgIfFail(status == 0);


        printf("Consumer No %d --> sum of array %d \n",((sync_ty *)param)->thread_id, SumArr(data));

        free(data);

    }

    return NULL;
}

int main()
{
    pthread_t producers[NUM_OF_PRODUCERS];
    pthread_t consumers[NUM_OF_CONSUMERS];
    sync_ty sync;
    int i = 0;
    int status = 0;

    status = sem_init((&sync.semaphore), 0, 0);
    ExitProgIfFail(status == 0);

    status = pthread_mutex_init(&sync.mutex_list_lock, NULL);
    ExitProgIfFail(status == 0);

    sync.list = DListCreate();
    ExitProgIfFail(sync.list != NULL);

    for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		sync.thread_id = i;
        
        status = pthread_create(&producers[i],NULL, &ProducerAct, &sync);
        ExitProgIfFail(status == 0);
    }

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
        sync.thread_id = i;
		        
        status = pthread_create(&consumers[i],NULL, &ConsumerAct, &sync);
        ExitProgIfFail(status == 0);
	}

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		status = pthread_join(producers[i],NULL);
        ExitProgIfFail(status == 0);
    }

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		status = pthread_join(consumers[i],NULL);
        ExitProgIfFail(status == 0);
    }

	status = pthread_mutex_destroy(&sync.mutex_list_lock);
    ExitProgIfFail(status == 0);

    status = sem_destroy(&sync.semaphore);
    ExitProgIfFail(status == 0);

	DListDestroy(sync.list);

	return 0;	
}

static int *Produce(int data)
{
    int i;
    int *nums = (int *) malloc (sizeof(int) * SIZE_ARR);
        
    for(i = 0; i < SIZE_ARR; ++i)
    {
        *(nums + i) = data;
    }

    return nums;

}

static int SumArr(int *arr)
{
    int sum = 0;
    int i = 0;

    assert(arr);

    for(i = 0; i < SIZE_ARR; ++i)
    {
        sum += *(arr + i);
    }

    return sum;
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


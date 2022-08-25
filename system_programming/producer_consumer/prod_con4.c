/****************************************************************************
*	Project:	producer consumer             								*											*
*	Date: 		24/08/2022													*
*	Name: 		Amit Regev													*
*	Reviewer:												                *
*	Version: 	1.00														*
****************************************************************************/
#include <stdio.h> /*printf*/
#include <stdlib.h>  /*exit*/
#include <errno.h>
#include <assert.h> 

#include <pthread.h>
#include <semaphore.h>

#include "circ_buffer.h"

#define NUM_OF_PRODUCERS 2
#define NUM_OF_CONSUMERS 4

#define NUM_OF_ELEMENTS 50
#define SIZE_ARR 10


static int *Produce(int data);
static int SumArr(int *arr);
static void ExitProgIfFail(int status);


typedef struct 
{
    circ_buffer_ty *buffer;
    pthread_mutex_t mutex_buffer_lock;
    sem_t semaphore_ready_to_read;
    sem_t semaphore_ready_to_write;
    int thread_id;
    
}sync_ty;


void *ProducerAct(void *param)
{
   
    int num_of_iterations = 2;
    static int num = 0;
    int *res = NULL;

    while(num_of_iterations)
    {  
        --num_of_iterations;

        ++num;

        res = Produce(num);
        ExitProgIfFail(res != NULL);
        
        sem_wait(&((sync_ty *)param)->semaphore_ready_to_write);

        pthread_mutex_lock(&((sync_ty *)param)->mutex_buffer_lock);

        BufferWrite(((sync_ty *)param)->buffer,&res, sizeof(size_t));

        pthread_mutex_unlock(&((sync_ty *)param)->mutex_buffer_lock);

        printf("Producer No %d --> sum of array %d \n",((sync_ty *)param)->thread_id, SumArr(res));
        
        sem_post(&((sync_ty *)param)->semaphore_ready_to_read);         

    }
    return NULL;
}

void *ConsumerAct(void *param)
{
    int num_of_iterations = 2;
    int *data = NULL;

    while(num_of_iterations)
    {
        --num_of_iterations;

        sem_wait(&((sync_ty *)param)->semaphore_ready_to_read);

        pthread_mutex_lock(&((sync_ty *)param)->mutex_buffer_lock);

        BufferRead(((sync_ty *)param)->buffer,&data,sizeof(size_t));

        pthread_mutex_unlock(&((sync_ty *)param)->mutex_buffer_lock);
            
        printf("Consumer No %d --> sum of array %d \n",((sync_ty *)param)->thread_id, SumArr(data));

        sem_post(&((sync_ty *)param)->semaphore_ready_to_write);
    }

    return NULL;
}

int main()
{
    pthread_t producers[NUM_OF_PRODUCERS];
    pthread_t consumers[NUM_OF_CONSUMERS];
    int i = 0;
    int status = 0;

    sync_ty sync;

    sync.buffer = BufferCreate(NUM_OF_ELEMENTS * sizeof(size_t));
    ExitProgIfFail(NULL != sync.buffer);

    status = pthread_mutex_init(&sync.mutex_buffer_lock,NULL);
    ExitProgIfFail(0 == status);

    status = sem_init((&sync.semaphore_ready_to_read), 0, 0);
    ExitProgIfFail(0 == status);

    status = sem_init((&sync.semaphore_ready_to_write), 0, 0);
    ExitProgIfFail(0 == status);


    for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		sync.thread_id = i;

        status = pthread_create(&producers[i],NULL, &ProducerAct, &sync);
        ExitProgIfFail(0 == status);
    }

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		sync.thread_id = i;

        status = pthread_create(&producers[i],NULL, &ConsumerAct, &sync);
        ExitProgIfFail(0 == status);
    }

	for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{   
        status = pthread_join(producers[i],NULL);
        ExitProgIfFail(0 == status);
    }


	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{   
        status = pthread_join(consumers[i],NULL);
        ExitProgIfFail(0 == status);
    }

	status = pthread_mutex_destroy(&sync.mutex_buffer_lock);
    ExitProgIfFail(0 == status);
    
    status = sem_destroy(&sync.semaphore_ready_to_write);
    ExitProgIfFail(0 == status);

    status = sem_destroy(&sync.semaphore_ready_to_read);
    ExitProgIfFail(0 == status);

	BufferDestroy(sync.buffer);

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

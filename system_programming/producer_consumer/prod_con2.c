/****************************************************************************
*	Project:	producer consumer             								*											*
*	Date: 		24/08/2022													*
*	Name: 		Amit Regev													*
*	Reviewer:												                *
*	Version: 	1.00														*
****************************************************************************/

#include <stdio.h> /*printf*/
#include <stdlib.h>  /*exit*/
#include <assert.h>
#include <pthread.h> 
#include <errno.h>
#include "dlinked_list.h"


#define NUM_OF_PRODUCERS 3
#define NUM_OF_CONSUMERS 3

#define SIZE_ARR 10 

static void ExitProgIfFail(int status);


dlist_ty *list = NULL;
static pthread_mutex_t mutex_list_lock = PTHREAD_MUTEX_INITIALIZER;
static int volatile data_count = 0; /*share data counter*/


static int *Produce(int num);
static int SumArr(int *arr);

void *ProducerAct(void *param)
{
    int num_of_iterations = 5;
    int *numbers = NULL;
    static int num = 0;
    int status = 0;
    void *status_ptr = NULL;
    size_t prod_thread_number = (size_t)param;

    while(num_of_iterations)
    {
        --num_of_iterations;
        ++num;

        numbers = Produce(num);
        ExitProgIfFail(numbers != NULL);
        
        status = pthread_mutex_lock(&mutex_list_lock);
        ExitProgIfFail(status == 0);
        
        status_ptr = DListPushFront(list, numbers);
        ExitProgIfFail(status_ptr != NULL);
        
        status = pthread_mutex_unlock(&mutex_list_lock);
        ExitProgIfFail(status == 0);

        __atomic_add_fetch(&data_count, 1, __ATOMIC_SEQ_CST);

        printf("Producer No %ld --> sum of array %d \n",prod_thread_number, SumArr(numbers));
       
    }

    return NULL;
}

void *ConsumerAct(void *param)
{
    int num_of_iterations = 2;
    int *data = NULL;
    int status = 0;
    

    while(num_of_iterations)
    {
        --num_of_iterations;

        while(!data_count)
        {
           /*busy wait*/ 
        }

        status = pthread_mutex_lock(&mutex_list_lock);
        ExitProgIfFail(status == 0);
        printf("data %d\n", data_count);
        if(!DListIsEmpty(list))
        {
            data = (int *)DListPopBack(list);
            ExitProgIfFail(data != NULL);
        }

        status = pthread_mutex_unlock(&mutex_list_lock);
        ExitProgIfFail(status == 0);


        printf("Consumer No %ld --> sum of array %d \n",(size_t)param, SumArr(data));
        free(data);


        __atomic_sub_fetch(&data_count,1,__ATOMIC_SEQ_CST);

    }

    return NULL;
}


int main()
{
    pthread_t producers[NUM_OF_PRODUCERS];
    pthread_t consumers[NUM_OF_CONSUMERS];
    size_t i = 0;
    int status = 0;

    list = DListCreate();
    ExitProgIfFail(list != NULL);


    for (i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		status = pthread_create(&producers[i],NULL, &ProducerAct,(void *)i);
        ExitProgIfFail(status == 0);
    }

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        status = pthread_create(&consumers[i],NULL, &ConsumerAct, (void *)i);
        ExitProgIfFail(status == 0);
    }

	for(i = 0; i < NUM_OF_PRODUCERS; ++i)
	{
		status = pthread_join(producers[i],NULL);
        ExitProgIfFail(status == 0);
    }

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
		status = pthread_join(consumers[i],NULL);
        ExitProgIfFail(status == 0);
	}

	/*status = pthread_mutex_destroy(&mutex_list_lock);
    ExitProgIfFail(0 == status);*/
    
	DListDestroy(list);

	return 0;	
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



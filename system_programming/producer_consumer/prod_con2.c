/****************************************************************************
*	Project:	producer consumer             								*											*
*	Date: 		24/08/2022													*
*	Name: 		Amit Regev													*
*	Reviewer:												                *
*	Version: 	1.00														*
****************************************************************************/
/*

g_list pointer
g_mutex_flag
g_is_data_ready

1. Dlist create --> g_list

2. init mutex

3. for  
        pthread create -> producer i = 0  --> i < magic_num
        pthread create -> consumer i = 0  --> i < magic_num
      
4. for 
        pthread join -> producer i = 0 producer i = 0  --> i < magic_num
        pthread join -> consumer consumer i = 0  --> i < magic_num

5. mutex destroy

6. Dlist destroy g_list


        producer routine:

        1. while(num of iterations)

        2. mutex lock -> g_mutex_flag

        3  DlistPushFront(g_list)
            write on data node 

        4. mutex unlock -> g_mutex_flag 

        5. add 1 to value of g_is_data_ready  - atomic operator

        6. -- num of iterations

        consumer routine:

        1.  while(num of iterations)
        
        2. while(!g_is_data_ready)  //busy wait


                update value of counter in local_arr

            1.3 static counter++;

            1.4 while(g_is_data_ready)  //busy wait

            1.5 copy from local_arr to g_arr
 

            1.7 --num of iterations
        


        2.1 while (num of iterations) 


            2.2 while(!g_is_data_ready)  //busy wait

            2.3 copy from global arr to local arr

            2.4  update value of g_is_data_free to 0 - atomic operator

            2.5 for 0- -> magic_num
                sum local arr --> sum

            2.6 sum = 0

            2.7  --num of iterations
                 
    
    */
#include <stdio.h> /*printf*/
#include <stdlib.h>  /*exit*/
#include <pthread.h> 
#include <errno.h>
#include "dlinked_list.h"


#define NUM_OF_THREADS 4



dlist_ty *g_list = NULL;
static pthread_mutex_t mutex_list_lock = PTHREAD_MUTEX_INITIALIZER;
static unsigned char data_count = 0; /*share data counter*/

void *ProducerAct(void *param)
{
    static int num_of_iterations = 5;
    int data = 1;
    param = param;

    while(num_of_iterations)
    {
        
        pthread_mutex_lock(&mutex_list_lock);
        
        DListPushFront(g_list, data);
        
        pthread_mutex_unlock(&mutex_list_lock);
        
        printf("pushed number %d from producer\n", data);

        ++data;

        --num_of_iterations;

        __atomic_add_fetch(&data_count, 1, __ATOMIC_SEQ_CST);       
       
    }

    return NULL;
}

void *ConsumerAct(void *param)
{
    static int num_of_iterations = 5;
    int data = 0;
    param = param;

    while(num_of_iterations)
    {
        while(!data_count)
        {
           /*busy wait*/ 
        }

        pthread_mutex_lock(&mutex_list_lock);

        if(!DListIsEmpty(g_list))
        {
            data = (int)DListPopBack(g_list);
        }

        pthread_mutex_unlock(&mutex_list_lock);
    
        printf("poped number %d from consumer\n", data);

        --num_of_iterations;

        __atomic_sub_fetch(&data_count,1,__ATOMIC_SEQ_CST);

    }

    return NULL;
}

int main()
{
    pthread_t producers[NUM_OF_THREADS];
    pthread_t consumers[NUM_OF_THREADS];
    int i = 0;
    int status = 0;

    g_list = DListCreate();
    ExitProgIfFail(g_list == NULL);

    for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_create(&producers[i],NULL, &ProducerAct, NULL);
        ExitProgIfFail(status != 0);

        status = pthread_create(&consumers[i],NULL, &ConsumerAct, NULL);
        ExitProgIfFail(status != 0);
    }

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		status = pthread_join(producers[i],NULL);
        ExitProgIfFail(status != 0);

		status = pthread_join(consumers[i],NULL);
        ExitProgIfFail(status != 0);
	}

	pthread_mutex_destroy(&mutex_list_lock);

	DListDestroy(g_list);

	return 0;	
}


static void ExitProgIfFail(int status)
{
    if(status)
    {
        strerror(errno);
        exit(status);
    }

    return;
}




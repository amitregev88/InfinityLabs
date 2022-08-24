/****************************************************************************
*	Project:	producer consumer             								*												*
*	Date: 		24/08/2022													*
*	Name: 		Amit Regev													*
*	Reviewer:												                *
*	Version: 	1.00														*
****************************************************************************/


/*  1. pthread create -> producer
        1.1 while(num of iterations)        

            1.2 for 0 -> magic_num
                update value of counter in local_arr

            1.3 static counter ++;

            1.4 while(g_is_data_ready)  //busy wait

            1.5 copy from local_arr to g_arr
 
            1.6 update value of g_is_data_free to 1 - atomic operator

            1.7 --num of iterations
        

    2. pthread create -> consumer

        2.1 while (num of iterations) 


            2.2 while(!g_is_data_ready)  //busy wait

            2.3 copy from global arr to local arr

            2.4  update value of g_is_data_free to 0 - atomic operator

            2.5 for 0- -> magic_num
                sum local arr --> sum

            2.6 sum = 0

            2.7  --num of iterations
                 
    3. pthread join -> producer
    4. pthread join -> consumer
    
    */

#include <stdio.h> /*printf*/
#include <string.h> /* memcpy*/
#include <pthread.h> 

#define ARR_SIZE 10

static unsigned char g_is_data_ready = 0;
static int g_arr[ARR_SIZE];


void *ProducerAct(void *param)
{
    static int counter = 1;
    int prod_mums[ARR_SIZE] = {0};
    int i = 0;
    static int num_of_iterations = 3;
    param = param;

    
    while(num_of_iterations)
    {
        for(i = 0; i < ARR_SIZE; ++i)
        {
            prod_mums[i] = counter;
        }

         ++counter;
                
        while(g_is_data_ready)
        {
            /*busy wait*/
        }
    
        memcpy(g_arr,prod_mums,sizeof(int) * ARR_SIZE);

        __atomic_store_8(&g_is_data_ready,1,__ATOMIC_SEQ_CST);

        --num_of_iterations;
    }
    
       
    return NULL;
}

void *ConsumerAct(void *param)
{
    int sum_arr = 0;
    int cons_nums[ARR_SIZE] = {0};
    int i = 0;
    static int num_of_iterations = 3;
    param = param;

    while(num_of_iterations)
    {
        
        while(!g_is_data_ready)
        {
            /*busy wait*/
        }
    
        memcpy(cons_nums,g_arr,sizeof(int) * ARR_SIZE);
          
        __atomic_store_8(&g_is_data_ready,0,__ATOMIC_SEQ_CST);

        for(i = 0; i < ARR_SIZE; ++i)
        {
            sum_arr += cons_nums[i];
        }
            
        printf("SUM OF GLOBAL ARR IS : %d\n", sum_arr);

        sum_arr = 0;

        --num_of_iterations;
    }
    return NULL;
}

int main()
{
    pthread_t consumer;
    pthread_t producer;

    if (pthread_create(&producer, NULL, ProducerAct ,NULL) != 0)
    {
        perror("pthread_create of producer failed\n");
        return 1;
    }

    if (pthread_create(&consumer, NULL, ConsumerAct ,NULL) != 0)
    {
        perror("pthread_create of consumer failed\n");
        return 1;
    }



    if (pthread_join(consumer, NULL)  != 0)
    {
        perror("pthread_join of consumer failed\n");
        return 1;
    }

    if (pthread_join(producer, NULL)  != 0)
    {
        perror("pthread_join of producer failed\n");
        return 1;
    }

    

    return 0;

}






    
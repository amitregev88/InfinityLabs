#include <stdio.h> /* printf*/
#include <stdlib.h>  /*exit*/
#include <errno.h>
#include <assert.h>

#include <pthread.h>
#include <semaphore.h>

#define NUM_OF_COMSUMERS 4
#define SIZE_ARR 10 


typedef struct 
{
    int *data;

    int uid;

    sem_t done_read;

    pthread_mutex_t data_guard;

    pthread_cond_t cond_message;

    size_t thread_id; 

    int pass_data_no;

}data_ty;

sem_t g_done_read;


static int *Produce(int data);
static void ExitProgIfFail(int status);
static int SumArr(int *arr);
void *ProducerAct(void *param);
void *ConsumerAct(void *param);

int main(void)
{
    pthread_t provider;
    pthread_t obserders[NUM_OF_COMSUMERS];
    size_t i = 0;
    int status = 0;
    data_ty sync;

    pthread_mutex_t data_lock = PTHREAD_MUTEX_INITIALIZER;
    pthread_cond_t cond_mes = PTHREAD_COND_INITIALIZER;

    sync.cond_message = cond_mes;
    sync.data_guard = data_lock;

    sync.pass_data_no = -1;
    
    status = sem_init(&g_done_read,0,NUM_OF_COMSUMERS);
    ExitProgIfFail(status == 0);


    /*status = sem_init(&(sync.done_read),0,NUM_OF_COMSUMERS);
    ExitProgIfFail(status == 0);*/

    status = pthread_mutex_init(&(sync.data_guard), NULL); 
    /*ExitProgIfFail(status == 0);*/


	status = pthread_create(&provider,NULL, &ProducerAct, NULL);
    /*ExitProgIfFail(status == 0);*/


    for (i = 0; i < NUM_OF_COMSUMERS; ++i)
	{
		sync.thread_id = i;
        status = pthread_create(&obserders[i],NULL, &ConsumerAct,&sync);
        ExitProgIfFail(status == 0);
	}

	for (i = 0; i < NUM_OF_COMSUMERS; ++i)
	{
		status = pthread_join(obserders[i],NULL);
        ExitProgIfFail(status == 0);
	}

	pthread_mutex_destroy(&(sync.data_guard));
    sem_destroy(&(sync.done_read));   

	return 0;	
}

void *ProducerAct(void *param)
{
    size_t i = 0;
    int num_of_iteration = 5;
    int num = 0;
    int *res = NULL;
    int status = 0;

    while(num_of_iteration)
    {  
        --num_of_iteration;
        ++num;

        res = Produce(num);
        ExitProgIfFail(res != NULL);

          
        for(i = 0; i < NUM_OF_COMSUMERS; ++i)
        {
            /*status = sem_wait(&((data_ty *)param)->done_read);
            ExitProgIfFail(status != 0);*/

            status = sem_wait(&g_done_read);
            ExitProgIfFail(status != 0);
        }

        status = pthread_mutex_lock(&((data_ty *)param)->data_guard);
        ExitProgIfFail(status != 0);

        ((data_ty *)param)->data = res;
        ((data_ty *)param)->pass_data_no += 1;     

        status = pthread_mutex_unlock(&((data_ty *)param)->data_guard);
        ExitProgIfFail(status != 0);

        printf("data from publisher is:  %d\n",SumArr(res));

        status = pthread_cond_broadcast(&((data_ty *)param)->cond_message);   
        ExitProgIfFail(status != 0);


    }
    return NULL;
}

void *ConsumerAct(void *param)
{
    int curr_message = 0;

    int num_of_iteration = 5;

    int *data = NULL;

    while(num_of_iteration)
    {
        --num_of_iteration;

        /*sem_post(&((data_ty *)param)->done_read);*/
        sem_post(&g_done_read);
        
        pthread_mutex_lock(&((data_ty *)param)->data_guard);

        while (((data_ty *)param)->pass_data_no == curr_message)
        {
            data = ((data_ty *)param)->data;
            pthread_cond_wait(&((data_ty *)param)->cond_message, &((data_ty *)param)->data_guard);         
        }
        
        printf("data from observer num %ld is:  %d\n", ((data_ty *)param)->thread_id ,SumArr(data));

        curr_message  = ((data_ty *)param)->pass_data_no;
               
        pthread_mutex_unlock(&((data_ty *)param)->data_guard);
    }

    return NULL;
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
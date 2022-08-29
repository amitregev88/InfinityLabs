#include <stdio.h> /* printf*/
#include <stdlib.h>  /*exit*/
#include <pthread.h>
#include <semaphore.h>


#define KEEP_RUNNING 1
#define NUM_OF_CONSUMERS 4

typedef struct 
{
    int data;

    int uid;

}data_ty;


static pthread_mutex_t data_guard = PTHREAD_MUTEX_INITIALIZER;

static sem_t done_read ;


static data_ty data_from_publisher = {0,-1};

static pthread_cond_t cond_message = PTHREAD_COND_INITIALIZER;

static void ExitProgIfFail(int status);



void *ProducerAct(void *param)
{
   
    int status = 0;
    size_t i = 0;

    while(KEEP_RUNNING)
    {  

        for(i = 0; i < NUM_OF_CONSUMERS; ++i)
        {
            sem_wait(&done_read);
        }
        status = pthread_mutex_lock(&data_guard);
        ExitProgIfFail(0 == status);

        data_from_publisher.data = rand() % 100;
        data_from_publisher.uid += 1; 
        
        status = pthread_mutex_unlock(&data_guard);
        ExitProgIfFail(0 == status);

        printf("data from publisher is:  %u\n",data_from_publisher.data);

        status = pthread_cond_broadcast(&cond_message);   
        ExitProgIfFail(0 == status);

    }

    return NULL;
}

void *ConsumerAct(void *param)
{
    int curr_uid = 0;
    int status = 0;


    while(KEEP_RUNNING)
    {
        
        sem_post(&done_read);
        
        status = pthread_mutex_lock(&data_guard);
        ExitProgIfFail(0 == status);

        while (data_from_publisher.uid == curr_uid)
        {
            pthread_cond_wait(&cond_message,&data_guard);
        }

        curr_uid  = data_from_publisher.uid;
               
        status = pthread_mutex_unlock(&data_guard);
        ExitProgIfFail(0 == status);

        printf("data from observer num %lu is:  %u\n", (size_t)param ,data_from_publisher.data);
    }

    return NULL;
}

int main()
{
    pthread_t provider;
    pthread_t obserders[NUM_OF_CONSUMERS];
    size_t i;
    int status = 0;
    
    status = sem_init(&done_read,0,NUM_OF_CONSUMERS);
    ExitProgIfFail(0 == status);

    status = pthread_mutex_init(&data_guard, NULL);
    ExitProgIfFail(0 == status);

	status = pthread_create(&provider,NULL, &ProducerAct, NULL);
    ExitProgIfFail(0 == status);

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		status = pthread_create(&obserders[i],NULL, &ConsumerAct,(void *)i);
        ExitProgIfFail(0 == status);
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		status = pthread_join(obserders[i],NULL);
        ExitProgIfFail(0 == status);
	}

	status = pthread_mutex_destroy(&data_guard);
    ExitProgIfFail(0 == status);

    status = sem_destroy(&done_read);
    ExitProgIfFail(0 == status);

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
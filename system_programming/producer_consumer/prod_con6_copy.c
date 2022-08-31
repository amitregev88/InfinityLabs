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

typedef struct
{
    pthread_mutex_t data_guard;

    sem_t done_read;

    pthread_cond_t cond_message;

    data_ty *publisher_data; 

    size_t thread_no;

}sync_ty;



static void ExitProgIfFail(int status);



void *ProducerAct(void *param)
{
   
    int status = 0;
    size_t i = 0;

    while(KEEP_RUNNING)
    {  
       
        for(i = 0; i < NUM_OF_CONSUMERS; ++i)
        {
            sem_wait(&((sync_ty *)param)->done_read);
        }
        status = pthread_mutex_lock(&((sync_ty *)param)->data_guard);
        ExitProgIfFail(0 == status);

        ((sync_ty *)param)->publisher_data->data = rand() % 100;
        ((sync_ty *)param)->publisher_data->uid +=1; 
        
        status = pthread_mutex_unlock(&((sync_ty *)param)->data_guard);
        ExitProgIfFail(0 == status);

        printf("data from publisher is:  %u\n",((sync_ty *)param)->publisher_data->data);

        status = pthread_cond_broadcast(&((sync_ty *)param)->cond_message);   
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
        sem_post(&((sync_ty *)param)->done_read);
        
        status = pthread_mutex_lock(&((sync_ty *)param)->data_guard);
        ExitProgIfFail(0 == status);

        while (((sync_ty *)param)->publisher_data->uid == curr_uid)
        {
            pthread_cond_wait(&((sync_ty *)param)->cond_message, &((sync_ty *)param)->data_guard);
        }

        curr_uid  = ((sync_ty *)param)->publisher_data->uid;
               
        status = pthread_mutex_unlock(&((sync_ty *)param)->data_guard);
        ExitProgIfFail(0 == status);

        printf("data from observer num %lu is:  %u\n",((sync_ty *)param)->thread_no , ((sync_ty *)param)->publisher_data->data);
    }

    return NULL;
}

int main()
{
    pthread_t provider;
    pthread_t obserders[NUM_OF_CONSUMERS];
    size_t i = 0;
    int status = 0;
    sync_ty sync;
    pthread_cond_t cond_mess = PTHREAD_COND_INITIALIZER;

    data_ty publisher_data;

    pthread_mutex_t guard = PTHREAD_MUTEX_INITIALIZER;
    sync.data_guard = guard;   

    publisher_data.data = 0;
    publisher_data.uid = -1;
    sync.thread_no = 0;

    sync.publisher_data = &publisher_data;

    sync.cond_message = cond_mess;
   
    status = sem_init(&sync.done_read, 0, NUM_OF_CONSUMERS);
    ExitProgIfFail(0 == status);

    status = pthread_mutex_init(&sync.data_guard, NULL);
    ExitProgIfFail(0 == status);

	status = pthread_create(&provider,NULL, &ProducerAct, &sync);
    ExitProgIfFail(0 == status);

    for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		sync.thread_no = i;

        status = pthread_create(&obserders[i],NULL, &ConsumerAct,&sync);
        ExitProgIfFail(0 == status);
	}

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		status = pthread_join(obserders[i],NULL);
        ExitProgIfFail(0 == status);
	}

	status = pthread_mutex_destroy(&sync.data_guard);
    ExitProgIfFail(0 == status);

    status = sem_destroy(&sync.done_read);
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

/*****************************************includes*******************************/
#include <stdio.h>      /* printf*/
#include <stdlib.h>     /*exit*/
#include <pthread.h>    /*pthread_create pthread join , pthread_cond_broadcast*/
#include <semaphore.h>  /*sem_init, sem_wait , sem_post*/

/*******************************macros************************************/

#define KEEP_RUNNING 1
#define NUM_OF_CONSUMERS 4

/***************************  farward declaretions  ********************************/

typedef struct 
{
    int producer_num;

    int uid;

}producer_data_ty;

typedef struct
{
    pthread_mutex_t *data_guard;

    sem_t *done_read;

    pthread_cond_t *cond_message;

    producer_data_ty *publisher_data; 

    size_t thread_no;

}sync_ty;

typedef void* (*thread_routine)(void*);

/***************************  static functions declaretions  ********************************/

static void ExitProgIfFail(int status);
static void *ProducerAct(sync_ty *param);
static void *ConsumerAct(sync_ty *param);

/***************************  main function  ************************************************/
int main(void)
{
    pthread_t provider;
    pthread_t obserders[NUM_OF_CONSUMERS];
    size_t i = 0;
    int status = 0;
    sync_ty sync[NUM_OF_CONSUMERS];
    pthread_cond_t cond_mess = PTHREAD_COND_INITIALIZER;
    sem_t sema_done_read;
    producer_data_ty publisher_data;
    pthread_mutex_t guard = PTHREAD_MUTEX_INITIALIZER;

    publisher_data.producer_num = 0;
    publisher_data.uid = -1;

    status = sem_init(&sema_done_read, 0, NUM_OF_CONSUMERS);
    ExitProgIfFail(0 == status);


    for(i = 0; i < NUM_OF_CONSUMERS; ++i)
    {
        sync[i].data_guard = &guard;
        sync[i].done_read = &sema_done_read;
        sync[i].cond_message = &cond_mess;
        sync[i].publisher_data = &publisher_data; 
        sync[i].thread_no = i;    

        status = pthread_create(&obserders[i],NULL, (thread_routine )ConsumerAct,&sync[i]);
        ExitProgIfFail(0 == status);
    }
  
	status = pthread_create(&provider,NULL, (thread_routine )ProducerAct, &sync);
    ExitProgIfFail(0 == status);

	for (i = 0; i < NUM_OF_CONSUMERS; ++i)
	{
		status = pthread_join(obserders[i],NULL);
        ExitProgIfFail(0 == status);
	}

	status = pthread_mutex_destroy(sync->data_guard);
    ExitProgIfFail(0 == status);

    status = sem_destroy(sync->done_read);
    ExitProgIfFail(0 == status);

	return 0;	
}

/***************************  producer function definition ********************************/

static void *ProducerAct(sync_ty *param)
{
    int status = 0;
    size_t i = 0;

    while(KEEP_RUNNING)
    {  
        for(i = 0; i < NUM_OF_CONSUMERS; ++i)
        {
            sem_wait(param->done_read);
        }

        status = pthread_mutex_lock(param->data_guard);
        ExitProgIfFail(0 == status);

        param->publisher_data->producer_num = rand() % 100;
        param->publisher_data->uid +=1; 
        
        status = pthread_mutex_unlock(((sync_ty *)param)->data_guard);
        ExitProgIfFail(0 == status);

        printf("data from publisher is:  %u\n",(param->publisher_data->producer_num));

        status = pthread_cond_broadcast(param->cond_message);   
        ExitProgIfFail(0 == status);
    }

    return NULL;
}

/***************************  consumer function definition    ********************************/
static void *ConsumerAct(sync_ty *param)
{
    int curr_uid = 0;
    int status = 0;
       

    while(KEEP_RUNNING)
    {
        sem_post(((sync_ty *)param)->done_read);
        
        status = pthread_mutex_lock(((sync_ty *)param)->data_guard);
        ExitProgIfFail(0 == status);

        while (((sync_ty *)param)->publisher_data->uid == curr_uid)
        {
            pthread_cond_wait(((sync_ty *)param)->cond_message, ((sync_ty *)param)->data_guard);
        }

        curr_uid  = ((sync_ty *)param)->publisher_data->uid;
               
        status = pthread_mutex_unlock(((sync_ty *)param)->data_guard);
        ExitProgIfFail(0 == status);

        printf("data from observer num %lu is: %u\n",param->thread_no , param->publisher_data->producer_num);
    }

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
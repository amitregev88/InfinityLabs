#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  /*exit*/
#include <semaphore.h>
#include "circ_buffer_size_t.h"

#define KEEP_RUNNING 1
#define NUM_OF_THREADS 4
#define NUM_OF_ELEMENTS 50

static pthread_mutex_t read_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t write_lock = PTHREAD_MUTEX_INITIALIZER;

static sem_t semaphore_ready_to_read;
static sem_t semaphore_ready_to_write;
static circ_buffer_sizet_ty *buffer = NULL;




void *ProducerAct(void *param)
{
   
    static size_t data = 0;


    while(KEEP_RUNNING)
    {  
        sem_wait(&semaphore_ready_to_write);

        pthread_mutex_lock(&write_lock);

        BufferWrite(buffer,data);

        pthread_mutex_unlock(&write_lock);

        printf("data from producer is:  %lu\n",data++);
        
        sem_post(&semaphore_ready_to_read);         

        sleep(1);  
    }
    return NULL;
}

void *ConsumerAct(void *param)
{
    size_t data = 0;
    param = param;

    while(KEEP_RUNNING)
    {
        sem_wait(&semaphore_ready_to_read);

        pthread_mutex_lock(&read_lock);

        data = BufferRead(buffer);

        pthread_mutex_unlock(&read_lock);
            
        printf("data from consumer is:  %lu\n",data);

        sem_post(&semaphore_ready_to_write);
 
    }

    return NULL;
}

int main()
{
    pthread_t producers[NUM_OF_COMSUMERS];
    pthread_t consumers[NUM_OF_COMSUMERS];
    size_t i;
    buffer = BufferCreate(NUM_OF_ELEMENTS * sizeof(size_t));

    if (NULL == buffer)
    {
        puts("creation of buffer failed\n ");
        exit(1);
    }


    if(sem_init(&semaphore_ready_to_read,0,0) != 0)
    {
        perror("sem_init failed\n");
        BufferDestroy(buffer);
        exit(1);
    }

    if(sem_init(&semaphore_ready_to_write,0,NUM_OF_ELEMENTS) != 0)
    {
        perror("sem_init failed\n");
        BufferDestroy(buffer);
        exit(1);
    }      
    
    if (pthread_mutex_init(&read_lock, NULL) != 0) 
	{
        perror("pthread_mutex_init of read failed\n");
        BufferDestroy(buffer);
        exit(1);
    }

    if (pthread_mutex_init(&write_lock, NULL) != 0) 
	{
        perror("pthread_mutex_init of write failed\n");
        BufferDestroy(buffer);
        exit(1);
    }

    for (i = 0; i < NUM_OF_COMSUMERS; ++i)
	{
		if (pthread_create(&producers[i],NULL, &ProducerAct, NULL) != 0)
		{
			perror("pthread_create failed for producer\n");
            BufferDestroy(buffer);
       		exit(1);
		}

		if (pthread_create(&consumers[i],NULL, &ConsumerAct, NULL) != 0)
		{
			perror("pthread_create failed for consumer\n");
            BufferDestroy(buffer);
       		exit(1);
		}
	}

	for (i = 0; i < NUM_OF_COMSUMERS; ++i)
	{
		if (pthread_join(producers[i],NULL) != 0)
		{
			perror("pthread_join failed for producers\n");
            BufferDestroy(buffer);
			exit(1);
		}
		if (pthread_join(consumers[i],NULL) != 0)
		{
			perror("pthread_join failed for consumers\n");
            BufferDestroy(buffer);
			exit(1);
		}
	}

	pthread_mutex_destroy(&read_lock);
	pthread_mutex_destroy(&write_lock);

    sem_destroy(&semaphore_ready_to_write);
    sem_destroy(&semaphore_ready_to_read);
    

	BufferDestroy(buffer);

	return 0;	
}





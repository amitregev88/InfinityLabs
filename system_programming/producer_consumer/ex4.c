#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  /*exit*/
#include <semaphore.h>
#include "circ_buffer.h"

#define KEEP_RUNNING 1
#define NUM_OF_THREADS 2
#define NUM_OF_ELEMENTS 50



static pthread_mutex_t buffer_lock = PTHREAD_MUTEX_INITIALIZER;
static sem_t semaphore_ready_to_read;
static sem_t semaphore_ready_to_write;
static circ_buffer_ty *buffer = NULL;




void *ProducerAct(void *param)
{
   
    size_t data = (size_t)param;


    while(KEEP_RUNNING)
    {  
        sem_wait(&semaphore_ready_to_write);

        pthread_mutex_lock(&buffer_lock);

        BufferWrite(buffer,&data, sizeof(size_t));

        pthread_mutex_unlock(&buffer_lock);

        printf("data from producer is:  %lu\n",data);
        
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

        pthread_mutex_lock(&buffer_lock);

        BufferRead(buffer,&data,sizeof(size_t));

        pthread_mutex_unlock(&buffer_lock);
            
        printf("data from consumer is:  %lu\n",data);

        sem_post(&semaphore_ready_to_write);
 
    }

    return NULL;
}

int main()
{
    pthread_t producers[NUM_OF_THREADS];
    pthread_t consumers[NUM_OF_THREADS];
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
    
    if (pthread_mutex_init(&buffer_lock, NULL) != 0) 
	{
        perror("pthread_mutex_init failed\n");
        BufferDestroy(buffer);
        exit(1);
    }

    for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (pthread_create(&producers[i],NULL, &ProducerAct, (void *)i) != 0)
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

	for (i = 0; i < NUM_OF_THREADS; ++i)
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

	pthread_mutex_destroy(&buffer_lock);
    sem_destroy(&semaphore_ready_to_write);
    sem_destroy(&semaphore_ready_to_read);
    

	BufferDestroy(buffer);

	return 0;	
}





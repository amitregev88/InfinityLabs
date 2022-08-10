#include<pthread.h>
#include <stdio.h>
#include <stdlib.h>  /*exit*/
#include<semaphore.h>
#include "dlinked_list.h"

#define KEEP_RUNNING 1
#define NUM_OF_THREADS 2


dlist_ty *list = NULL;
static pthread_mutex_t list_lock = PTHREAD_MUTEX_INITIALIZER;
static unsigned char data_count = 0;
static sem_t semaphore;




void *ProducerAct(void *param)
{
    int data = (int)param;

    while(KEEP_RUNNING)
    {
        
        pthread_mutex_lock(&list_lock);
        
        DListPushFront(list, param);
        
        pthread_mutex_unlock(&list_lock);

        sem_post(&semaphore);

        printf("pushed number %d from producer\n", data);

        usleep(50000);
        

         
    }
    return NULL;
}

void *ConsumerAct(void *param)
{
    int data = 0;
    param = param;

    while(KEEP_RUNNING)
    {
        sem_wait(&semaphore);

        pthread_mutex_lock(&list_lock);

        data = (int)DListPopBack(list);
        
        pthread_mutex_unlock(&list_lock);
        
        printf("poped number %d from consumer\n", data);

  
    }

    return NULL;
}

int main()
{
    pthread_t producers[NUM_OF_THREADS];
    pthread_t consumers[NUM_OF_THREADS];
    int i;

    if(sem_init(&semaphore,0,0) != 0)
    {
        perror("sem_init failed\n");
        exit(1);
    }
        
    
    if (pthread_mutex_init(&list_lock, NULL) != 0) 
	{
        perror("pthread_mutex_init failed\n");
        exit(1);
    }

    list = DListCreate();

    for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (pthread_create(&producers[i],NULL, &ProducerAct, (void *)i) != 0)
		{
			perror("pthread_create failed for producer\n");
       		exit(1);
		}

		if (0 != pthread_create(&consumers[i],NULL, &ConsumerAct, (void *)i))
		{
			perror("pthread_create failed for consumer\n");
       		exit(1);
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (pthread_join(producers[i],NULL) != 0)
		{
			perror("pthread_join failed for producers\n");
			exit(1);
		}
		if (pthread_join(consumers[i],NULL) != 0)
		{
			perror("pthread_join failed for consumers\n");
			exit(1);
		}
	}

	pthread_mutex_destroy(&list_lock);

	DListDestroy(list);

	return 0;	
}





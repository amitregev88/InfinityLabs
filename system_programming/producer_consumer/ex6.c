#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>  /*exit*/
#include <semaphore.h>


#define KEEP_RUNNING 1
#define NUM_OF_THREADS 4

typedef struct 
{
    int producer_num;

    int uid;

}producer_data_ty;


static pthread_mutex_t data_lock = PTHREAD_MUTEX_INITIALIZER;

static sem_t done_read ;


static data_ty data_from_publisher = {0,-1};

static pthread_cond_t cond_message = PTHREAD_COND_INITIALIZER;




void *ProducerAct(void *param)
{
   
    
    size_t i;


    while(KEEP_RUNNING)
    {  


        for(i=0; i< NUM_OF_THREADS; ++i)
        {
            sem_wait(&done_read);
        }
        pthread_mutex_lock(&data_lock);

        data_from_publisher.data = rand() % 100;
        data_from_publisher.uid += 1; 

        printf("data from publisher is:  %u\n",data_from_publisher.data);

        pthread_mutex_unlock(&data_lock);

        pthread_cond_broadcast(&cond_message);   

    }
    return NULL;
}

void *ConsumerAct(void *param)
{
    int curr_uid = 0;

    while(KEEP_RUNNING)
    {
        
        sem_post(&done_read);
        
        pthread_mutex_lock(&data_lock);

        while (data_from_publisher.uid == curr_uid)
        {
            pthread_cond_wait(&cond_message,&data_lock);
            
        }
        
        printf("data from observer num %lu is:  %u\n", (size_t)param ,data_from_publisher.data);

        curr_uid  = data_from_publisher.uid;

               
        pthread_mutex_unlock(&data_lock);

    }

    return NULL;
}

int main()
{
    pthread_t provider;
    pthread_t obserders[NUM_OF_THREADS];
    size_t i;
    

    if(sem_init(&done_read,0,NUM_OF_THREADS) != 0)
    {
        perror("sem_init failed\n");
        exit(1);
    }  
    
    if (pthread_mutex_init(&data_lock, NULL) != 0) 
	{
        perror("pthread_mutex_init failed\n");
        exit(1);
    }


	if (pthread_create(&provider,NULL, &ProducerAct, NULL) != 0)
	{
		perror("pthread_create failed for producer\n");
       	exit(1);
	}

    for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (pthread_create(&obserders[i],NULL, &ConsumerAct,(void *)i) != 0)
		{
			perror("pthread_create failed for consumer\n");
       		exit(1);
		}
	}

	for (i = 0; i < NUM_OF_THREADS; ++i)
	{
		if (pthread_join(obserders[i],NULL) != 0)
		{
			perror("pthread_join failed for obserders\n");
			exit(1);
		}
	}

	pthread_mutex_destroy(&data_lock);
    sem_destroy(&done_read);   

	return 0;	
}





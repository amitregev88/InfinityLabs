#include<pthread.h>
#include<stdio.h>

#define KEEP_RUNNING 1

static unsigned char g_is_data_ready = 0;
static char *data = NULL;

void *ProducerAct(void *param)
{
    param = param;

    while(KEEP_RUNNING)
    {
        while(g_is_data_ready)
        {
            /*empty*/
        }

    data = "this is producer routine\n";
    printf("%s", data);
    __atomic_store_8(&g_is_data_ready,1,__ATOMIC_SEQ_CST);
       
    }
    return NULL;
}

void *ConsumerAct(void *param)
{
    param = param;

    while(KEEP_RUNNING)
    {
        while(!g_is_data_ready)
        {
           /*empty*/ 
        }
            data = "this is consumer routine\n";
            printf("%s", data);
            __atomic_store_8(&g_is_data_ready,0,__ATOMIC_SEQ_CST);
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






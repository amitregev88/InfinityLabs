#include<pthread.h>
#include<stdio.h>

#define KEEP_RUNNING 1

unsigned char g_flag = 0;

void *ProducerAct(void *param)
{
    param = param;

    while(KEEP_RUNNING)
    {
        while(!g_flag)
        {
            __atomic_add_fetch(&g_flag, 1, __ATOMIC_RELAXED);
            puts("this is producer routine\n");
            __atomic_sub_fetch(&g_flag, 1, __ATOMIC_RELAXED);
        }
    }
    return NULL;
}

void *ConsumerAct(void *param)
{
    param = param;

    while(KEEP_RUNNING)
    {
        while(!g_flag)
        {
            __atomic_add_fetch(&g_flag, 1, __ATOMIC_RELAXED);
            puts("this is consumer routine\n");
            __atomic_sub_fetch(&g_flag, 1, __ATOMIC_RELAXED);
        }
    }
    return NULL;
}

int main()
{
    pthread_t consumer;
    pthread_t producer;

    if (pthread_create(&consumer, NULL, ConsumerAct ,NULL) != 0)
    {
        perror("pthread_create of consumer failed\n");
        return 1;
    }

    if (pthread_create(&producer, NULL, ProducerAct ,NULL) != 0)
    {
        perror("pthread_create of producer failed\n");
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






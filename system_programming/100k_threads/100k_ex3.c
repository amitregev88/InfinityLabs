#include <stdio.h> /*printf*/
#include <string.h> /*strerror*/
#include <errno.h> 
#include <pthread.h> 

#define NUM_OF_THREADS 100000

static int volatile g_active_threads = NUM_OF_THREADS;
static pthread_mutex_t g_active_threads_lock = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t g_cond_var = PTHREAD_COND_INITIALIZER;

static size_t g_nums[NUM_OF_THREADS] = {0};

void *InitArr(void *num_indx)
{
	size_t index = (size_t)num_indx;
	g_nums[index] = index;

    /*broadscast*/
    pthread_mutex_lock(&g_active_threads_lock);

    --g_active_threads;
    
    if (0 == g_active_threads)
    {
        pthread_cond_broadcast(&g_cond_var);
    }

    pthread_mutex_unlock(&g_active_threads_lock);

    pthread_exit(NULL);
}


int main(void)
{
    size_t i = 0;
    pthread_attr_t detach_thread;
    pthread_t threads[NUM_OF_THREADS];
    time_t start , end ;
    pthread_attr_init(&detach_thread);
    pthread_attr_setdetachstate(&detach_thread,PTHREAD_CREATE_DETACHED);
        
    start = time(NULL);

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
  
        if(0 != pthread_create(&threads[i],&detach_thread,InitArr,(void *)i))
        {
            printf("creation of thread No %ld failed\n", i);
            fprintf(stderr, "pthread_create failed: %s\n\n", strerror(errno));
        }
    }
     
    pthread_mutex_lock(&g_active_threads_lock);

    while(0 != g_active_threads)
    {
        pthread_cond_wait(&g_cond_var,&g_active_threads_lock);
    }
     
    pthread_mutex_unlock(&g_active_threads_lock);

    end = time(NULL);

    printf(" took  %ld sec\n",end - start);

    for(i = 0; i < NUM_OF_THREADS; ++i)
    {
        if (g_nums[i] != i) 
        {
            printf(" g_nums[%ld]  is worng:  %ld\n",i ,g_nums[i]);
        }  
    }

    pthread_attr_destroy(&detach_thread);

    return 0; 
}
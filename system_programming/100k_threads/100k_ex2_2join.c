#include <stdio.h> /*printf*/
#include <string.h> /*strerror*/
#include <errno.h> 
#include <pthread.h> 

#define NUM_OF_THREADS 100000


int g_nums[NUM_OF_THREADS] = {0};

void *InitArr(void *num_indx)
{
	size_t index = (size_t)num_indx;

	g_nums[index] = index;

	return NULL;
}


int main (void)
{
    size_t i = 0;
    pthread_t threads[NUM_OF_THREADS];
    time_t start , end ;
    
    
    start = time(NULL);

    for(i=0; i<NUM_OF_THREADS; ++i)
    {

        if(pthread_create(&threads[i],NULL,InitArr,(void *)i) == 0)
        {
            if(pthread_join(threads[i], NULL) != 0)
            {
                printf("pthread_join failed - thread No %ld \n", i);
                fprintf(stderr, "pthread_join failed: %s\n\n", strerror(errno));
                return errno;
                
            }
        }

        else
        {
            printf("pthread_create failed - thread No %ld \n", i);
            fprintf(stderr, "pthread_create failed: %s\n\n", strerror(errno));
            return errno;
        }

    }

    end = time(NULL);

    printf(" took  %ld sec\n",end-start);

    printf(" g_nums[%ld]  %d\n",i-1 ,g_nums[NUM_OF_THREADS - 1]);

    return 0; 

}
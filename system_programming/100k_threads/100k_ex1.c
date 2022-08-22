
#include <stdio.h>  /*printf*/
#include <unistd.h> /*sleep*/
#include <pthread.h>    /*pthead create*/
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
        pthread_create(&threads[i],NULL,InitArr,(void *)i);
    }

    end = time(NULL);

    printf(" took  %ld sec\n",end-start);

    sleep(10);

    for(i=0;i<NUM_OF_THREADS;++i)
    {
        if(i != g_nums[i])
        {
            printf("error creation of thead No %ld\n", i);
            break;
        }
    }

    return 0; 
}
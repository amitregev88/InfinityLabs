#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <string.h> /*strerror*/

int global_arr[100000] = {0};


void *InitArr(void *num_indx)
{
	int index = (int)num_indx;
	global_arr[index] = index;

	return NULL;
}

int main (void)
{
    int i = 0;
    pthread_t threads[100000];
    time_t start , end ;
    
    start = time(NULL);

    for(i=0; i<100000; ++i)
    {
        if(pthread_create(&threads[i],NULL,InitArr,(void *)i) != 0)
        {
            printf("creation of thread No %d failed\n", i);
            fprintf(stderr, "pthread_create failed: %s\n\n", strerror(errno));
        }
    }
    end = time(NULL);
    printf(" took  %ld sec\n",end-start);

    return 0; 
}
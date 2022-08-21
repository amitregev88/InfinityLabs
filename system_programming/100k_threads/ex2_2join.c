#include <stdio.h> /*printf*/
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

        while (pthread_create(&threads[i],NULL,InitArr,(void *)i) != 0)
        {
            if(pthread_join(threads[i-1], NULL) != 0)
            {
                printf("pthread_join failed - thread No %d \n", i);
                fprintf(stderr, "pthread_join failed: %s\n\n", strerror(errno));
            }
        }


    }

    end = time(NULL);

    printf(" took  %ld sec\n",end-start);

    printf(" global_arr[%d]  %d\n",i-1 ,global_arr[99999]);

/*
    sleep(10);

    for(i=0;i<100000;++i)
    {
        if(i != global_arr[i])
        {
            printf("error creation of thead No %d\n", i);
            break;

        }
    }
*/

    return 0; 


}
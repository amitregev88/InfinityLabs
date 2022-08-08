#include <pthread.h>
#include <stdio.h>


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

        pthread_create(&threads[i],NULL,InitArr,(void *)i);

    }

    end = time(NULL);

    printf(" took  %ld sec\n",end-start);

    sleep(10);

    for(i=0;i<100000;++i)
    {
        if(i != global_arr[i])
        {
            printf("error creation of thead No %d\n", i);
            break;

        }
    }


    return 0; 


}
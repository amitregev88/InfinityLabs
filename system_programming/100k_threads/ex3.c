#include <pthread.h>
#include <stdio.h>

int global_arr[100000] = {0};
pthread_attr_t detach_thread;

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
    pthread_attr_init(&detach_thread);
    pthread_attr_setdetachstate(&detach_thread,PTHREAD_CREATE_DETACHED);
    
    
    start = time(NULL);

    for(i=0; i<100000; ++i)
    {

        
        while (pthread_create(&threads[i],&detach_thread,InitArr,(void *)i) != 0)
        {
                /*empty*/
            
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
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define LONG_NUM 5000000000

typedef struct range
{
    size_t from;
    size_t to;

}range_ty;


void *Sum_Of_Divisors(void *param)
{
	range_ty *range = (range_ty *)param;

    size_t sum_of_divisors = 0;
    size_t i = 0;
    
    for(i= range->from; i< range->to ;++i)
    {
        if(0 == LONG_NUM % i)
        {
            sum_of_divisors += i;

        }
    }

    return *(void **)&sum_of_divisors;
}


int main (int argc ,char **argv)
{
    size_t i = 0;
    pthread_t *threads;
    range_ty *ranges;
    time_t start , end ;
    size_t sum =0;
    void * ret_val = NULL;
    size_t num_threads = 1;


    if(argc > 1)
    {
        num_threads = atoi(argv[1]);
    }
    
    threads = malloc(num_threads * sizeof(pthread_t));
    if(!threads)
    {
        return 1;
    }
    ranges = malloc(num_threads * sizeof(range_ty));
    if(!ranges)
    {
        free(threads);
        return 1;
    }

    start = time(NULL);

    for(i=0; i<num_threads; ++i)
    {
        ranges[i].from = (LONG_NUM / num_threads) * i + 1;
        ranges[i].to = LONG_NUM / num_threads * (i+1);

        if(pthread_create(&threads[i],NULL,Sum_Of_Divisors,&ranges[i])!= 0)
        {
            printf("thread create failed %ld\n",i);
        }
    }
  
    for(i=0; i<num_threads; ++i)
    {

        if(pthread_join(threads[i], /* (void **) */&ret_val) != 0)
        {
            printf("thread create failed %ld\n",i);
        }
    }

    sum += (size_t)ret_val;
            
    end = time(NULL);

    printf(" took  %ld sec\n",end-start);

    printf("Sum Of Divisors %ld\n",sum);

    return 0; 
}
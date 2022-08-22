#include <stdio.h> /*printf*/
#include <stdlib.h>  /*atoi*/
#include <pthread.h>

#define LONG_NUM 5000000000UL

void *Sum_Of_Divisors(void *param)
{
	
  size_t sum_of_divisors = 0;
  size_t i = 0;

  (void)param;

    #pragma omp parallel private(i) shared(sum_of_divisors) 

    #pragma omp for 

    for(i=1; i<= LONG_NUM ;++i)
    {
        if(0 == LONG_NUM % i)
        {
            sum_of_divisors += i;
        }
    }
    
    return (void *)sum_of_divisors;
}
  

int main()
{
    size_t i = 0;
    
    time_t start , end;

    void *sum = NULL;
       
    start = time(NULL);

    sum = Sum_Of_Divisors(NULL);
           
    end = time(NULL);

    printf("took  %ld sec\n",end-start);

    printf("Sum Of Divisors %lu\n",(size_t)sum);

    return 0; 
}
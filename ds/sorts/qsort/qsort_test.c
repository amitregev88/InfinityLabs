/*************************************************************
* Author: Amit Regev
* Date: 07/7/22 
* OL124 quick sort recursively Test.
*******************************************************************/
#include<stdio.h>
#include"sorts.h"

#define ARR_SIZE 15
#define ARR_SIZE2 10000000

static int arr[ARR_SIZE2] = {0};

int IntComp(const void *val1, const void *val2)
{

    return (*(int *)val1 - *(int *)val2);
}

int main()
{ 
    int unsorted_arr[ARR_SIZE] = {72,13,93,85,93,8,4,25,31,18,99,44,78,54,2};
    int i = 0;

    /*for(;i<ARR_SIZE;++i)
    {
        unsorted_arr[i] = rand();
    }
    */

    printf("\nThe unsorted array is:\n\n");

    for(i = 0; i < ARR_SIZE; ++ i)
    {
        printf("%d ", unsorted_arr[i]);
    }

    printf("\n\nAfter sorting by QuickSort function (recursively), the array is :\n\n");

    QuickSort(unsorted_arr,ARR_SIZE, sizeof(int),IntComp);
  
    for(i = 0; i < ARR_SIZE; ++i)
    {
        printf("%d ", unsorted_arr[i]);
    }

    printf("\n");
   
  	printf("\n\ncomparing between my QuickSort function implementation to linux's qsort:\n\n");

    CompareQuickSort(arr,ARR_SIZE2,sizeof(int),&IntComp);
    
    return 0;
}




    
    
    



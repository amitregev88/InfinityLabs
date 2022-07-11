/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 07/7/22 
* OL124 Merge Sort Recursively.
*******************************************************************/

#include <stdio.h>   /*printf*/
#include "sorts.h" 

#define ARR_SIZE 15

int main()
{ 
    int unsorted_arr[ARR_SIZE]= {72,13,93,85,93,8,4,25,31,18,99,44,78,54,2};
    int i = 0;

   /* for(;i<ARR_SIZE;++i)
    {
        unsorted_arr[i] = rand() % 100;
    }
    */

    printf("\nThe unsorted array is:\n\n");

    for(i = 0; i < ARR_SIZE; ++ i)
    {
      printf("%d ", unsorted_arr[i]);
    }

    printf("\n\nAfter sorting by MergeSort function (recursively), the array is :\n\n");

    MergeSort(unsorted_arr, ARR_SIZE);
  
    for(i = 0; i < ARR_SIZE; ++ i)
    {
      printf("%d ", unsorted_arr[i]);
    }

    printf("\n");
   
    return 0;
}

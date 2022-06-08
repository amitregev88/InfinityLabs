/*************************************************************
*
* OL124 Linear sorts project
*
*    Linear Sorts 
******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "comparison_and_linear_sorts.h"

void CoutingSort(int arr[], int output [], size_t size)
{
    
    size_t i = 0, j = 0;

    int min = 0, max = 0;

       
    
    assert(NULL != arr);
    assert(NULL != output);
    assert(size > 0);


    min = arr[i];
    max = arr[i];
    
    for(i = 1; i < size; ++i)
    {

        if(arr[i] < min)
        {
            min = arr[i];

        }

        if(arr[i] > max)
        {
            max = arr[i];

        }


    }


    int *temp_arr = (int *)malloc(sizeof(int) * (max - min + 1));
    if (NULL == temp_arr)
    {
        printf("memory allocation failed\n");
        return;

    }

    for(j = 0; j < max - min +1; ++j)
    {

       temp_arr[i] = 0;

    }

    for(i = 0; i < size; ++i)
    {
        
        temp_arr[arr[i] - min]++;
    }
        
        


    }






}
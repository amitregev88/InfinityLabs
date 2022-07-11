/*************************************************************
*
* OL124 Linear sorts project
*
*    Linear Sorts 
******************************************************************/

#include <assert.h> /* assert */
#include <stdlib.h> /* malloc */
#include "sorts.h"

void CoutingSort(int arr[], int output [], size_t size)
{
    
    int i = 0, j = 0, min = 0, max = 0;
    int *temp_arr = NULL;
  
    assert(NULL != arr);
    assert(NULL != output);
    assert(size > 0);

    min = arr[i];
    max = arr[i];
    
    for(i = 1; (size_t)i < size; ++i)
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

    /* memory allocation for temp arr  */
    temp_arr = (int *)calloc((max - min + 1),sizeof(int));
    if (NULL == temp_arr)
    {
        return;
    }

  

    /* Updates the number of appearance for each number in temp arr */
    for(i = 0; (size_t)i < size; ++i)
    {
       
        temp_arr[arr[i] - min]++;
    }
  
    
    
    for(i = 0; i < max - min + 1; ++i)
    {
        
        while(temp_arr[i] > 0)
        {
            output[j] = i + min;
            temp_arr[i]--;
            j++; 
        }
    }

    free(temp_arr);
    temp_arr = NULL;

}

/*************************************************************************************
* --- RadixSort --- sort a given arry using Radix Sort algorithm
**************************************************************************************/
/*void RadixSort(int arr[], int output[], size_t size, unsigned char num_of_bits)
{

    size_t i = 0;
	size_t max = 0;

	assert(NULL != arr);
	assert(NULL != output);
    assert(size > 0);
	assert(num_of_bits > 0);

	
    max = arr[i];
    for(i = 1; i < size; ++i)
    {
        if(arr[i] > max)
        {
            max = arr[i];
        }
    }

	for (i = 1; 0 < max/i; i <<=num_of_bits)
	{
		RadixCountSort(arr,output,size,num_of_bits,i);

    }

}
*/





/*************************************************************************************
* --- RandInsert --- insert size int numbers and insert them to given array
**************************************************************************************/
void RandInsert(int arr[], size_t size)
{

    size_t i = 0;

    assert(size > 0);
    assert(NULL != arr);

    for(i = 0; i < size; ++i)
    {
        arr[i] = rand() ;
    }
}


/*************************************************************************************
* --- IsSorted --- returns 1 if array is sorted, 0 otherwise
**************************************************************************************/
int IsSorted(int arr[], size_t size)
{
    size_t i = 0;

    assert(size > 0);
    assert(NULL != arr);

    for(i = 0; i < size - 1; ++i)
    {
        if(arr[i] > arr[i + 1])
        {
            return 0;
        }
        
    }

    return 1;
}




/*static void RadixCountSort(int arr[],int output[],size_t size,unsigned char num_of_bits, size_t exp)*/





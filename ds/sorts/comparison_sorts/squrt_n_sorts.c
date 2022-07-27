/*************************************************************
* Author: Amit Regev
* Reviewer: Amir Shachar
* OL124 Comparison Sorts 
*******************************************************************/


#include <assert.h>     /*  assert */
#include <stdlib.h>    /* rand */
#include <time.h>     /* clock */
#include <stdio.h>    /* printf*/
#include <sorts.h>

static void SwapInt(int *num1, int *num2);


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
        arr[i] = rand() % 1000;
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


/*************************************************************************************
* --- PrintSortTime --- insert our sort and print its time of action compered to qsort
**************************************************************************************/
void PrintSortTime(void (*SortFunc)(int arr[], size_t size),int arr[], size_t size, char *str)
{
    
    clock_t  start = 0, end = 0;

    assert(SortFunc != NULL);
    assert(size > 0);
    assert(NULL != arr);

    start = clock();
    SortFunc(arr, size);
    end = clock();

    printf("The runtime of function  %s  took  %f sec\n", str, ((double)(end - start))/CLOCKS_PER_SEC);

}

/*************************************************************************************
* --- BubbleSort --- sort a given arry using Bubble Sort algorithm
**************************************************************************************/
void BubbleSort(int arr[], size_t size)
{ 
    size_t i = 0, j = 0;


    assert(size > 0);
    assert(NULL != arr);
    

    while (i < size - 1)
    {

        for(j = 0;j < size - i - 1; ++j)
        {
            if (arr[j] > arr [j+1])
            {

                SwapInt(&arr[j], &arr[j + 1]);

            }
        }

        ++i;
    }
}

/*************************************************************************************
* --- SelectionSort --- sort a given arry using Selection Sort algorithm
**************************************************************************************/
void SelectionSort(int arr[], size_t size)
{
    size_t i = 0, j = 0;
    int index_min = 0;


    assert(size > 0);
    assert(NULL != arr);

    while (i < size - 1)
    {
        index_min = i;    
        
        for(j = i + 1; j < size; ++j)
        {
            if(arr[index_min] > arr[j])
            {
                index_min = j;
            }
        }

        SwapInt(&arr[index_min], &arr[i]);
        ++i;
    }
}

/*************************************************************************************
* --- InsertionSort --- sort a given arry using Insertion Sort algorithm
**************************************************************************************/

void InsertionSort(int arr[], size_t size)
{
    int i = 0, j = 0, tmp = 0;

    assert(size > 0);
    assert(NULL != arr);
    
    
    for(i = 1; (size_t)i < size; ++i)
    {
        tmp = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > tmp)
        {
            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = tmp;
    }
}


static void SwapInt(int *num1, int *num2)
{
    int temp = *num1;

    *num1 = *num2;
    *num2 = temp; 
}

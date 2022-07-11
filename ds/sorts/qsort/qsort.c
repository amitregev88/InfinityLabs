/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 07/7/22 
* OL124 quick sort recursively.
*******************************************************************/

#include<stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <time.h> /*clock*/
#include <stdio.h>/*printf*/
#include <assert.h>/*assert*/
#include"sorts.h"

static void QuickSortRec(void *base, size_t left ,size_t right,int (*compar)(const void *, const void *),size_t size, void *tmp_elem);

static size_t Pivot(void *base, size_t left, size_t right, size_t size ,int (*compar)(const void *, const void *),void *tmp_elem);

static void Swap(void *base, int i, int j, size_t size, void *tmp_elem);



void QuickSort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *))
{
    void *tmp = malloc(size);
    if(NULL == tmp)
    {
        return;
    }

    QuickSortRec(base,0,nmemb-1,compar,size,tmp);

    free(tmp);
}

static void QuickSortRec(void *base, size_t left ,size_t right,int (*compar)(const void *, const void *),size_t size, void *tmp_elem)
{
    size_t curr_pivot = 0;

    if(left >= right)
    {
        return;
    }
    
    curr_pivot = Pivot(base,left,right,size,compar,tmp_elem);


    if (curr_pivot > 0)
    {
        QuickSortRec(base,left,curr_pivot-1,compar,size,tmp_elem);

    }   

    QuickSortRec(base,curr_pivot+1,right,compar,size,tmp_elem);

}

static size_t Pivot(void *base, size_t left, size_t right, size_t size ,int (*compar)(const void *, const void *),void *tmp_elem)
{
    int i = left - 1 , j = left, pivot = right;
    char *iter_arr = base;

    for(; j < pivot; ++j)
    {
        if (compar(iter_arr + (size * pivot), iter_arr+ (size * j)) > 0)
        {
            ++i;
            Swap(base,i,j,size,tmp_elem);       
        }
    }

    Swap(base,i+1,pivot,size,tmp_elem);

    return i+1;
}

static void Swap(void *base, int i, int j, size_t size, void *tmp_elem)
{
    char *iter_i = (char *)base + (i * size);
	char *iter_j = (char *)base + (j * size);
      
    if (i==j)
    {
        return;
    }

	memcpy(tmp_elem, iter_i, size);
	memcpy(iter_i, iter_j, size);
	memcpy(iter_j, tmp_elem, size);
}

void CompareQuickSort(void *base, size_t nmeb, size_t size, int (*compar)(const void *, const void * ))
{
	clock_t start, end;

	RandInsert(base,nmeb);
	start = clock();	
	QuickSort(base,nmeb, size, compar);
	end = clock();

	printf("QuickSort took %f seconds to execute \n\n",(double)(end - start)/ CLOCKS_PER_SEC);

	RandInsert(base,nmeb);
	start = clock();
	qsort(base,nmeb, size, compar);
	end = clock();
	printf("Linux's qsort took %f seconds to execute \n",(double)(end - start)/ CLOCKS_PER_SEC);

}

/*************************************************************************************
* --- RandInsert --- insert size int numbers and insert them to given array
**************************************************************************************/
void RandInsert(int arr[], size_t size)
{
	size_t i = 0;
	assert(arr);

	for (i = 0; i < size; ++i)
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
	assert(arr);

	for (i = 1; i < size; ++i)
	{
		if (arr[i] < arr[i-1])
		{
			return 0;
		}
	}
	return 1;
}


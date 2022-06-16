/*************************************************************
*OL124  Test Compression Sorts Project
*
*   Tests
******************************************************************/

#include <stdio.h> /* printf */
#include <time.h> /* clock */
#include <assert.h> /* assert */

#include "comparison_and_linear_sorts.h"


#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


#define BUFFER 50000

static int arr[BUFFER] = {0};

static int arr2[BUFFER] = {0};

static void PrintCoutingSortTime(void (*SortFunc)(int arr[], int arr2[],size_t size),int arr[],int arr2[], size_t size, char *str);
static void InitArrWorstCase(int arr[], const size_t size);

int main()
{
	
	printf ("testing of CoutingSort function in case of random numbers:\n");
	RandInsert(arr,BUFFER);
	CoutingSort(arr, arr2,BUFFER);
	TEST(1, IsSorted(arr2,BUFFER));

	RandInsert(arr,BUFFER);
	PrintCoutingSortTime(&CoutingSort, arr, arr2, BUFFER, "CoutingSort");

	printf ("testing of CoutingSort function in worst case:\n");
	RandInsert(arr,BUFFER);
	CoutingSort(arr, arr2,BUFFER);
	InitArrWorstCase(arr2,BUFFER);
	PrintCoutingSortTime(&CoutingSort, arr, arr2, BUFFER, "CoutingSort");

    return 0;

}


static void PrintCoutingSortTime(void (*SortFunc)(int arr[], int arr2[],size_t size),int arr[],int arr2[], size_t size, char *str)
{
    
    clock_t  start = 0, end = 0;

    assert(SortFunc != NULL);
    assert(size > 0);
    assert(NULL != arr);
	assert(NULL != arr2);

    start = clock();
    SortFunc(arr, arr2, size);
    end = clock();

    printf("The runtime of function  %s  took  %f sec\n", str, ((double)(end - start))/CLOCKS_PER_SEC);

}

static void InitArrWorstCase(int arr[], const size_t size)
{
    size_t i = 0;

    for(i = 0; i < size; ++i)
    {
        arr[i] = size - i;
    }
}



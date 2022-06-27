/*************************************************************
*OL124  Test Compression Sorts Project
*
*   Tests
******************************************************************/

#include <stdio.h> /* printf */

#include "comparison_and_linear_sorts.h"

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


#define BUFFER 30000

static int arr[BUFFER] = {0};

static void InitArrWorstCase(int arr[], const size_t size);


int main()
{
	
	printf ("testing of BubbleSort function in case of random numbers:\n");
	RandInsert(arr,BUFFER);
	BubbleSort(arr,BUFFER);
	TEST(1, IsSorted(arr,BUFFER));

	RandInsert(arr,BUFFER);
	PrintSortTime(&BubbleSort,arr,BUFFER,"BubbleSort");

    printf ("\ntesting of BubbleSort function in worst case:\n");
    RandInsert(arr,BUFFER);
	BubbleSort(arr,BUFFER);
    InitArrWorstCase(arr, BUFFER);
    PrintSortTime(&BubbleSort,arr,BUFFER,"BubbleSort");




	printf ("\n\ntesting of SelectionSort function in case of random numbers:\n");
	RandInsert(arr,BUFFER);
	SelectionSort(arr,BUFFER);
	TEST(1, IsSorted(arr,BUFFER));

	RandInsert(arr,BUFFER);
	PrintSortTime(&SelectionSort,arr,BUFFER,"SelectionSort");

    printf ("\ntesting of SelectionSort function in worst case:\n");
    RandInsert(arr,BUFFER);
	SelectionSort(arr,BUFFER);
    InitArrWorstCase(arr, BUFFER);
    PrintSortTime(&SelectionSort,arr,BUFFER,"SelectionSort");



	printf ("\n\nesting of InsertionSort function in case of random numbers:\n");
	RandInsert(arr,BUFFER);
	InsertionSort(arr,BUFFER);
	TEST(1, IsSorted(arr,BUFFER));

	RandInsert(arr,BUFFER);
	PrintSortTime(&InsertionSort,arr,BUFFER,"InsertionSort");

    printf ("\ntesting of InsertionSort function in worst case:\n");
    RandInsert(arr,BUFFER);
	InsertionSort(arr,BUFFER);
    InitArrWorstCase(arr, BUFFER);
    PrintSortTime(&InsertionSort,arr,BUFFER,"InsertionSort");


	return 0;
}



static void InitArrWorstCase(int arr[], const size_t size)
{
    size_t i = 0;

    for(i = 0; i < size; ++i)
    {
        arr[i] = size - i;
    }
}

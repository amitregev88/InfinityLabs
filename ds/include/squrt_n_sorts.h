/*************************************************************
*OL124 comparison sorts project
*
* squrt_n_sorts_tests.c
* squrt_n_sorts.c
* squrt_n_sorts.h
*
* version 1.1 - last change  - signature of PrintSortTime
******************************************************************/


#ifndef OL124_SqurtNSortts_H
#define OL124_SqurtNSortts_H

#include <stddef.h> /* size_t */


/*************************************************************************************
* --- RandInsert --- insert size int numbers and insert them to given array
**************************************************************************************/
int *RandInsert(int arr[], size_t size);


/*************************************************************************************
* --- IsSorted --- returns 1 if array is sorted, 0 otherwise
**************************************************************************************/
int IsSorted(int arr[], size_t size);


/*************************************************************************************
* --- PrintSortTime --- insert our sort and print its time of action compered to qsort
**************************************************************************************/
void PrintSortTime(int* (*SortFunc)(int arr[], size_t size),int arr[], size_t size, char *str);


/*************************************************************************************
* --- BubbleSort --- sort a given arry using Bubble Sort algorithm
**************************************************************************************/
int *BubbleSort(int arr[], size_t size);

/*************************************************************************************
* --- SelectionSort --- sort a given arry using Selection Sort algorithm
**************************************************************************************/
int *SelectionSort(int arr[], size_t size);

/*************************************************************************************
* --- InsertionSort --- sort a given arry using Insertion Sort algorithm
**************************************************************************************/
int *InsertionSort(int arr[], size_t size);



#endif /* OL124_PriorityQueue_H */

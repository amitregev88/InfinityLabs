/*************************************************************
*OL124 comparison sorts project
*
* squrt_n_sorts_tests.c
* squrt_n_sorts.c
*
* linear_sorts.c
* linear_sorts_tests.c
*
*
* sorts.h
*
* version 1.4 - last change  - change MergeSort, QuickSort, CompareQuickSort
******************************************************************/


#ifndef OL124_Sorts_H
#define OL124_Sorts_H

#include <stddef.h> /* size_t */


/*************************************************************************************
* --- RandInsert --- insert size int numbers and insert them to given array
**************************************************************************************/
void RandInsert(int arr[], size_t size);

/*************************************************************************************
* --- IsSorted --- returns 1 if array is sorted, 0 otherwise
**************************************************************************************/
int IsSorted(int arr[], size_t size);

/*************************************************************************************
* --- PrintSortTime --- insert our sort and print its time of action compered to qsort
						(for BubbleSort, SelectionSort, SelectionSort)
**************************************************************************************/
void PrintSortTime(void (*SortFunc)(int arr[], size_t size),int arr[], size_t size, char *str);

/*************************************************************************************
* --- BubbleSort --- sort a given arry using Bubble Sort algorithm
**************************************************************************************/
void BubbleSort(int arr[], size_t size);

/*************************************************************************************
* --- SelectionSort --- sort a given arry using Selection Sort algorithm
**************************************************************************************/
void SelectionSort(int arr[], size_t size);

/*************************************************************************************
* --- InsertionSort --- sort a given arry using Insertion Sort algorithm
**************************************************************************************/
void InsertionSort(int arr[], size_t size);

/*************************************************************************************
* --- CoutingSort --- sort a given arry using Couting Sort Sort algorithm
**************************************************************************************/
void CoutingSort(int arr[], int output [], size_t size);

/*************************************************************************************
* --- RadixSort --- sort a given arry using Radix Sort algorithm
**************************************************************************************/
void RadixSort(int arr[], int output[], size_t size, unsigned char num_of_bits);

/*************************************************************************************
* --- MergeSort --- sort a given arry using Merge Sort  algorithm
**************************************************************************************/
int MergeSort(int *arr_to_sort, size_t num_elements);

/*************************************************************************************
* --- QuickSort --- sort a given arry using Quick Sort  algorithm
**************************************************************************************/
void QuickSort(void *base, size_t nmeb, size_t size, int (*compar)(const void *, const void *));

/*************************************************************************************
* --- CompareQuickSort --- print the time that take for QuickSort and for qsort
*                          to exacute.
**************************************************************************************/
void CompareQuickSort(void *base, size_t nmeb, size_t size, int (*compar)(const void *, const void * ));


#endif /* OL124_Sorts_H */

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
* comparison_and_linear_sorts.h
*
* version 1.3 - last change  - change parameter in  RadixSort function.
******************************************************************/


#ifndef OL124_Comparison_And_Linear_Sorts_H
#define OL124_Comparison_And_Linear_Sorts_H

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





#endif /* OL124_Comparison_And_Linear_Sorts_H */

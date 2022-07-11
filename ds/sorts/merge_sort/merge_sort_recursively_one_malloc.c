/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 07/7/22 
* OL124 Merge Sort Recursively.
*******************************************************************/

#include<stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include "sorts.h" 

static void MergeSortRec(int *arr, size_t size, int *marge_arr);
static void MargeArr(int arr1[], int size_arr1, int arr2[], int size_arr2, int *marge_arr);


    
int MergeSort(int *arr_to_sort, size_t num_elements)
{
    int *tmp_arr = malloc(sizeof(int) * num_elements);
    if (!tmp_arr)
    {
        return 1;
    }

    MergeSortRec(arr_to_sort, num_elements, tmp_arr);

    free(tmp_arr);

    return 0;
}

static void MergeSortRec(int *arr, size_t size, int *marge_arr)
{
    size_t left = size / 2 , right = size - left;

    if(size < 2)
    {
        return;
    }

    MergeSortRec(arr, left, marge_arr);
    MergeSortRec(arr+left, right, marge_arr);

    MargeArr(arr, left, arr + left, right, marge_arr);

    memcpy(arr,marge_arr, sizeof(int) * size);
}

static void MargeArr(int arr1[], int size_arr1, int arr2[], int size_arr2, int *marge_arr)
{

    int lindex = 0, rindex = 0 , mergeindex = 0;

    while (lindex < size_arr1 && rindex <size_arr2)
    {
        if(arr1[lindex] <= arr2[rindex])
        {
            marge_arr[mergeindex] = arr1[lindex];
            ++lindex;
        }

        else
        {
            marge_arr[mergeindex] = arr2[rindex];
            ++rindex;
        }
        ++mergeindex;
    }

    while(lindex < size_arr1)
    {
        marge_arr[mergeindex] = arr1[lindex];
        ++lindex;
        ++mergeindex;
    }

    while(rindex < size_arr2)
    {
        marge_arr[mergeindex] = arr2[rindex];
        ++rindex;
        ++mergeindex;
    }       
}

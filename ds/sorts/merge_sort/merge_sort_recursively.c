/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 07/7/22 
* OL124 Merge Sort Recursively.
*******************************************************************/

#include<stdio.h>   /*printf*/
#include<stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include "sorts.h" 


static void MargeArr(int arr1[], size_t size_arr1, int arr2[], size_t size_arr2);
    
int MergeSort(int *arr_to_sort, size_t num_elements)
{
    size_t left = num_elements / 2 , right = num_elements - left;

    if(num_elements < 2)
    {
        return 1;
    }

    MergeSort(arr_to_sort, left);
    MergeSort(arr_to_sort+left, right);

    MargeArr(arr_to_sort, left, arr_to_sort + left, right);

    return 0;
}

static void MargeArr(int arr1[], size_t size_arr1, int arr2[], size_t size_arr2)
{
    size_t lindex = 0, rindex = 0 , mergeindex = 0;

    int *marge_arr = malloc(sizeof(int) * (size_arr1+size_arr2));
    if (!marge_arr)
    {
        return;
    }

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

    memcpy(arr1,marge_arr, sizeof(int) * (size_arr1+size_arr2));

    free(marge_arr);      
}

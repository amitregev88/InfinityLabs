/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 06/7/22 
* OL124 Binary Search iterative and recursively.
*******************************************************************/

int *BinarySearch(int *sort_arr, size_t size, int to_find)
{
    int left_bound = 0;
    int right_bound = size - 1;
    int mid_index_arr = 0;


    while (left_bound <= right_bound)
    {
        mid_index_arr = (left_bound + right_bound) / 2;

        if (sort_arr[mid_index_arr] > to_find)
        {
            right_bound = mid_index_arr - 1;
        }

        else if (sort_arr[mid_index_arr] < to_find)
        {
            left_bound = mid_index_arr + 1;
        }

        else
        {
            return sort_arr[mid_index_arr];
        }
    }
    return NULL;
}   


int *BinarySearchRec(int *sort_arr, size_t size, int to_find)


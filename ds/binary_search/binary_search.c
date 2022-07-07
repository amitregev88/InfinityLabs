/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 06/7/22 
* OL124 Binary Search iterative and recursively.
*******************************************************************/

#include<stdio.h>

#define ARR_SIZE 20

int BinarySearch(int *sort_arr, int size, int to_find)
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
            return mid_index_arr;
        }
    }
    return -1;
}   


int BinarySearchRec(int *sort_arr, int to_find, int left , int right)
{
    int middle = 0;
    
    if(left <= right)
    {
        middle = (left+right)/2;
    

      if((sort_arr[middle] == to_find))
      { 
        return middle;
      }
    
      else if (sort_arr[middle] < to_find)
      {
        return BinarySearchRec(sort_arr,to_find,middle + 1, right);
      }

      else
      {
        return BinarySearchRec(sort_arr,to_find,left, middle - 1);
      }
    }

  return -1;
}

void PrintRes(int res)
{
  if(res == -1)
  {
    printf("not found\n");
  }

  else
  {
    printf("founded in index : %d" , res);
  }

}


int main()
{
    
    int arr[20]={0};

    int i = 0, find_res = 0, left = 0, right = ARR_SIZE - 1;

    for(i = 0; i < ARR_SIZE; ++ i)
    {
      arr[i] = i+1;
    }

    printf("\nThe sort arr is:\n");
  
    for(i = 0; i < ARR_SIZE; ++ i)
    {
      printf("%d ", arr[i]);
    }

    printf("\n\nSearcing 6 by BinarySearch function:\n");

    find_res = BinarySearch(arr,ARR_SIZE,6);

    PrintRes(find_res);

    printf("\n\nSearcing 21 by BinarySearch function:\n");

    find_res = BinarySearch(arr,ARR_SIZE,21);

    PrintRes(find_res);

    printf("\n\nSearcing 15 by BinarySearchRec function:\n");

    find_res = BinarySearchRec(arr,15,left,right);

    PrintRes(find_res);

    printf("\n\nSearcing 29 by BinarySearch function:\n");

    find_res = BinarySearchRec(arr,29,left,right);

    PrintRes(find_res);

  return 0;
}

#include <stdio.h>

typedef struct
{
	size_t index1;
	size_t index2;
	int sum;
}subarray_ty;

subarray_ty MaxSumSubArray(const int arr[], const size_t size);


int main ()
{
	subarray_ty s = {0, 0, 0};
	int arr[] = {-2, 1, -3, 4, -1, 2, 3, -5, 4};
	
	s = MaxSumSubArray(arr, 9);
	printf ("The max sum is: %d from index %lu to index %lu \n", s.sum, s.index1, s.index2);
	
	return (0);
}


subarray_ty MaxSumSubArray(const int arr[], const size_t size)
{
	
	size_t i = 0;
	subarray_ty currsum = {0,0,0};
	subarray_ty max_sum = {0,0,0};
	
	for(; i < size; ++i)
	{
		/*Adding current element to currsum.max_sum*/
		currsum.sum = currsum.sum + arr[i];
		
/*If current sum becomes negative, Initialize current sum to 0 and set the index of current sum to next element*/
		
		   if(currsum.sum < 0)
            {
                currsum.sum = 0;
                currsum.index1 = i + 1;
            }
			
			else if (currsum.sum > max_sum.sum)
            {
                max_sum.sum = currsum.sum;
                max_sum.index1 = currsum.index1;
                max_sum.index2 = i;
            }
	}
	
	return max_sum;
}

		
		
		









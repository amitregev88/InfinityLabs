#include <stdio.h>

void copyArr(int arr1[], int arr2[], int size);



int main()
{
	int i = 0;
	int arr_size = 8;
	int array[] = {1,2,3,4,5,6,7,8};
	int new_arr[8];
	
	copyArr(array, new_arr, arr_size);
	
	printf("The copied array is:\n");
	
	for (i = 0; i < arr_size; i++)
	{
		printf("%d ", new_arr[i]);
	}
	printf("\n");
	
	return 0;
}

void copyArr(int arr1[], int arr2[], int size)
{
	int i;
	
	for (i = 0; i < size; i++)
	{
		arr2[i] = arr1[i];
	}
}

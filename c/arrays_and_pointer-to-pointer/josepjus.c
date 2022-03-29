#include <stdio.h>
#include <stdlib.h>

/*int *update_arr(int *arr, size_t len);*/
void josephus(int *arr, size_t n, size_t k);

int main()
{
	size_t n = 143;  /* number of soliders*/
	size_t k = 3; /*solider No. that will be killed first*/ 
	size_t i = 0;
	/*
	printf("Enter the number of soldiers (mimimun 2 soldiers)\n");
	scanf("%lu", &n);
	printf("choose a soldier No. to die first\n");
	scanf("%lu", &k);
	*/
	
	int *arr = (int*)malloc(n*sizeof(int));

	
	if(arr == NULL)
	{
		 printf("Memory error allocation\n");
		 return 1;
	}		 
		 
	for(; i < n; i++) *(arr + i) = i + 1; /* initialize arr from 1 until n */

	josephus(arr, n, k);
	free(arr);
	arr = NULL;
	return 0;
}


void josephus(int *arr, size_t n, size_t k)
{
	
	size_t i = 0;
	size_t j = 0;
	
	while(n!=1)
	{
		i = (i + k - 1)%n; /* this expression calculates the next soldier will die */
		n--;
		if (*(arr + i) != 0)  
		{
			*(arr + i) = 0;  /*value arr[i] = 0 means - solider die */
			for(j = i;j < n; j++) /*update the arr*/
				{
				  arr[j] = arr[j + 1];
				}
			arr[n] = (int) NULL;
		}
	}
	
	printf("Soldier No. %d survived\n", *arr);

}


#include <stdio.h>
#include <stdlib.h>

/*int *update_arr(int *arr, size_t len);*/
void josephus(int *arr, size_t n, size_t k);

int main()
{
	size_t n = 7;
	size_t k = 3;
	size_t i = 0;
	
	/*printf("Enter the number of soldiers (mimimun 2 soldiers)\n");*/
	/*scanf("%lu", &n);*/
	/*printf("choose a number of soldier to die first\n");*/
	/*scanf("%lu", &k);*/
	
	int *arr=(int*)malloc(n*sizeof(int));
/*	k= random (1,n)*/

	
	if(arr == NULL)
	{
		 printf("memory error");
		 return 1;
	}		 
		 
	for(; i < n; i++) *(arr + i) = i + 1;

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
		i = (i + k - 1)%n;
		n--;
		if (*(arr + i) != 0)
		{
			*(arr + i) = 0; 
			for(j = i;j < n; j++)
				{
				  arr[j] = arr[j + 1];
				}
			arr[n] = (int) NULL;
		}
	}
	
	printf("Soldier No. %d survived in index %d\n", *arr, *arr - 1);
	
	/*return arr*/;
}

/*
int *update_arr(int *arr, size_t len)
{
	size_t i=0;
	int *ptr = arr;	
	int *new = (int*)realloc(arr,len);
		
	for( ; i<len; i++)
	{	
		if ( *(ptr +i) != 0 )
			*(new+i) = *(ptr+i);
	}
	
	free(ptr);		

	return new;

}
*/

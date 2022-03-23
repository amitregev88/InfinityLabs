#include <stdio.h>
#include <stdlib.h>

int *update_arr(int *arr, size_t len);
void josephus(int *arr, size_t n, size_t k);

int main()
{
	size_t n = 7;
	size_t k = 3;
	size_t i=0;

/*	scanf("num" &n)*/
	int *arr=(int*)malloc(n*sizeof(int));
/*	k= random (1,n)*/

	
	if(arr == NULL)
	{
		 printf("memory eror");
		 return 1;
	}		 
		 
	for(; i < n; i++) *(arr+i) = i+1;

	josephus(arr, n, k);

	return 0;
}


void josephus(int *arr, size_t n, size_t k)
{
	size_t i = 0;
	
	while(n!=1)
	{
		i = (i + k-1)%n;
		if (*(arr +i) != 0) *(arr+i) = 0; 
		n--;
		arr = update_arr(arr, n);
	}
	
	printf("winer %d", *arr);
	
	/*return arr*/;
}


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

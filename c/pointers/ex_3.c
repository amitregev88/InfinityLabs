#include <stdio.h>
#include <stdlib.h>

int main()
{
	static int s_i = 7;
	int i = 7;
	int *ptr = &i;
	int *ptr2 = (int *)malloc(sizeof(int));
	int *ptr3 = NULL;
	
	if(ptr)
	{
		int **ptr3 = &ptr;
	}
	
	
	
	printf("Address of s_i: %p\n", (void*)&s_i);
	printf("Address of i: %p\n", (void*)&i);
	printf("Address of *ptr: %p\n", (void*)ptr);
	printf("Address of *ptr2: %p\n", (void*)ptr2);
	printf("Address of *ptr3: %ls\n", (void*)ptr3);
	
	free(ptr2);
	ptr2 = NULL; 
	return 0;
}

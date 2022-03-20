#include <stdio.h>
#include <stdlib.h>

int main()
{
	static int s_i = 7;
	int i = 7;
	int *ptr  = &i;
	int *ptr2 = (int *)malloc(sizeof(int));

	if (ptr)
	{
        int **ptr3 = &ptr;
        printf("address of ptr3 is: %p\n", ptr3);
	}



	printf("address of s_i is: %p\n", &s_i);
	printf("address of i is: %p\n", &i);
	printf("address of ptr is: %p\n", ptr);
	printf("address of ptr2 is: %p\n", ptr2);
	//printf("address of ptr3 is: %p\n", (ptr3));
	return 0;
}


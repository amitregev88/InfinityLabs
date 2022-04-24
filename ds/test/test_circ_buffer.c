#include <stdio.h>
#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")


int test_circular_buffer()
{
	circ_buffer_ty ptr = NULL;	

	BufferCreate(0) /* checking in case size is 0*/
	
	if (NULL != ptr)
	{
		printf("test BufferCreate in case size is 0\n");
			
	}
	else
	{
		printf("test of BufferCreate succeeded in case size is 0\n");	
	}
	
	BufferCreate(10) /* checking in case size is 0*/
	if (NULL != ptr)
	{
		printf("test of BufferCreate succeeded in case size is greater than 0\n");	
	}
	else 
	{
		printf("test of BufferCreate failed in case size is greater than 0\n");		
	}
	
}
	
	



}


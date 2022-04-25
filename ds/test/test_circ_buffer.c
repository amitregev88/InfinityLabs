#include <stdio.h>
#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")


void test_circular_buffer()
{
	circ_buffer_ty ptr = NULL;	

	BufferCreate(0) /* checking in case size is 0*/
	
	if (NULL != ptr)
	{
		printf("checking test BufferCreate in case size is 0\n");
		IF_SUCCESS(1);
			
	}
	else
	{
		printf("checking test BufferCreate in case size is 0\n");
		IF_SUCCESS(0);
	}
	
	BufferCreate(10) /* checking in case size is 0*/
	if (NULL != ptr)
	{
		printf("checking test of BufferCreate in case size is greater than 0\n");
		IF_SUCCESS(1);	
	}
	else 
	{
		printf(" checking test of BufferCreate in case size is greater than 0\n");
		IF_SUCCESS(0);				
	}
	
	
	/* TODO execute destroy*/
	
	BufferIsEmpty
	
	
	if (BufferIsEmpty(ptr)) /* test of IsEmpty function*/
	{
		printf("checking test of IsEmpty function in case buffer is empty\n");
		IF_SUCCESS(1);
	}
	else
	{
		printf("checking test of IsEmpty function in case buffer is empty\n");
		IF_SUCCESS(0);
	} 
	

	
	
	
	
size_t BufferWrite(circ_buffer_ty *buffer, const void *data, size_t count)
	
}
	
	



}


/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 04.24.22
* OL124 Circular Buffer Project
*************************************************************************************/


#include <stdio.h>
#include "../include/circ_buffer.h" 

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


void test_circular_buffer()
{
	circ_buffer_ty buffer = NULL;	

	BufferCreate(0); /*checking in case size is 0*/
	
	if (NULL != buffer)
	{
		printf("testing BufferCreate in case size is 0\n");
		IF_SUCCESS(1);
			
	}
	else
	{
		printf("testing BufferCreate in case size is 0\n");
		IF_SUCCESS(0);
	}
	
	BufferCreate(10) /* checking in case size is 0*/
	if (NULL != buffer)
	{
		printf("testing of BufferCreate in case size is greater than 0\n");
		IF_SUCCESS(1);	
	}
	else 
	{
		printf("testing of BufferCreate in case size is greater than 0\n");
		IF_SUCCESS(0);				
	}
	
	printf("the siz")BufferSize
	TEST(10,BufferSize(buffer));
	
	
	
	
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
	

	
	
	
	



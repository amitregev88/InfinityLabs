/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 04.24.22
* OL124 Circular Buffer Project
*************************************************************************************/


#include <stdio.h>	/*printf*/
#include <string.h> /* strlen*/
#include "circ_buffer.h" 

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


void test_circular_buffer(void)
{
	circ_buffer_ty *buffer = NULL;
	static char string[20] = "Hello World";	
	static char string_from_read_func[50];	
	static char long_string[] ="this is a long string for testing the BufferWrite function in case the data is greater than buffer";	
	

	BufferCreate(0); /*checking in case size is 0*/

	if (NULL == buffer)
	{
		printf("Testing of function BufferCreate in case size is 0\n");
		IF_SUCCESS(1);
			
	}
	else
	{
		printf("Testing of function BufferCreate in case size is 0\n");
		IF_SUCCESS(0);
	}
	
	buffer = BufferCreate(20); /* checking in case size is greater then 0*/
	if (NULL != buffer)
	{
		printf("\nTesting of function BufferCreate in case size is greater than 0\n");
		IF_SUCCESS(1);	
	}
	else 
	{
		printf("Testing of function BufferCreate in case size is greater than 0\n");
		IF_SUCCESS(0);				
	}
	
	printf("\nTesting of BufferSize function:\n");
	
	TEST(20,BufferSize(buffer));
	
	printf("\nTesting of BufferIsEmpty function in case buffer is empty:\n");
	TEST(1,BufferIsEmpty(buffer));
	
	
	printf("\nTesting of BufferWrite and BufferFreeSpace functions in case buffer is greater than data:\n");
	TEST(BufferWrite(buffer, string, 11),11);
	TEST(9,BufferFreeSpace(buffer));
	
	printf("\nTesting of BufferIsEmpty function in case buffer is not empty:\n");
	TEST(0,BufferIsEmpty(buffer));
	
	printf("\nTesting of BufferRead function:\n");
	TEST(BufferRead(buffer, string_from_read_func, 11),11);
	TEST(11,strlen(string_from_read_func));
	TEST(20,BufferFreeSpace(buffer));
	
	
	printf("\nTesting of BufferWrite and BufferFreeSpace functions in case the data is greater than buffer:\n");
	TEST(20,BufferWrite(buffer, long_string, 21));
	TEST(0,BufferFreeSpace(buffer));
	
	printf("\nTesting of BufferRead function:\n");
	TEST(BufferRead(buffer, string_from_read_func, 20),20);
	TEST(20,BufferFreeSpace(buffer));
	
	BufferDestroy(buffer);
}

	
int main()
{
		
	test_circular_buffer();

	return 0;	
}
	
	

	
	
	
	



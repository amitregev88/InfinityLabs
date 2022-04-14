#include <stdio.h>
#include "../include/dynamic_vector.h"


typedef struct stack stack_ty;


void TestStackCreate(void);
void TestStackDestroy(void);
void Test_StackPush_StackSize_StackPeek(void)
void TestStackPop(void);





dynamic_vector_ty *Vector
/************************TestStackCreateAndDestroy**********************/


void TestStackCreateAndDestroy(void)
{

	dynamic_vector_ty *ptr = NULL;

/*create a dynamic vector*/

	ptr = VectorCreate(10, 11); /*checking in case the size of element greater than capacity */ 
	
	if (ptr == NULL)
	{
		printf("Test create stack succeed - in case size of elements greater than capacity\n");
	}
	else
	{
		printf("Test create failed - in case size of elements greater than capacity\n");
		StackDestroy(ptr);	/*destroy a stack - test*/
	
		if (ptr == NULL)
		{
			printf("Test destroy stack succeed in case the size of elements greater than capacity\n");
		}
		else
		{
			printf("Test destroy stack failed in case  the size of elements greater than capacity \n");
		}
	}
	
	
/*create a stack again*/
	ptr = NULL;
	
	ptr = StackCreate(15, 2); /*checking in case the capacity value  greater than size of elements */ 
	if (ptr != NULL)
	{
		printf("Test create stack succeed - in case the capacity greater than size of elements\n");
		StackDestroy(ptr);	/*destroy a stack - test*/
		if (ptr == NULL)
		{
			printf("Test destroy stack succeed - in case the capacity greater than size of elements\n");
		}
		else
		{
			printf("Test destroy stack failed - in case the capacity greater than size of elements\n");
		}
	}
	else
	{
		printf("Test create stack failed - in case the capacity greater than size of elements\n");
	}

}

void Test_StackPush_StackSize_StackPeek(void)
{
	
	char  a = 'a';

	stack_ty *ptr = StackCreate(1,1); 
	
	StackPush(ptr, &a)
		
	if (StackSize(ptr)==1)
	{
		printf("succeed stack push\n");
		
	}
	else 
	{
	printf("failed stack push\n");
	
	
	}
	
	
	if (*(char *)(StackPeek(ptr) == a)
	{
		printf("succed stackpeek\n");
	}
	
	else 
	{
	
		printf("failed stackpeek\n");
	}
	
	
	SrackPop(ptr)
	
	if (size == 0)
	
	{
		printf("succed StackPop\n");
	}
	
	else 
	{
	
		printf("failed stackPop");
	}
}








}

	/*
struct stack
{
    size_t size;
    void *stack;
    size_t capacity;
    size_t size_of_element;
};
*/




#include <stdio.h>
#include "../include/stack.h"

void TestStackCreateAndDestroy(void);
void TestStack(void);


int main()
{
	TestStackCreateAndDestroy();
	TestStack();

	return 0;
}



/************************TestStackCreateAndDestroy**********************/
void TestStackCreateAndDestroy(void)
{
	stack_ty *ptr = NULL;	/*create a stack struct*/

/*create a stack*/

	ptr = StackCreate(2, 8); /*checking in case the size of element greater than capacity */ 
	
	if (NULL != ptr)
	{
		printf("Test of create stack succeed - in case size of elements greater than capacity\n");
	}
	else
	{
		printf("Test of create stack failed - in case size of elements greater than capacity\n");
		StackDestroy(ptr);	/*destroy a stack */		
	}
	
	
/*create a stack again*/
	ptr = NULL;
	
	ptr = StackCreate(15, 4); /*checking in case the capacity value  greater than size of element */ 
	if (ptr != NULL)
	{
		printf("Test of create stack succeed - in case the capacity greater than size of elements\n");
		StackDestroy(ptr);	/*destroy a stack - test*/
		
	}
	else
	{
		printf("Test of create stack failed - in case the capacity greater than size of elements\n");
	}

}

void TestStack(void)
{
	
	char  a = 'a';
	char  b = 'b';
	const void *tmp = NULL;

	stack_ty *ptr = StackCreate(3,1);
	
	if (StackIsEmpty(ptr)) /* test of IsEmpty function*/
	{
		printf("test of IsEmpty function succeed\n");
	}
	else
	{
		printf("test of IsEmpty function failed\n");
	} 
	
	printf("before the first push, size is: %ld\n", StackSize(ptr)); /*test of size function*/
	
	
	StackPush(ptr, &a);
	
	
	if (StackSize(ptr) == 1)
	{
		printf("after the first push, size is: %ld - stack push test and stack size test succeed\n", StackSize(ptr));
		
	}
	else 
	{
	printf("stack push test and stack size test failed \n");
	
	}
	
	StackPush(ptr, &b);
	
	tmp = StackPeek(ptr);
	
	if (*(char *)tmp == 'b')
	{
		printf("StackPeek test succeed\n");
	}
	
	else 
	{
		printf("StackPeek test failed\n");
	}
	
	
	if(StackCapacity(ptr) == 3)
	{
		printf("The capacity of the stack is %ld - StackCapacity test succeed\n",StackCapacity(ptr));
	}
	
	else
	{
		printf("StackCapacity test failed\n");
	}
	
	
	StackPop(ptr);
	StackPop(ptr);
	
	if (StackSize(ptr) == 0)	
	{
		printf("StackPop test succeed\n");
	}
	
	else 
	{
	
		printf("StackPop test failed\n");
	}
}


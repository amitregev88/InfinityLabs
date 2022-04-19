#include <stdio.h>
#include "../include/dynamic_vector.h"

void TestDynamicVectorCreateAndDestroy(void);
void TestVector(void);

int main()
{
	TestDynamicVectorCreateAndDestroy();
	TestVector();

	return 0;
}

/************************TestDynamicVectorCreateAndDestroy**********************/

void TestDynamicVectorCreateAndDestroy(void)
{

	dynamic_vector_ty *ptr = NULL;	 /*create a dynamic vector*/



	ptr = VectorCreate(10, 11); /*checking in case the size of element greater than capacity */ 
	
	if (ptr != NULL)
	{
		printf("Test of VectorCreate succeed - in case size of elements greater than capacity\n");
	}
	else
	{
		printf("Test of VectorCreate failed - in case size of elements greater than capacity\n");
		VectorDestroy(ptr);	
	
	}
	
	
		
	ptr = NULL;
	
	ptr = VectorCreate(15, 2); /*checking in case the capacity value  greater than size of elements */ 
	if (ptr != NULL)
	{
		printf("Test of VectorCreate succeed - in case the capacity greater than size of elements\n");
		VectorDestroy(ptr);	
	}
	else
	{
		printf("Test of VectorCreate failed - in case the capacity greater than size of elements\n");
	}

}



void TestVector(void)
{
	
	char a = 'a';
	char b = 'b'; 
	char c = 'c';
	void *tmp = NULL;
	
	
	dynamic_vector_ty *ptr = VectorCreate(2,1); 
	
	if (VectorIsEmpty(ptr)) /* test of IsEmpty function*/
	{
		printf("test of IsEmpty function succeed\n");
	}
	else
	{
		printf("test of IsEmpty function failed\n");
	}
	
	printf("before the first push, size is: %ld\n", VectorSize(ptr)); /*test of size function*/
	
	VectorPushBack(ptr, &a);
		
	if (VectorSize(ptr)==1)
	{
		printf("after the first push, size is: %ld\n", VectorSize(ptr)); /*test of size function*/
		printf("VectorPushBack and VectorSize succeed\n");

		VectorPushBack(ptr, &b); 
	
		if (VectorSize(ptr)==2)
		{
			printf("after the second push, size is: %ld\n", VectorSize(ptr)); /*test size function*/
			printf("VectorPushBack and VectorSize succeed\n");
		
		}
	}
	else 
	{
		printf("VectorPushBack and VectorSize failed\n");
	}
		
	
	
	
	/*test of VectorCapacity function  and realloc of VectorPushBack*/
	
	VectorPushBack(ptr, &c); 
	
	printf("before realloc capacity is 2. after thrid push -realloc . after realloc, the capacity is %ld\n",VectorCapacity(ptr));
	
	
	/* test of VectorGetAccessToElement*/
	
	tmp = VectorGetAccessToElement(ptr, 10); /* test with invalid index*/
	
	if (tmp == NULL)
	{
		printf("test of VectorGetAccessToElement succeed in case invalid index\n");
	} 
	
	else 
	{
		printf("test of VectorGetAccessToElement failed in case invalid index\n");
	}
	
	tmp = VectorGetAccessToElement(ptr, 2); /* test with valid index*/
	
	if (*(char *)tmp == 'c')
	{
		printf("the value in index 2 is %c -vectorGetAccessToElement succeed in case valid index\n",(*(char *)tmp));
	} 
	
	else 
	{
		printf("test of VectorGetAccessToElement faild in case invalid index\n");
	}
	
	
	/*test of VectorPopBack function*/
	
	VectorPopBack(ptr);
	VectorPopBack(ptr);
		 
	/*VectorPopBack(ptr); */
	
	if ((VectorSize(ptr) == 1) && (VectorCapacity(ptr) == 2))
	{
		printf("after  VectorPopBack 2 times. the size is %ld  and capacity is %ld - VectorPopBack and  VectorReserve succeeded\n", VectorSize(ptr), VectorCapacity(ptr));
	}
	else
	{
		printf("test of VectorPopBack function faild\n");
	}
		
	

}
	
	









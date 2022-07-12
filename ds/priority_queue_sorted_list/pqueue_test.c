/*************************************************************************************
* 
* 
* OL124 PQUEUE Test
*   
*************************************************************************************/


#include <stdio.h> /* printf */
#include "pqueue.h"



#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)



int IntCmp(const void *a, const void *b);

int IsIntMatch(const void *a, const void *b);

void PQUEUE_TEST(void);

int main(void)
{
	PQUEUE_TEST();

	return 0;
}




int IntCmp(const void *a, const void *b)
{
	return (*(int *)a - *(int *)b);
}

int IsIntMatch(const void *a, const void *b)
{
	return (*(int *)a == *(int *)b);
}



void PQUEUE_TEST(void)
{	
	int num1 = 1, num2 = 2, num3 = 3, num4 = 4;
	
	pqueue_ty *pqueue = NULL;
	

	printf("Testing of PQCreate() function:\n");
	pqueue = PQCreate(IntCmp);
	
	
	if (pqueue)
	{
		printf("Testing of PQCreate() function succeeded\n");
	} 
	
	else
	{
		printf("Testing of  PQCreate() function failed\n");
	}
	
	printf("\nTesting of PQIsEmpty() function in case the list is empty:\n");
	
	TEST(PQIsEmpty(pqueue), 1);
	
	printf("\nTesting of PQSize() function in case the list is empty:\n");
	
	TEST(PQSize(pqueue), 0);
	
	printf ("\nTesting of PQEnQueue function\n");
	
	TEST(PQEnQueue(pqueue, &num4), 0);
	TEST(PQEnQueue(pqueue, &num1), 0);
	TEST(PQEnQueue(pqueue, &num3), 0);
	TEST(PQEnQueue(pqueue, &num2), 0);
	
	printf ("\nTesting of PQSize() function in case the list is not empty:\n");
	TEST(PQSize(pqueue), 4); 
	
	printf ("\nTesting of PQPeek() function\n");
	TEST(*(int *)PQPeek(pqueue), num4); 
	
	printf ("\nTesting of PQDeQueue() function\n");
	TEST(PQDeQueue(pqueue), &num1);
	TEST(PQSize(pqueue), 3); 
	
	printf("\nTesting of PQIsEmpty() function in case the list is not empty:\n");
	TEST(PQIsEmpty(pqueue), 0);
	
	
	printf("\nTesting of PQErase() function :\n");

	TEST(*(int *)PQErase(pqueue, IsIntMatch, &num2), num2);

	TEST(PQSize(pqueue), 2); 

		
	PQDestroy(pqueue);	
	
}









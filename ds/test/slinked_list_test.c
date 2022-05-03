
#include <stdio.h> /* printf */
#include "slinked_list.h"


#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)




void TestA(void);
void TestB(void);
int IsMatch(const void *data, const void *param);	/* for find function*/
int IntAddNum(void *data_from_list, void *param);	/* for foreach function*/

/*******************************************************************************
* TestA - checking the following functions: 

* SlistCreate(),SListIsEmpty(),SListSize(),SListPushFront(),SListPushBack(),
* SListPopFront(), SListPopBack  SListBegin() ,SListGetData(), SListSetData(),
* SListGetNext(), SListFind(), SListDestroy() .
* *******************************************************************************/

int main(void)
{
	TestA();
	
	TestB();

	return 0;
}

int IsMatch(const void *data, const void *param) 
{
	return (*(char *)data == *(char *)param);
}

int IntAddNum(void *data_from_list, void *param) 
{
	if (!*(int *)param)
	{
		return 0;
	}
	
	*(int *)data_from_list += *(int *)param;
	
	return 1;
}


void TestA(void)
{
	slist_ty *list = NULL;
	
	slist_iter_ty iter = {NULL};
		
	char a = a, b = b, c = c;
	
	int num1 = 1;
	
	float num2 = 2.5;
	
	printf("Testing of SListCreate() function:\n");
	
	list = SListCreate();
	
	TEST(list, !NULL);
	
	printf("\nTesting of SListIsEmpty() function in case list is empty:\n");
	
	TEST(SListIsEmpty(list), 1);
	
	printf("\nTesting of SListSize() function in case list is empty:\n");
	
	TEST(SListSize(list), 0);
	
	printf("\nTesting of SListPushFront() function:\n");
	
	SListPushFront(list, &c);
	SListPushFront(list, &b);
	SListPushFront(list, &a);
	
	
	printf("\nTesting of SListSize() function in case list is not empty:\n");
	
	TEST(SListSize(list), 3);
	
	printf("\nTesting of SListIsEmpty() function in case list is not empty:\n");
	
	TEST(SListIsEmpty(list), 0);
	
	
	printf ("\nTesting of SListGetData(), SListBegin() and SListGetNext() function:\n");
	
	iter = SListBegin(list);
	
	TEST(*(char *)SListGetData(iter), a);
	
	iter = SListGetNext(iter);
	
	TEST(*(char *)SListGetData(iter), b);
	
	iter = SListGetNext(iter);
	
	TEST(*(char *)SListGetData(iter), c);
	
	
	
	printf ("\nTesting of SListPushBack() and SListGetData() function:\n");
	
	iter = SListPushBack(list, &num1);
	
	TEST(*(int *)SListGetData(iter), num1);
	
	
	printf ("\nTesting of SListSetData() and SListGetData() function:\n");
	
	SListSetData(SListBegin(list), &num2);
	
	TEST(*(float *)SListGetData(SListBegin(list)), num2);
	
	
	printf ("\nTesting of SListPopBack() function:\n");
	
	TEST(*(int *)SListPopBack(list), num1);
	
	printf ("\nTesting of SListSize function after SListPopBack():\n");
	
	TEST(SListSize(list), 3);
	
	
	printf ("\nTesting of SListFind() function:\n");
	
	iter = SListFind(SListBegin(list), SListEnd(list), IsMatch, &b);
	TEST(*(char *)SListGetData(iter), b);
	
	
	printf ("\nTesting of SListPopFront() function:\n");
	TEST(*(char *)SListPopFront(list), a);
	TEST(*(char *)SListPopFront(list), b);
	TEST(*(char *)SListPopFront(list), c);
	
	printf ("\nTesting of SListSize function after SListPopFront():\n");
	
	TEST(SListSize(list), 0);
	
	
	printf ("\nTesting of SListPopFront() function in case list is empty:\n");
	
	TEST(SListPopFront(list), NULL);
	
	printf ("\nTesting of SListPopBack() function in case list is empty:\n");
	
	TEST(SListPopBack(list), NULL);
	
	

	SListDestroy(list);	

	
}

/*******************************************************************************
* TestB - checking the following functions: 

* SlistCreate(), SlistInsert(), SlistRemove() SlistEnd(), SlistForEach() SListDestroy().
* *******************************************************************************/


void TestB(void);
{
	slist_ty *list = NULL;
	
	slist_iter_ty iter = {NULL};




	
	
	
	
	
	
	



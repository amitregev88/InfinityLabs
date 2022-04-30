/*************************************************************************************
* Name: Amit Regev 
* Date: 04.26.22
* OL124 Double Linked List test
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include "dlinked_list.h" 

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


void TestDlinkedList(void)
{
	char ch = a;
	char ch1 = b;
	char ch2 = c;
	
	dlist_node_ty *node = NULL;

	printf("Testing of DListCreate() function\n");
	
	dlist_ty *list = DListCreate();	
		
	TEST(list,!NULL);
	
	printf("\nTesting of DListSize() function in case size is 0\n");
	
	TEST(DListSize(list),0);
	
	printf("\nTesting of DListIsEmpty() function in case the linked list is empty\n");

	TEST(DListIsEmpty(list),1);
	
	
	
	printf("\nTesting of DListPushFront() function\n");
	
	TEST(DListPushFront(list, &ch), 1);
	
	
	printf("\nTesting of DListSize() function in case size is greater than 0\n");
	
	TEST(DListSize(list),1);
		
	printf("\nTesting of DListIsEmpty() function in case the linked list is not empty\n");
	TEST(DListIsEmpty(list),0);
	
	printf("\nTesting of DListPushFront() and DListGetDatafunction in case linked list is not empty\n");
		
	TEST(*DListGetData(DListPushFront(list, &ch1), b);
	TEST(DListPushFront(list, &ch1), 1);
	
	printf("\nTesting of DListPushBack()\n");
	TEST(*DListGetData(DListPushBack(list, &ch1), b);
	TEST(DListPushBack(list, &ch), a);

	printf("\nTesting of DListPopBack()\n");

	TEST(*(char *)DListPopBack(list), b);
	TEST(DListSize(list),4);
	
	printf("\nTesting of DListFront()\n");

	TEST(*(char *)DListPopBack(list), b);
	TEST(DListSize(list),3);
	
	printf("\nTesting of DListInsert()\n");
	
	node = DListInsert(node, &ch)
	(*(char *
	TEST(DListSize(list),3);
	
	/*TODO*/
	
	

	
	printf("\nTesting of DListSetData() function\n");
	DListSetData(node, &ch2);
	
	TEST(*(char *)DListSetData(node), ch2);
	DListSetData(node, &ch);
	
	
	
	printf("\nTesting of DListGetNext() function\n");
	node = DListGetNext(node);
	TEST(*(char *)DListGetData(node), ch);
	
	

	
	
}


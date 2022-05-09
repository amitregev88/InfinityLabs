
#include <stdio.h> /* printf */
#include "dlinked_list.h"


#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)




void Test(void);
int IsMatch(const void *data, const void *param);	/* for find function*/
int IntPlusInt(void * data_from_list, void *param);	/* for foreach function*/



int main(void)
{
	Test();
	
	return 0;
}

int IsMatch(const void *data, const void *param) 
{
	return (*(int *)data == *(int *)param);
}

int IntPlusInt(void *ldata, void *param) 
{
	if (!*(int *)param)
	{
		return 0;
	}
	
	*(int *)ldata += *(int *)param;
	
	return 1;
}






void Test(void)
{
	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5, num6 = 6, num7 = 7;
	
	dlist_ty *list = NULL;
	
	dlist_ty *list2 = NULL;
	
	dlist_node_ty *node = NULL;
	
	dlist_node_ty *begin = NULL;
	
	dlist_node_ty *end = NULL;
	
	printf("Testing of DListCreate() function:\n");
	
	list = DListCreate();
	
	if (list)
	{
		printf("Testing of DListCreate() function succeeded\n");
	} 
	
	else
	{
		printf("Testing of DListCreate() function failed\n");
	}
	
	printf("\nTesting of DlistSize() function in case list is empty:\n");
	TEST(DListSize(list), 0);
	
	printf("\nTesting of DlistIsEmpty() function in case list is empty:\n");
	TEST(DListIsEmpty(list), 1);
	
	printf("\nTesting of DlistPushFront() and  DlistGetData function:\n");
	DListPushFront(list, &num3);
	DListPushFront(list, &num2);
	DListPushFront(list, &num1);
	node = DListBegin(list);
	TEST(*(int *)DListGetData(node), 1);
	
	printf("\nTesting of DlistSize() function in case list is not empty:\n");
	TEST(DListSize(list), 3);
	
	printf("\nTesting of DlistIsEmpty() function in case list is not empty:\n");
	TEST(DListIsEmpty(list), 0);
	
	
	printf ("\nTesting of DlistPopBack() DlistBegin() DListGetNext() DListGetData() DListSize() function:\n");
	TEST(*(int *)DListPopBack(list), 3);
	node = DListBegin(list);
	TEST(*(int *)DListGetData(node), num1);
	node = DListGetNext(node);
	TEST(*(int *)DListGetData(node), num2);
	TEST(DListSize(list), 2);
	
	

	printf ("\nTesting of DlistPopFront() function:\n");
	TEST(*(int *)DListPopFront(list), 1);
	TEST(DListSize(list), 1);
	node = DListBegin(list);
	TEST(*(int *)DListGetData(node), num2);
	
	
	printf("\nTesting of DlistPushBack() and  DlistGetData function:\n");
	DListPushBack(list, &num2);
	DListPushBack(list, &num3);
	node = DListGetNext(DListBegin(list));
	TEST(*(int *)DListGetData(node), 2);
	node = DListGetNext(node);
	TEST(*(int *)DListGetData(node), 3);
	
	printf("\nTesting of DlistSize() function :\n");
	TEST(DListSize(list), 3);
	
	printf("\nTesting of DListInsert() DListGetEnd  DlistGetData DListGetPrev()function:\n");
	node = DListEnd(list);
	node = DListInsert(node, &num2);
	TEST(DListSize(list), 4);
	TEST(*(int *)DListGetData(node), num2);
		
	printf("\nTesting of DlistSetData() and  DlistGetData function:\n");
	node = DListEnd(list);
	node = DListGetPrev(node);
	DListSetData(node, &num4);
	TEST(*(int *)DListGetData(node), num4);
	

	printf ("\nTesting of DListGetNext() function:\n");
	node = DListBegin(list);
	TEST(*(int *)DListGetData(node), num2);
	node = DListGetNext(node);
	TEST(*(int *)DListGetData(node), num2);
	node = DListGetNext(node);
	TEST(*(int *)DListGetData(node), num3);
	node = DListGetNext(node);
	TEST(*(int *)DListGetData(node), num4);
	
	
	printf ("\nTesting of DListBegin() function :\n");
	node = DListBegin(list);
	TEST(*(int *)DListGetData(node), num2);
	
	printf ("\nTesting of DListEnd() function :\n");
	node = DListEnd(list);
	node = DListGetPrev(node);
	TEST(*(int *)DListGetData(node), num4);
	
	printf ("\nTesting of DListFind() function:\n");
	begin = DListBegin(list);
	end = DListEnd(list);
	
	node = DListFind(begin, end, IsMatch, &num3);
	TEST(*(int *)DListGetData(node), num3);
	
	printf ("\nTesting of DListForEach() function ?????????????:\n");
	TEST(*(int *)DListGetData(begin), 2);
	
	TEST(DListForEach(begin, end, &IntPlusInt, &num1), 1);
	
	TEST(*(int *)DListGetData(begin), 4);
	

	printf ("\nTesting of DListSplice function :\n");
		
	list2 = DListCreate();
	
	DListPushBack(list2, &num5);
	DListPushBack(list2, &num6);
	DListPushBack(list2, &num7);
	
	DListSplice(DListEnd(list), DListBegin(list2), DListEnd(list2));
	
	
	TEST(DListSize(list), 7);
	TEST(DListIsEmpty(list2), 1);
	
	node = DListEnd(list);
	node = DListGetPrev(node);
	
	TEST(*(int *)DListGetData(node), 7);

	DListDestroy(list);	
	DListDestroy(list2);	

}



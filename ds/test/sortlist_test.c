

#include <stdio.h> /* printf */
#include "sortlist.h"

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


void Test(void);
void TestMerge(void);
int Compare (const void *a, const void *b);
int IsIntMatch(const void *data, const void *param);
int IntPlusInt(void *ldata, const void *param);

int main(void)
{
	Test();
	TestMerge();
	
	return 0;
}


int Compare (const void *a, const void *b)
{

	return (*(int *)a - *(int *)b);

}

int IsIntMatch(const void *data, const void *param)
{
	return (*(int *)data == *(int *)param);
}

int IntPlusInt(void *ldata, const void *param) 
{
	if (ldata == NULL || param == NULL)
	{
		return 1;
	}
	
	*(int *)ldata += *(int *)param;
	
	return 0;
}





void Test(void)
{
	int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5, num6 = 6;
	
	sortlist_ty *slist1 = {NULL};
	
	sortlist_iter_ty iter = {NULL};
	
	sortlist_iter_ty iter2 = {NULL};
	
	
	
	
	
	printf("Testing of SortLCreate() function:\n");
	
	slist1 = SortLCreate(Compare);
	
	if (slist1)
	{
		printf("Testing of SortLCreate() function succeeded\n");
	} 
	
	else
	{
		printf("Testing of  SortLCreate() function failed\n");
	}
	

	
	printf("\nTesting of  SortLIsEmpty() function in case sort list is empty:\n");
	TEST(SortLIsEmpty(slist1), 1);
	
	printf("\nTesting of SortLSize() function in case queue is empty:\n");
	TEST(SortLSize(slist1), 0);
	
	
	
	
	printf("\nTesting of SortLInsert() and SortLGetData() function:\n");
	
	TEST(SortLGetData(SortLInsert(slist1, &num2)), &num2);
	TEST(SortLGetData(SortLInsert(slist1, &num3)), &num3);
	TEST(SortLGetData(SortLInsert(slist1, &num1)), &num1);
	
	
	
		
	printf("\nTesting of SortLBegin(), SortLEnd(), SortLGetNext(), SortLGetPrev() and SortLGetData():\n");
	
	iter = SortLBegin(slist1);
	
	TEST(SortLGetData((SortLBegin(slist1))), &num1);
	
	TEST(SortLGetData((SortLGetNext(iter))), &num2);
	
	TEST(SortLGetData((SortLEnd(slist1))), NULL);
	
	TEST(SortLGetData(SortLGetPrev(SortLEnd(slist1))), &num3);
	

	
	printf("\nTesting of SortLSize() function in case sort list is not empty:\n");
	
	TEST(SortLSize(slist1), 3);
	
	
		
	printf("\nTesting of SortLIsEmpty() function  in case sort list is not empty:\n");
	
	TEST(SortLIsEmpty(slist1), 0);
	

	
	printf("\nTesting of SortLPopBack() function  in case sort list is not empty:\n");
	
	TEST(SortLPopBack(slist1), &num3);
	TEST(SortLSize(slist1), 2);
	
	
	
	
	printf("\nTesting of SortLRemove() function:\n");
	
	SortLRemove(iter); 
	TEST(SortLSize(slist1), 1);
	
	

	printf("\nTesting of SortLPopFront() function  in case sort list is not empty:\n");
	
	
	TEST(SortLPopFront(slist1), &num2);
	TEST(SortLSize(slist1), 0);
	
	
	printf("\nTesting of SortLInsert() and SortLGetData() function:\n");
	
	iter2 = SortLInsert(slist1, &num1);	
	iter = SortLBegin(slist1);
	
	TEST(SortLGetData(iter2),&num1);
	
	printf("\nTesting of SortLIsSameIter() function:\n");
	
	TEST(SortLIsSameIter(iter2, iter), 1);
	
	printf("\nTesting of SortLInsert() and SortLGetData() function:\n");
	
	TEST(SortLGetData(SortLInsert(slist1, &num3)), &num3);
	TEST(SortLGetData(SortLInsert(slist1, &num2)), &num2);
	TEST(SortLGetData(SortLInsert(slist1, &num5)), &num5);
	TEST(SortLGetData(SortLInsert(slist1, &num6)), &num6);
	iter2 = SortLInsert(slist1, &num4);	
	
	printf("\nTesting of Find() function:\n");
	
	iter = SortLFind(slist1, SortLBegin(slist1), SortLEnd(slist1), &num4);
	
	TEST(SortLIsSameIter(iter2, iter), 1);
	

	printf("\nTesting of FindIf() function:\n");
	
	iter = SortLFindIf(SortLBegin(slist1), SortLEnd(slist1), IsIntMatch, &num5);
	TEST(*(int *)SortLGetData(iter), num5);
	
	printf ("\nTesting of SortLForEach()\n");
	TEST(SortLForEach(SortLBegin(slist1), SortLEnd(slist1), IntPlusInt, &num1), 0);
	TEST(*(int *)SortLGetData(SortLBegin(slist1)), 2);


	SortLDestroy(slist1);
	
}

void TestMerge(void)
{
	int num1= 1, num4 = 4, num5 = 5, num7 = 7, num8 = 8, num9 = 9, num10 = 10, num11 = 11, num12 = 12, num15 = 15;
	
	sortlist_ty *slist1 = {NULL};
	
	sortlist_ty *slist2 = {NULL};
	
	sortlist_iter_ty iter = {NULL};
		
	slist1 = SortLCreate(Compare);
	slist2 = SortLCreate(Compare);
	
	
	
	
	
	printf("\nTesting of SortLMerge() function:\n");
	
	printf("\ninsert numbers to list 1:\n");
	
	TEST(SortLGetData(SortLInsert(slist1, &num1)), &num1);
	
	TEST(SortLGetData(SortLInsert(slist1, &num7)), &num7);
	
	TEST(SortLGetData(SortLInsert(slist1, &num8)), &num8);
	
	TEST(SortLGetData(SortLInsert(slist1, &num10)), &num10);
	
	TEST(SortLGetData(SortLInsert(slist1, &num12)), &num12);
	
	
	printf("\ninsert numbers to list 2:\n");
	
	TEST(SortLGetData(SortLInsert(slist2, &num4)), &num4);
	
	TEST(SortLGetData(SortLInsert(slist2, &num5)), &num5);
	
	TEST(SortLGetData(SortLInsert(slist2, &num9)), &num9);
	
	TEST(SortLGetData(SortLInsert(slist2, &num11)), &num11);
	
	TEST(SortLGetData(SortLInsert(slist2, &num15)), &num15);
	
	printf("\nTesting of SortLMerge() function:\n");
	
	printf("\nslist1 should be  1 4 5 7 8 9 10 11 12 15 and slist2 should be empty: \n");
	
	SortLMerge(slist1, slist2);
	
	
	printf("\nTesting of size of slist1: \n");
	TEST(SortLSize(slist1), 10);
	
	
	printf("\nTesting of size of slist2: \n");
	TEST(SortLIsEmpty(slist2), 1);
	
	
	printf("\n After calling of SortLMerge() function, slist1 is: \n");
	
	for (iter = SortLBegin(slist1); !SortLIsSameIter(iter, SortLEnd(slist1)); iter = SortLGetNext(iter))
	{
		printf ("%d ", *(int *)SortLGetData(iter));
	}
	
	printf ("\n");

	

	SortLDestroy(slist1);
	SortLDestroy(slist2);	


}

	

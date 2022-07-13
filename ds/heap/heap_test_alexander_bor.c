/***************************
 * OL124 binary serch project
 * binary_serch
 * binary_serch.c
 * binary_serch_test.c
 * version 1.2
 ***************************/

#include <stddef.h>
#include <stdio.h>
#include <string.h> /* strcpy(), strcmp() */
#include <stdlib.h> /* malloc() */
#include "heap.h"


int IntCmp(const void *data1, const void *data2)
{
	if (*(int *)data1 < *(int *)data2)
	{
		return -1;
	}
	else
	{
		return (*(int *)data1 > *(int *)data2);
	}
	
}
int is_match(const void *data, const void *to_remove)
{
	return (*(int *)data == *(int *)to_remove);
}
#define __MSG_SUCCEED__ printf ("This test SUCCEEDED\n")
#define __MSG_FAILURE__ printf ("This test FAILED\n")
#define __MSG_FUNC_NAME__(a) printf ("-------------- Now Testin ---- a() ----\n")
#define __TEST__(a, b, c) if ((a) b (c)) {__MSG_SUCCEED__;} else {__MSG_FAILURE__;}
#define __TEST_ITER__(a, b) if(SListIsSameIter(a, b)){__MSG_SUCCEED__;}else{__MSG_FAILURE__;}
/* Comparison between two integers, return 1 in success or 0 other */




#define _SIZE 8
#define _X 67

void TEST_1()
{
	heap_ty *heap = NULL;
    

    
    printf ("\n--------------------------- TEST #1 -----------------------------\n\n\n");

	printf ("\nNow testing -------- HEAPCreate() --------\n\n");
	heap = HEAPCreate(IntCmp);
	__TEST__(heap, !=, NULL);

	printf ("\nNow testing -------- HEAPSize() --------\n\n");
	__TEST__(HEAPSize(heap), ==, 0);

	printf ("\nNow testing -------- HEAPSize() --------\n\n");
	__TEST__(HEAPIsEmpty(heap), ==, 1);
	
	HEAPDestroy(heap);
	heap = NULL;

}

void TEST_2()
{
    int arr[_SIZE] = {67,45, 24, 12, 7, 6, 4, 1};
	heap_ty *heap = NULL;
    

    
    printf ("\n--------------------------- TEST #2 -----------------------------\n\n\n");

	printf ("\nNow testing -------- HEAPCreate() --------\n\n");
	heap = HEAPCreate(IntCmp);
	__TEST__(heap, !=, NULL);

	printf ("\nNow testing -------- HEAPPush(1) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[7]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(4) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[6]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(6) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[5]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(7) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[4]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(12) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[3]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(24) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[2]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(45) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[1]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(67) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[0]), ==, 0);

	printf ("\nNow testing -------- HEAPPop(67) --------\n\n");
	HEAPPop(heap);

	printf ("\nNow testing -------- HEAPSize() == 7 ? --------\n\n");
	__TEST__(HEAPSize(heap), ==, 7);

	printf ("\nNow testing -------- HEAPPeek() --------\n\n");
	__TEST__(*(int *)HEAPPeek(heap), ==, arr[1]);


	HEAPDestroy(heap);
	heap = NULL;

}


void TEST_3()
{
    int arr[_SIZE] = {67,45, 24, 12, 7, 6, 4, 1};
	heap_ty *heap = NULL;
    

    
    printf ("\n--------------------------- TEST #3 -----------------------------\n\n\n");

	printf ("\nNow testing -------- HEAPCreate() --------\n\n");
	heap = HEAPCreate(IntCmp);
	__TEST__(heap, !=, NULL);

	printf ("\nNow testing -------- HEAPPush(67) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[0]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(45) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[1]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(24) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[2]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(12) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[3]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(7) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[4]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(6) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[5]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(4) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[6]), ==, 0);
	printf ("\nNow testing -------- HEAPPush(1) --------\n\n");
	__TEST__(HEAPPush(heap, &arr[7]), ==, 0);

	printf ("\nNow testing -------- HEAPRemove(7) --------\n\n");
	__TEST__(*(int *)HEAPRemove(heap, &arr[4], is_match), ==, arr[4]);
	printf ("\nNow testing -------- HEAPRemove(7) --------\n\n");
	__TEST__(HEAPRemove(heap, &arr[4],is_match), ==, NULL);

	printf ("\nNow testing -------- HEAPSize() == 7 ? --------\n\n");
	__TEST__(HEAPSize(heap), ==, 7);



	HEAPDestroy(heap);
	heap = NULL;

}
int main ()
{
	

	TEST_1();
    TEST_2();
    TEST_3();
	/*
	*/
	
	return 0;
}


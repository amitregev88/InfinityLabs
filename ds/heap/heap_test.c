/*************************************************************
*OL124  Test Heap project
*
*   Test
******************************************************************/

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,a,y)  if ((x) a (y)) {IF_SUCCESS(1);}else{IF_SUCCESS(0);}

#include <stdio.h> /* printf */
#include <string.h> /*strcmp*/
#include <stdlib.h> /*malloc*/
#include "heap.h"

typedef struct 
{
	int id; 
	char name[20]; 
}person_ty;

int IDCmp(const void* data1, const void* data2)
{
    const person_ty *p1 = data1;
    const person_ty *p2 = data2;

    return (p1->id - p2->id);
  
}

int IsMatachID(const void* data1, const void* data2)
{
    const person_ty *p1 = data1;
    const person_ty *p2 = data2;

    return (p1->id == p2->id);
  
}

void Heap_Test(void)
{
	heap_ty *heap = NULL;

	person_ty arr[20] = {{1,"Amit"}, {2,"Amir"}, {3,"David"}, {4,"Alex"}, {5,"Noya"}, {6,"Liat"}, {7,"Ron"}, {8,"Shir"}, {9,"Dan"}, {10,"Amit"}, {11,"Dana"}, {12,"Merav"}, {13,"Yoni"}, {14,"Mani"}, {15,"Pini"}, {16,"Eli"}, {17,"Naama"}, {18,"Dany"}, {19,"Benny"}, {20,"Itay"}};

	printf("*****************  Heap Test  **************\n");
	
	printf("\n\nTesting of HEAPCreate function:\n");

	heap = HEAPCreate(&IDCmp);

	TEST(heap, != , NULL);

	printf("\nTesting of Size and IsEmpty function:\n");

	TEST(HEAPIsEmpty(heap), == , 1);
	TEST(HEAPSize(heap), ==, 0);

	printf("\nTesting of HEAPPush and HEAPPeek function:\n");

	HEAPPush(heap, &arr[1]);
	HEAPPush(heap, &arr[0]);
	TEST(HEAPPush(heap, &arr[2]), == , 0);
	HEAPPush(heap, &arr[3]);
    TEST((person_ty *)HEAPPeek(heap), == , &arr[3]);
    TEST(HEAPSize(heap), ==, 4);

    printf("\nTesting of HEAPRemove function:\n");
    TEST(HEAPRemove(heap,&arr[0],IsMatachID),==,&arr[0]); /* remove node  with one child*/
    TEST(HEAPSize(heap), ==, 3);
	HEAPPush(heap, &arr[0]);

    printf("\nTesting of HEAPIsEmpty and HEAPSize function:\n");
	TEST(HEAPIsEmpty(heap), == , 0);
	TEST(HEAPSize(heap), ==, 4);

    

    printf("\nTesting of HEAPPop and HEAPPeek function:\n");
    HEAPPush(heap, &arr[4]);
    TEST((person_ty *)HEAPPeek(heap), == , &arr[4]);
    HEAPPop(heap);
    TEST(HEAPSize(heap), ==, 4);
    TEST((person_ty *)HEAPPeek(heap), == , &arr[3]);
    HEAPPush(heap, &arr[4]);
    HEAPPush(heap, &arr[6]);
    HEAPPush(heap, &arr[5]);

    printf("\nTesting of HEAPRemove function:\n");

    TEST(HEAPRemove(heap,&arr[5],IsMatachID),==,&arr[5]); /* remove node with 2 children */ 
    TEST(HEAPSize(heap), ==, 6);
    HEAPPush(heap, &arr[5]);

    TEST(HEAPRemove(heap,&arr[0],IsMatachID), == ,&arr[0]); /* remove a leaf */ 
    TEST(HEAPSize(heap), ==, 6);
    HEAPPush(heap, &arr[0]);

    TEST(HEAPRemove(heap,&arr[6],IsMatachID),==,&arr[6]); /* remove the root*/
    TEST(HEAPSize(heap), ==, 6);
    HEAPPush(heap, &arr[6]);

	HEAPDestroy(heap);
}


int main(void)
{
	Heap_Test();

	return 0;
}
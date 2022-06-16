/*************************************************************
*OL124  Test Binary Search Tree project
*
*   Test
******************************************************************/

#include <stdio.h> /* printf */
#include "bst.h"

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,a,y)  if ((x) a (y)) {IF_SUCCESS(1);}else{IF_SUCCESS(0);}

int IntCompare(const void* data1, const void* data2)
{

    return (*(int *)data1 > *(int *)data2 ? 1 : *(int *)data2 > *(int *)data1 ? -1 : 0);

}

int AddIntNum(void *data, void *num)
{

	if (data == NULL || num == NULL)
	{
		return 1;
	}
	
	*(int *)data += *(int *)num;
	
	return 0;

}


int main(void)
{

bst_ty *new_tree = NULL;
bst_iter_ty iter;

size_t counter = 0;

int root = 20, num25 = 25, num27 = 27 , num30 = 30, num21 = 21, num16 = 16, num23 = 23, num22 = 22;
int num18 = 18, num6 = 6, num10 = 10;


printf("Testing of BSTCreate function:\n");
new_tree = BSTCreate(IntCompare);
TEST(new_tree, != , NULL);

printf("\nTesting of BSTIsEmpty function in case the tree is empty:\n");
TEST(BSTIsEmpty(new_tree), == , 1);

printf("\nTesting of BSTSize function in case the tree is empty:\n");
TEST(BSTSize(new_tree), == , 0);

printf("\nTesting of BSTInsert function:\n");
iter = BSTInsert(new_tree, &root);

printf("\nTesting of BSTIsEmpty function in case the tree is not empty:\n");
TEST(BSTIsEmpty(new_tree), == , 0);

printf("\nTesting of BSTSize function in case size is greater than 0:\n");
TEST(BSTSize(new_tree), == , 1);

printf("\nTesting of BSTInsert function:\n");
BSTInsert(new_tree, &num16);

printf("\nTesting of BSTSize function in case size is greater than 0:\n");
TEST(BSTSize(new_tree), == , 2);

printf("\nTesting of BSTInsert function in case of inserting exist number in the tree:\n");
BSTInsert(new_tree, &num16);
TEST(BSTSize(new_tree), == , 2);

BSTInsert(new_tree, &num23);
BSTInsert(new_tree, &num27);
BSTInsert(new_tree, &num22);
BSTInsert(new_tree, &num25);
BSTInsert(new_tree, &num21);
BSTInsert(new_tree, &num10);
BSTInsert(new_tree, &num6);
BSTInsert(new_tree, &num30);
BSTInsert(new_tree, &num18);


printf("\nTesting of BSTBegin, BSTIter_Is_Equal, BSTEnd, BSTGet_Data, BSTNext functions\n");

iter =  BSTBegin(new_tree);
for(iter; !BSTIter_Is_Equal(iter,BSTEnd(new_tree)); iter = BSTNext(iter))
{
  printf("%d, ",*(int *)BSTGet_Data(iter));
  
}
  printf("\nshould be \n 6, 10, 16, 18, 20, 21, 22, 23, 25, 27, 30\n");


printf("\nTesting of BSTEnd ,BSTSize, BSTPrev, BSTGet_Data functions\n");

iter =  BSTPrev(BSTEnd(new_tree));

counter = BSTSize(new_tree);

for(iter; counter > 1 ; iter = BSTPrev(iter))
{
  printf("%d ",*(int *)BSTGet_Data(iter));
  --counter;
}

printf("%d ",*(int *)BSTGet_Data(iter));

 printf("\nshould be \n 30 27 25 23 22 21 20 18 16 10 6\n");

 printf("\nTesting of BSTFind function\n");

 TEST(*(int *)BSTGet_Data(BSTFind(new_tree, &num21)), ==, 21);


 printf("\nTesting of ForEach function\n");

  
  TEST(BSTForeach());












/*

iter =  BSTBegin(new_tree);

BSTRemove(new_tree,iter);

iter =  BSTBegin(new_tree);

for(iter; !BSTIter_Is_Equal(iter,BSTEnd(new_tree)); iter = BSTNext(iter))
{
  printf("%d\n",*(int *)BSTGet_Data(iter));
}




*/




/*BSTDestroy(new_tree);*/

return 0;
}


















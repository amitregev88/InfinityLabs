/*************************************************************
*OL124  Test AVL Tree project
*
*   Test
******************************************************************/

#include <stdio.h> /* printf */
#include "avl.h"

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,a,y)  if ((x) a (y)) {IF_SUCCESS(1);}else{IF_SUCCESS(0);}


int IntCompare(const void* key1, const void* key2)
{
    return (*(int *)key1 > *(int *)key2 ? 1 : *(int *)key2 > *(int *)key1 ? -1 : 0);
}

int AddIntNum(void *data, const void *num)
{
	if (data == NULL || num == NULL)
	{
		return 1;
	}
	
	*(int *)data += *(int *)num;
	
	return 0;
}

static int PrintAVLTree(void *data, const void *param)
{
   	param = (void *)param;

	printf("%d  ", *(int *) data);

    return 0;
}


int main(void)
{


avl_ty *new_tree = NULL;

int num20 = 20, num25 = 25, num27 = 27 , num30 = 30, num21 = 21, num16 = 16, num23 = 23, num22 = 22;
int num18 = 18, num6 = 6, num10 = 10, num1 = 1;

printf("Testing of AVLCreate function:\n");
new_tree = AVLCreate(IntCompare);
TEST(new_tree, != , NULL);

printf("\nTesting of AVLIsEmpty function in case the tree is empty:\n");
TEST(AVLIsEmpty(new_tree), == , 1);

printf("\nTesting of AVLSize function in case the tree is empty:\n");
TEST(AVLSize(new_tree), == , 0);

printf("\nTesting of AVLInsert function:\n");
TEST(AVLInsert(new_tree,&num20, &num20), == , 0);

printf("\nTesting of AVLIsEmpty function in case the tree is not empty:\n");
TEST(AVLIsEmpty(new_tree), == , 0);

printf("\nTesting of AVLSize function in case size is greater than 0:\n");
TEST(AVLSize(new_tree), == , 1);

printf("\nTesting of AVLInsert function:\n");
AVLInsert(new_tree, &num16 ,&num16);

printf("\nTesting of AVLSize function in case size is greater than 0:\n");
TEST(AVLSize(new_tree), == , 2);

printf("\nTesting of AVLInsert function in case of inserting exist key in the tree:\n");
TEST(AVLInsert(new_tree, &num16 ,&num16), == , 2);
TEST(AVLSize(new_tree), == , 2);


AVLInsert(new_tree,&num23, &num23);
AVLInsert(new_tree,&num27, &num27);
AVLInsert(new_tree,&num22, &num22);
AVLInsert(new_tree,&num25, &num25);
AVLInsert(new_tree,&num21, &num21);
AVLInsert(new_tree,&num10, &num10);
AVLInsert(new_tree,&num6, &num6);
AVLInsert(new_tree,&num30, &num30);
AVLInsert(new_tree,&num18, &num18);

printf("\nTesting of AVLHeight and AVLInsert (balance tree functionality) function:\n\n");
TEST(AVLHeight(new_tree),==,3);

printf("\nTesting of AVLFind function:\n\n");
TEST(AVLFind(new_tree, &num18), == ,&num18);

printf("\nTesting of AVLForEach function:\n");

printf("\npost order method:\n");

TEST(AVLForeach(new_tree,AddIntNum, &num1, post_order), == ,0);
AVLForeach(new_tree,PrintAVLTree, NULL, post_order);

printf("\n\nshould be:\n 7  19  17  11  22  23  26  31  28  24  21\n");


printf("\n\nin order method:\n");

TEST(AVLForeach(new_tree,AddIntNum, &num1, in_order), == ,0);
AVLForeach(new_tree,PrintAVLTree, NULL, in_order);

printf("\n\nshould be:\n 8  12  18  20  22  23  24  25  27  29  32\n");

printf("\n\npre order method:\n");

TEST(AVLForeach(new_tree,AddIntNum, &num1, pre_order), == ,0);
AVLForeach(new_tree,PrintAVLTree, NULL, pre_order);

printf("\n\nshould be:\n 23  13  9  19  21  26  25  24  30  28  33\n");

printf("\n");

printf("\nTesting of Remove function\n");

TEST(AVLRemove(new_tree, &num27),==,&num27);
TEST(AVLSize(new_tree), == , 10);
/*TEST(AVLRemove(new_tree, &num25),==,&num25);
TEST(AVLSize(new_tree), == , 9);*/
TEST(AVLRemove(new_tree, &num30),==,&num30);
TEST(AVLSize(new_tree), == , 9);

AVLDestroy(new_tree);

return 0;
}
/*************************************************************************************
* Name: Amit Regev 
* Date: 04.26.22
* OL124 Double Linked List test
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include "dlinked_list.h" 

#define IF_SUCCESS(A) A != NULL? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


dlist_ty * Test_DListCreate(void);


dlist_ty *list = DListCreate();
	
	printf("testing of DListCreate() function\n");
	IF_SUCCESS(list)
	
	


dlist_node_ty * Test_DListInsert(dlist_ty *list, dlist_node_ty *where, void *data)
{


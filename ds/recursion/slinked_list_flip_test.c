/*************************************************************
*OL124 SLinked List Flip TEST
*
*Author: Yotam Aharon
*
******************************************************************/

#include <stdio.h> /* printf, puts */
#include <assert.h>
#include "slinked_list_modify_for_exercises.h"


/* -- to reverse the single list to the other direction (NOT RETURN THE NEW HEAD) */
node_t *FlipList(node_t *node)
{

	node_t *current_next = NULL;
	
	assert(node);
	
	if (node->next == NULL)
	{
		return node;
	}

	current_next = FlipList(node->next);
	
	current_next->next = node;
	
	node->next = NULL;
	
	return node;
}


/* --- utilities function --- */
void SIngleListIntPrint(node_t *head)
{
	node_t *iter = head;
	while (iter)
	{
		printf("%d -> ",*(int *)iter->data);
		iter = iter->next;
	}
	puts("NULL\n");
}


int main(void)
{
	int a = 1;
	int * a_data = &a;
	int b = 2;
	int * b_data = &b;
	int c = 3;
	int * c_data = &c;
	int d = 4;
	int * d_data = &d;
	int e = 5;
	int * e_data = &e;
	int f = 6;
	int * f_data = &f;

	
	node_t *f_list = SingleListCreate(f_data);
	node_t *e_list = SingleListAdd(f_list,e_data);
	node_t *d_list = SingleListAdd(e_list,d_data);
	node_t *c_list = SingleListAdd(d_list,c_data);
	node_t *b_list = SingleListAdd(c_list,b_data);
	node_t *a_list = SingleListAdd(b_list,a_data);


/* --- test for flip ---*/
	puts("BEFORE FLIP");
	SIngleListIntPrint(a_list);
	
	f_list = SingleListGetNode(a_list,5);

	FlipList(a_list);
	puts("AFTER FLIP");
	SIngleListIntPrint(f_list);


	FlipList(f_list);
	puts("AFTER ANOTHER FLIP");
	SIngleListIntPrint(a_list);

	SListDestroy(f_list);
	return 0;
}




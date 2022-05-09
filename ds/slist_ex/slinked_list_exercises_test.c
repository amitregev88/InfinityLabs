/*************************************************************
*OL124 SLinked List Exercises Tests
*
*Author: Yotam Aharon
*
******************************************************************/

#include <stdio.h> /* printf, puts */
#include "slinked_list_modify_for_exercises.h"

#define RESET   "\033[0m"        /* Reset colour */
#define RED     "\033[31m"       /* Red */
#define GREEN   "\033[32m"      /* Green */
#define White   "\033[37m"	    /* White */

#define CHECK(function, val, variable, input) val == variable ? \
printf(GREEN "%s worked succesfully for %s\n",function, input) : \
printf(RED "%s failed  for %s\n",function, input)

node_t *Flip(node_t *head)
{
	/* code here*/
}

int HasLoop(const node_t *head)
{
	/* code here*/
}

node_t *FindIntersection(node_t *head1, node_t *head2)
{
	/* code here*/
}

/* --- utilities functions --- */
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

void SIngleListCycleIntPrint(node_t *head)
{
	int i = 0;
	node_t *iter = head;
	for (i = 0; i <16; ++i)
	{
		printf("%d -> ",*(int *)iter->data);
		iter = iter->next;
	}
	puts("...\n");
}

	

int main(void)
{
	int has_loop = 0;

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

	int g = 8;
	int * g_data = &g;
	int h = 9;
	int * h_data = &h;
	node_t *h_list = NULL;
	node_t *g_list = NULL;

	node_t *new_h = NULL;
	node_t *back_to_orig_h = NULL;
	node_t *intersection = NULL;
	node_t *f_list = SingleListCreate(f_data);
	node_t *e_list = SingleListAdd(f_list,e_data);
	node_t *d_list = SingleListAdd(e_list,d_data);
	node_t *c_list = SingleListAdd(d_list,c_data);
	node_t *b_list = SingleListAdd(c_list,b_data);
	node_t *a_list = SingleListAdd(b_list,a_data);


/* --- test for flip ---*/
	printf (White" ----------Flip Test--------------\n");
	puts("BEFORE FLIP");
	SIngleListIntPrint(a_list); 
	
	new_h = Flip(a_list);
	puts("AFTER FLIP");
	SIngleListIntPrint(new_h);

	back_to_orig_h = Flip(new_h);
	puts("AFTER ANOTHER FLIP");
	SIngleListIntPrint(back_to_orig_h);


/* --- test for has loop --- */
	printf (White" ----------HasLoop Test--------------\n");
	puts("BEFORE LOOP CREATED");

	has_loop = HasLoop(a_list);
	CHECK("HasLoop",0,has_loop, "detect there is no loop");

	(SingleListGetNode(a_list,5))->next = SingleListGetNode(a_list,2);
	puts("AFTER LOOP CREATED: ");
	SIngleListCycleIntPrint(a_list);

	has_loop = HasLoop(a_list);
	CHECK("HasLoop",1,has_loop, "detect there is loop");
	

/* --- test for FindIntersection --- */
	printf (White" ----------FindIntersection Test--------------\n");
	(SingleListGetNode(a_list,5))->next = NULL;

	c_list = SingleListGetNode(a_list,3);

	h_list = SingleListCreate(h_data);
	g_list = SingleListAdd(h_list,g_data);
	
	puts("THE LISTS BRFORE ANY INTERSECTION:");
	puts("LIST 1 IS:");
	SIngleListIntPrint(a_list);
	puts("LIST 2 IS:");
	SIngleListIntPrint(h_list);

	intersection = FindIntersection(a_list, h_list);
	CHECK("FindIntersection",NULL,intersection, "detect there is no intersection");


	h_list->next->next = a_list;

	puts("THE LISTS AFTER INTERSECTION:");
	puts("LIST 1 IS:");
	SIngleListIntPrint(a_list);
	puts("LIST 2 IS:");
	SIngleListIntPrint(h_list);

	intersection = FindIntersection(a_list, h_list);
	CHECK("FindIntersection",1,*(int *)intersection->data, "detect intersection");

	SListDestroy(h_list);

	return 0;
}




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

	node_t *curr = NULL, *next_curr = NULL, *tmp = NULL; 
	
	if ((!head) || (!(head->next)))
	{
		return head;
	} 
	
	curr = head;
	
	next_curr = head->next;
	
	tmp = next_curr->next;
	
	curr->next = NULL;
	
	while (tmp->next != NULL)
	{
	
		next_curr->next = curr;
	
		curr = next_curr;
	
		next_curr = tmp; 
	
		tmp = tmp->next;
	}
		
	next_curr->next = curr;
	
	tmp->next = next_curr;
	
	return tmp; 
	
}


int HasLoop(const node_t *head)
{
	node_t *first = NULL;
	
	node_t *has_loop = NULL;

	int flag = 0;

	first = (node_t *) head;

	
	has_loop = Flip(first);
	
	
	if ((has_loop->data == first->data) && (has_loop->next == first->next))
	{
		flag = 1;
	}
	

	
	Flip(has_loop);
	

	
	return flag;
}


node_t *FindIntersection(node_t *head_1, node_t *head_2)
{
	
	size_t i = 0, size_list1 = 0, size_list2 = 0, steps = 0;
	
	size_list1 = SingleListSize(head_1);
	
	size_list2 = SingleListSize(head_2);
	
	
	
	if (size_list1 < size_list2)
	{
		node_t *tmp = NULL;
				
		tmp = head_1;
		
		head_1 = head_2;
		
		head_2 = tmp;
		
		steps = size_list2 - size_list1;
	}
	
	else
	{
		steps = size_list1 - size_list2;
	}
	
	
	for (; i < steps; ++i)
	{
		head_1 = head_1->next;
	}
	

	while ((NULL != head_1) && (NULL != head_2))
	{
		if (head_1 == head_2)
		{
			return head_1;
		}
		
		head_1 = head_1->next;
		head_2 = head_2->next;
	}
	
	
	return NULL;
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
	
	SIngleListIntPrint(a_list);

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




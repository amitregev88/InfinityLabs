/*************************************************************************************
* OL124  Modify Functions For SLinked List Exercises 
*
*Author: Yotam Aharon
*   
*************************************************************************************/
#ifndef OL124_SILINKED_LIST_H
#define OL124_SILINKED_LIST_H

#include <stddef.h>
#include <stdlib.h>

typedef struct node 
{
    void *data; 
    struct node *next;
}node_t;

static void SwapNode_tData(node_t *node_a, node_t *node_b);

/*************************************************************************************
* --- SingleListCreate --- returns *head
**************************************************************************************/
node_t *SingleListCreate(void *data);

/*************************************************************************************
* --- SingleListCreate --- free() all the NODES  O(n)
**************************************************************************************/
void SListDestroy(node_t *head);

/*************************************************************************************
* --- SingleListAdd --- receives the "where" and inserts before the "where" O(1)
**************************************************************************************/
node_t * SingleListAdd(node_t * where, void *data);

/*************************************************************************************
* --- SingleListRemove --- Removes the NODE in the node *to_remove
* return NEXT NODE (iter) o(1)***
**************************************************************************************/
void *SingleListRemove(node_t *to_remove);

/*************************************************************************************
* --- SingleListIsSameNode --- * return 1 in case of match or 0
**************************************************************************************/
int SingleListIsSameNode(node_t *node1, node_t *node2);

/*************************************************************************************
* --- SingleListSize --- returns the size of the Linked List ----- O(n)
**************************************************************************************/
size_t SingleListSize(const node_t *head);

/*************************************************************************************
* --- GetNode --- returns the sthe node numbr <iter> ----- O(n)
**************************************************************************************/
node_t * SingleListGetNode(const node_t *head, int iter);

/* --------------- inplementation --------------- */
node_t *SingleListCreate(void *data)
{
node_t *head = malloc (sizeof(node_t));
	if (NULL == head)
	{
		return NULL;
	}
	head->data = data;
	head->next = NULL;
	
	return head;
}

void SListDestroy(node_t *head)
{
	node_t *iter = head;
	node_t *iter_next = head->next;

	while (iter_next != NULL)
	{
		free(iter);
		iter = iter_next;
		iter_next = iter_next->next;
	}
	free(iter);
}

node_t * SingleListAdd(node_t *where, void *data)
{
	node_t *next = where->next;
	node_t *new_node = malloc (sizeof(node_t));
	if (NULL == new_node)
	{
		return NULL;
	}
	new_node->data = data;
	new_node->next = next;
	where->next = new_node;
	SwapNode_tData(new_node,where);	

	return where;
}

void *SingleListRemove(node_t *to_remove)
{
	node_t *keep_new_next = to_remove->next->next;
	void *data = to_remove->data;
	
	to_remove->data = to_remove->next->data;
	free(to_remove->next);
	to_remove->next = keep_new_next;

	return data;
}

int SingleListIsSameNode(node_t *node1, node_t *node2)
{
	return ((node1->data == node2->data) && \
			(node1->next->data == node2->next->data));
}

size_t SingleListSize(const node_t *head)
{
	size_t count = 0;
	const node_t *iter = head;

	while (iter)
	{
		iter = iter->next;
		count++;
	}
	return count;
}

node_t * SingleListGetNode(const node_t *head, int iter)
{
	node_t *node = (node_t *)head;
	int i = 0;
	for (; i < iter; ++i)
	{
		node = node->next;
	}
	return  node;
}

static void SwapNode_tData(node_t *node_a, node_t *node_b)
{
	void *tmp_data = NULL;
	
	tmp_data = node_a->data;
	node_a->data = node_b->data;
	node_b->data = tmp_data;
}
#endif /*OL124_SILINKED_LIST_H*/


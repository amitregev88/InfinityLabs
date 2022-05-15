/*************************************************************************************
* Name: Amit Regev 
* Reviewer: Noam Dan Hadad
* Date: 04.26.22
* OL124 Double Linked List
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include "dlinked_list.h" 

struct doubly_node 
{
    void *data; 
    dlist_node_ty *next;
    dlist_node_ty *prev;
};


struct doubly_list
{
    dlist_node_ty head;
    dlist_node_ty tail;
};


dlist_ty *DListCreate(void)
{
	dlist_ty *new_list = (dlist_ty *)malloc(sizeof(dlist_ty));
	
	if (NULL == new_list)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	
	new_list->head.next = &new_list-> tail;
	new_list->head.prev = NULL;
	new_list->tail.next = NULL;
	new_list->tail.prev = &new_list->head;
	
	return new_list;
	
}

void DListDestroy(dlist_ty *list)
{
	dlist_node_ty *iter_node = DListBegin(list);
	
	while (iter_node != DListEnd(list))
	{
		iter_node = DListRemove(iter_node);
	}
	
		
	free(list);
	list = NULL;
}

dlist_node_ty *DListInsert(dlist_node_ty *where, void *data)
{
	dlist_node_ty *new_node = (dlist_node_ty *)malloc(sizeof(dlist_node_ty));
	
	if (NULL == new_node)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	

	where->prev->next = new_node;
	new_node->prev = where->prev;
	new_node->next = where;
	where->prev = new_node;
	new_node->data = data;
	
	return new_node;
	
}

dlist_node_ty *DListRemove(dlist_node_ty *to_remove)
{

	dlist_node_ty *next_node = DListGetNext(to_remove);
	
	to_remove->prev->next = next_node;
	next_node->prev = to_remove->prev;
	
	
	free (to_remove);
	to_remove = NULL;
	
	return next_node;

}

dlist_node_ty *DListPushBack(dlist_ty *list, void *data)
{
	return DListInsert(DListEnd(list), data);
}

dlist_node_ty *DListPushFront(dlist_ty *list, void *data)
{
	return DListInsert(DListBegin(list), data);
}

void *DListPopBack(dlist_ty *list)
{
	
	dlist_node_ty *temp = list->tail.prev;


	void *data = DListGetData(temp);
	
	
	list->tail.prev = DListGetPrev(temp);
	temp->prev->next = DListEnd(list);
	

	free(temp);
	
	return data;

}

void *DListPopFront(dlist_ty *list)
{
	dlist_node_ty *pop_front_node = DListBegin(list);
	
	void *data_pop_front = DListGetData(pop_front_node);
	
	list->head.next = DListGetNext(pop_front_node);
	pop_front_node->next->prev = &list->head;
	
	free(pop_front_node);
	
	
	return data_pop_front;
}


size_t DListSize(const dlist_ty *list)
{
	size_t counter = 0;
	dlist_node_ty *begin = DListBegin(list);
	
	
	if(DListIsEmpty(list))
	{
		return 0;
	}
	
	while(begin != DListEnd(list))			/*for(tmp; tmp != list->tail; tmp = DListGetNext(tmp))*/
	{
		++counter;
		begin = DListGetNext(begin); 
	}
		
	return counter;

}

int DListIsEmpty(const dlist_ty *list)
{
	return (DListBegin(list) == DListEnd(list));
}

void *DListGetData(const dlist_node_ty *node)
{
	return node->data;
}

void DListSetData(dlist_node_ty *node, void *data)
{
	node->data = data;	
}
dlist_node_ty *DListGetNext(const dlist_node_ty *node)
{
	return node->next;
}

dlist_node_ty *DListGetPrev(const dlist_node_ty *node)
{
	return node->prev;
}

dlist_node_ty *DListFind(const dlist_node_ty *from, const dlist_node_ty *to, int (*is_match)(const void *data, const void *param), const void *param)
{
	
	dlist_node_ty *iter_node = (dlist_node_ty *) from;
	
	
	while (iter_node != to)
	{
		if (is_match(DListGetData(iter_node), param))
		{
			return iter_node;
		}
		
		iter_node = DListGetNext(iter_node);
	}
	
	return NULL;
}


dlist_node_ty *DListBegin(const dlist_ty *list)
{
	return list->head.next;
}

dlist_node_ty *DListEnd(const dlist_ty *list)
{
	return (dlist_node_ty *) &list->tail;
}

int DListForEach(dlist_node_ty *from, const dlist_node_ty *to, int (*action)(void *list_data, const void *param), const void *param)
{

	dlist_node_ty *iter =(dlist_node_ty *) from; 

	
	while (iter != to)
	{
		if (action(DListGetData(iter),param) == 1)
		{	
			return 1;
		}
		
		iter = DListGetNext(iter);
	}
		
	return 0;	
}

void DListSplice(dlist_node_ty *dest, dlist_node_ty *from, dlist_node_ty *to)

	
{
	dlist_node_ty *temp_src = to->prev;
	
	
	from->prev->next = to;
	to->prev = DListGetPrev(from);
	
	
	dest->prev->next = from;
	from->prev = dest->prev;
	
	
	dest->prev = temp_src;
	temp_src->next = dest;
	
	
	
	
}
/*************************************************************************************
* --- Is Same Node ---  returns 1 if node1=node2 , returns 0  otherwise
**************************************************************************************/
int DListIsSameNode(const dlist_node_ty *node_1, const dlist_node_ty *node_2)
{
	return (node_1 == node_2);
}



/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 04.26.22
* OL124 Double Linked List
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include "dlinked_list.h" 

struct doubly_node 
{
    void *data; 
    doubly_node *next;
    doubly_node *prev;
};


struct doubly_list
{
    doubly_node head;
    doubly_node tail;
}


dlist_ty *DListCreate(void)
{
	dlist_ty *new_list = (dlist_ty *)malloc(sizeof(dlist_ty));
	
	if (NULL == new_list)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	
	new_list->head.next = &new_list-> tail
	new_list->head.prev = NULL;
	new_list->tail.next = NULL;
	new_list->tail.prev = &new_list->head
	
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
	
	if (NULL == node)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	

	where->prev.next = new_node;
	new_node->prev = where->prev;
	new_node->next = where;
	where->prev = new_node;
	new_node->data = data;
	
	return new_node;
	
}

dlist_node_ty *DListRemove(dlist_node_ty *to_remove)
{

	dlist_node_ty next_node = to_remove->next;
	
	to_remove->prev->next = next_node;
	tmp->prev = to_remove->prev;
	
	
	free (to_remove);
	
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
	dlist_ty data_pop_back = GetData(list->tail.prev);

	DListRemove(list->tail.prev);
	
	return data_pop_back;
}

void *DListPopFront(dlist_ty *list)
{
	dlist_ty data_pop_front = GetData(DListBegin(list));

	DListRemove(DListBegin(list));
	
	return data_pop_front;
}


size_t DListSize(const dlist_ty *list)
{
	size_t counter = 0;
	dlist_node_ty begin = DListBegin(list);
	
	
	if(DListIsEmpty(list))
	{
		return 0;
	}
	
	while(begin != DListEnd(list))			/*for(tmp; tmp != list->tail; tmp = DListGetNext(tmp))*/
	{
		++counter;
		begin = DListGetNext(tmp); 
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

void DListSetData(dlist_node_ty *no void *data)
{
	node-> data = data;	
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
	int output_func = 0;	
	dlist_node_ty *iter_node = (dlist_node_ty *) from;
	
	output_func = is_match(iter_node->data,param);
		
	if (!output_func));
	{
		return iter_node;
	}
	
	
	while((iter_node != to) && output_func == 1)	
	{
		iter_node = DListGetNext(iter_node); 
		output_func = is_match(iter_node->data,param);
	} 
	
	if(iter_node == to && output_func == 1)
	{
		iter_node = NULL;
	}

	
	return iter_node;
}

dlist_node_ty *DListBegin(const dlist_ty *list)
{
	return list->head.next;
}

dlist_node_ty *DListEnd(const dlist_ty *list)
{
	return (dlist_node_ty *) &list->tail;
}

int DListForEach(const dlist_node_ty *from, const dlist_node_ty *to, int (*action)(void *list_data, void *param), void *param)
{

	dlist_node_ty *iter =(dlist_node_ty *) from; 

	for(iter; iter != to; iter = DListGetNext(iter))
	{
		if (!action(iter->data, param))
		{	
			return 0;
		}
	}
		
	return 1;	
}

void DListSplice(dlist_node_ty *dest, dlist_node_ty *from, dlist_node_ty *to)
{
	
	from->prev->next = to;
	from->prev = dest->prev;
	to->prev->next = dest;
	
	to->prev = from->prev;
	dest->prev=to->prev	;
	dest->prev->next = from;
	
}


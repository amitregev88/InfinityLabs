/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 05.01.22
* OL124 Singly Linked List
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include "slinked_list.h" 



struct sin_list
{
    sin_node head;
    sin_node tail;
}

struct sin_node 
{
    void *data; 
    sin_node *next;
};

struct slist_iter
{
    slist_node_ty *node;
    
} slist_iter_ty;

typedef struct sin_node slist_node_ty;



sin_list_ty *SListCreate(void)
{
	slist_ty *new_list = (slist_ty *)malloc(sizeof(slist_ty));
	
	if (NULL == new_list)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	
	new_list->head.next = &new_list-> tail;
	
	new_list->tail.next = NULL;
	
	return new_list;
	
}

void SListDestroy(slist_ty *list)
{
	slist_iter_ty *iter_node = SListBegin(list);
	
	while (iter_node != SListEnd(list))
	{
		iter_node = SListRemove(iter_node);
	}
	
		
	free(list);
	list = NULL;
}



slist_iter_ty SListInsert(slist_ty *list, slist_iter_ty where, void *data)
{
	slist_node_ty *new_node = malloc(sizeof(slist_node_ty *));
	
	if (NULL == new_node)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	
	new_node->data = data;
	
		
	swap(where, new_node);

	return new_node;
	
}

static void swap(slist_iter_ty dest, slist_iter_ty src)
{
	void *tmp = src.node.data;
	
	
	src->node->data = dest-node->data;
	*next_node->data = tmp->data;
}




slist_iter_ty SListRemove(slist_ty *list, slist_iter_ty prev_remove)
{

	
	free (to_remove);
	
	return next_node;

}










/*


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
	
	dlist_node_ty *pop_back_node = list->tail.prev;
	
	void *data_pop_back = DListGetData(pop_back_node);
	
	pop_back_node = DListGetPrev(pop_back_node);

	pop_back_node->prev->next = DListEnd(list);
	
	DListRemove(pop_back_node);
	
	return data_pop_back;
}

void *DListPopFront(dlist_ty *list)
{
	dlist_node_ty *pop_front_node = DListBegin(list);
	
	void *data_pop_front = DListGetData(pop_front_node);
	
	pop_front_node = DListGetNext(pop_front_node);

	pop_front_node->next->prev = &list->head;
	
	DListRemove(pop_front_node);
	
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
	int output_func = 0;	
	dlist_node_ty *iter_node = (dlist_node_ty *) from;
	
	output_func = is_match(iter_node->data,param);
		
	if (!output_func)
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

	
	while (iter != to)
	{
		if (!action(DListGetData(iter),param))
		{	
			return 0;
		}
		
		iter = DListGetNext(iter);
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



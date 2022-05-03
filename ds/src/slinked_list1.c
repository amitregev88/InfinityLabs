/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 05.01.22
* OL124 Singly Linked List
*************************************************************************************/

#include <assert.h> /*assert*/
#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include "slinked_list.h" 

/*static void swap(slist_node_ty *dest, slist_node_ty *src);*/

struct sin_node 
{
    void *data; 
    slist_node_ty *next;
};



struct sin_list
{
   slist_node_ty *head;
   slist_node_ty *tail;
};



/*************************************************************************************
* --- ListCreate --- returns *list that points *head == NULL 
**************************************************************************************/
slist_ty *SListCreate(void)
{
	slist_ty *list = (slist_ty *)malloc(sizeof(slist_ty));
	slist_node_ty *dummy = (slist_node_ty *)malloc(sizeof(slist_node_ty));
	
	if (NULL == list)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	
	
	if (NULL == dummy)
	{
		printf("Memory allocation error\n");
		free(list);
		return NULL;
	}
	
	dummy->next = NULL;
	dummy->data = NULL;
	
	list->head = dummy;
	
	list->tail = dummy; 
		
	return list;
	
}

/*************************************************************************************
* --- ListDestroy --- free() all the NODES and LIST itself O(n)
**************************************************************************************/
void SListDestroy(slist_ty *list)
{
		
	slist_iter_ty iter = SListBegin(list);
	
	while (!SListIsSameIter(iter, SListEnd(list)))
	{
		iter = SListRemove(list,iter);
	}
	
		
	free(list);
	list = NULL;
}

/*************************************************************************************
* --- Insert --- receives the "where" and inserts before the "where" O(1)
**************************************************************************************/
slist_iter_ty SListInsert(slist_ty *list, slist_iter_ty where, void *data)
{
		
	void* temp;
		
	slist_node_ty *new_node = (slist_node_ty *) malloc(sizeof(slist_node_ty));
	
			
	if (NULL == new_node)
	{
		printf("Memory allocation error\n");
		where.node = NULL;
		return where;
	}
	
	assert (NULL != where.node);
	assert (NULL != data);
	
	new_node->data = data; 
	
	
	
	temp = where.node->data;
	
	where.node->data = new_node->data;
	
	new_node->data = temp;

	
	if (SListIsSameIter(where,SListEnd(list)))
	{
		list->tail->next = new_node;
		new_node->next = NULL;
		list->tail = new_node;
		
		return where;
	}
	
	
	new_node->next =  where.node->next; /*connect new_node after where*/
	where.node->next = new_node;
	

	return where;
	
}

/*************************************************************************************
* --- Remove --- Removes the NODE in the itter to_remove
* return NEXT NODE (iter) o(1)***
**************************************************************************************/
slist_iter_ty SListRemove(slist_ty *list, slist_iter_ty to_remove)
{

	void *temp;
	
	temp = to_remove.node->data;
		
	to_remove.node->data = to_remove.node->next->data;
		
	to_remove.node->next->data = temp;
		
	assert(list != NULL);
		
	if (!SListIsSameIter(SListGetNext(to_remove),SListEnd(list)))
	{
		slist_iter_ty iter = {NULL};
		
		iter = SListGetNext(to_remove);
		
		to_remove.node->next = iter.node->next;
		
		free(iter.node);
		
		return to_remove;
		
	}
	
	else /* in case to_remove is the last node*/
	{	
	
		free(list->tail);
		to_remove.node->next = NULL;
		list->tail = to_remove.node;
		
			
		return to_remove;
		
	}
}
		

/*************************************************************************************
* --- PushBack --- add's a NODE at the END of the linked list 
* return LAST NODE (iter) O(1)
**************************************************************************************/
slist_iter_ty SListPushBack(slist_ty *list, void *data)
{
	assert(list != NULL);
	assert(data != NULL);
	
	return SListInsert(list,SListEnd(list), data);
}

/*************************************************************************************
* --- PushFront --- add's a NODE at the FRONT of the linked list 
* return FIRST NODE (iter) O(1)
**************************************************************************************/
slist_iter_ty SListPushFront(slist_ty *list, void *data)
{
	assert(list != NULL);
	assert(data != NULL);
	
	
	return SListInsert(list,SListBegin(list), data);
}

/*************************************************************************************
* --- PopBack --- POP's the LAST NODE 
* returns pointer to DATA O(n)
**************************************************************************************/
void *SListPopBack(slist_ty *list)
{
	slist_iter_ty iter = {NULL};
	void *data = NULL;

	assert(list != NULL);
		
	if (SListIsEmpty(list))
	{
		return NULL;
	}
	
	iter = SListBegin(list);
	
	while (iter.node->next != list->tail)
	{
		iter = SListGetNext(iter);
	}
	
	data = iter.node->data;
	
		
	iter.node->next = NULL;
	free(list->tail);
	list->tail = iter.node;

	return data;
		
}

/*************************************************************************************
* --- PopFront --- POP's the FIRST NODE 
* returns pointer to DATA O(1)
**************************************************************************************/
void *SListPopFront(slist_ty *list)
{

	slist_iter_ty iter = {NULL};
	void *data = NULL;
	
	void *temp = NULL;
	
	

	assert(NULL != list);
	
	if (SListIsEmpty(list))
	{
		return NULL;
	}

	if (SListSize(list) == 1)
	{	
		return SListPopBack(list);	
	}
	
	iter.node = list->head->next; 
	
	data = list->head->data;
	
	
	temp = list->head->data;
	
	list->head->data = iter.node->data;
	
	iter.node->data = temp;
	
	list->head->next = iter.node->next;
	
	free(iter.node);
	
	return data; 
}

/*************************************************************************************
* --- Size --- returns the size of the Linked List ----- O(n)
**************************************************************************************/
size_t SListSize(const slist_ty *list)
{

	slist_iter_ty iter = {NULL};
	
	size_t counter = 0;
		
	assert(list != NULL);
	
	iter = SListBegin(list);
	
	
	if(SListIsEmpty(list))
	{
		return 0;
	}
	
	while(!SListIsSameIter(iter,SListEnd(list)))			
	{
		++counter;
		iter = SListGetNext(iter); 
	}
		
	return counter;

}

/*************************************************************************************
* --- DListIsEmpty --- returns 1 in case is empty or -0 other case ---- O(1)
**************************************************************************************/
int SListIsEmpty(const slist_ty *list)
{
	assert(list != NULL);
	return (SListIsSameIter(SListBegin(list),SListEnd(list)));

}

/*************************************************************************************
* --- GetData --- Gets the DATA from a NODE 
**************************************************************************************/
void *SListGetData(const slist_iter_ty node)
{
	assert(NULL != node.node);
	return node.node->data;
}
/*************************************************************************************
* --- SetData --- Sets the DATA to a NODE 
**************************************************************************************/
void SListSetData(slist_iter_ty node, void *data)
{
	node.node->data = data;
}
/*************************************************************************************
* --- GetNext --- Gets a iter of the NEXT NODE to <node> 
**************************************************************************************/
slist_iter_ty SListGetNext(const slist_iter_ty node)
{
	slist_iter_ty next_node = {NULL};
	
	assert(NULL != node.node);
	
	next_node.node = (slist_node_ty *) node.node->next;
	
	return next_node;
}

/*************************************************************************************
--- Find --- Finds the Node using USER's comparison function 
* return iter   
**************************************************************************************/
slist_iter_ty SListFind(const slist_iter_ty from, const slist_iter_ty to, int (*is_match)(const void *data, const void *param), const void *param)
{
		
	slist_iter_ty iter = {NULL};
	iter.node = (slist_node_ty *) from.node;
	
		
	while (iter.node != (slist_node_ty *) to.node)
	{
		if (is_match(SListGetData(iter),param) == 0)
		{
			iter = SListGetNext(iter);
		}
		
		else
		{
			return iter;
		}
	}
	
	iter.node = NULL;
	
	return iter;
}
		
/*************************************************************************************
* --- Begin --- gets the first node O(1)
*return iter of the first NODE
**************************************************************************************/
slist_iter_ty SListBegin(const slist_ty *list)
{
	slist_iter_ty begin = {NULL};
	
	assert(list != NULL);
	
	begin.node = list->head;
	
	return begin;
}

/*************************************************************************************
* --- End --- gets the  next of the last connected node,  O(1)		
* return iter of tail
**************************************************************************************/
slist_iter_ty SListEnd(const slist_ty *list)
{
	slist_iter_ty iter = {NULL};
	
	assert(list != NULL);
	
	iter.node = (slist_node_ty *) list->tail;	
	
	return iter;
}

/*************************************************************************************
* --- ForEach --- * return 1 in case of success or 0  O(n) 
**************************************************************************************/
int SListForEach(const slist_iter_ty from, const slist_iter_ty to, int (*action)(void *list_data, void *param), void *param)
{
	slist_iter_ty iter = {NULL};
	iter.node =(slist_node_ty *) from.node; 
	
	while (iter.node != (slist_node_ty *) to.node)
	{
		if (!action(SListGetData(iter),param))
		{	
			return 0;
		}
		
		iter = SListGetNext(iter);
	}
		
	return 1;	
}







/*************************************************************************************
* --- IsSameIter --- * return 1 in case of match or 0
**************************************************************************************/
int SListIsSameIter(slist_iter_ty iter1, slist_iter_ty iter2)
{
	return (iter1.node == iter2.node);
}




/*
static void swap(slist_node_ty *dest, slist_node_ty *src)
{
	void *tmp= dest->data;
	

	dest->data = src->data;
	
	src->data = tmp;
}

*/





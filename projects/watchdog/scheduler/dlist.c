/*****************************************************************************/
/*	Project: double linked list												 */
/*	Date:15.06.2022															 */
/*	Name: Sapir Kazir														 */
/*	Reviewer: Hagai															 */
/*	Version: 3.00	fix begin returned value								 */
/******************************************************************************/

#include <assert.h> /*assert()*/
#include <stdlib.h> /*malloc(), free()*/

#include "dlist.h"

#define EMPTY 0

enum {FALSE = 0, TRUE = 1};
enum {SUCCESS = 0, FAILURE = 1};

struct dnode
{
	dlist_iter_ty prev_node;
	void *data;
	dlist_iter_ty next_node;
};

struct dlist
{
	dlist_iter_ty head;
	dlist_iter_ty tail;
};

/******************************************************************************/
dlist_ty *DListCreate(void)
{
	
	/*Create a new list*/
	dlist_ty *new_list = (dlist_ty*)malloc(sizeof(struct dlist));
	/*Check if the allocation failed, if failed retur null*/
	if (NULL == new_list)
	{
		return NULL;
	}
	/*Create iterator object that points to the head of the list*/
	new_list->head = (dlist_iter_ty)malloc(sizeof(struct dnode));
	/*Check if the allocation failed*/
	if (NULL == new_list->head)
	{
		/*free the list and list now points to null and function returns null*/
		free(new_list);
		new_list = NULL;
		
		return NULL;
	}
	/*Create iterator object that points to the tail of the list*/
	new_list->tail = (dlist_iter_ty)malloc(sizeof(struct dnode));
	
	if (NULL == new_list->tail)
	{
		free(new_list->head);
		new_list->head = NULL;
		
		free(new_list);
		new_list = NULL;

		return NULL;
	}
	/*Initialize the data of the tail and head nodes to be null */
	new_list->tail->data = NULL;
	new_list->head->data = NULL;
	
	/*tail next node will point on null, tail prev node will point
	 on the head of the list*/
	new_list->tail->next_node = NULL;
	new_list->tail->prev_node = new_list->head;
	/*head next node will point on the end of the list , head prev node will
	 point to null*/
	new_list->head->next_node = new_list->tail;
	new_list->head->prev_node = NULL;
	/*return the new list that created*/
	return new_list;
	
}

/******************************************************************************/
void DListDestroy(dlist_ty *dlist)
{
	  /*declare two iterators to current node and previous node*/
    dlist_iter_ty current_node = NULL;
    dlist_iter_ty prev_node = NULL;
    
    /*assert dlist to self debag*/
    assert(NULL != dlist);
    
    /*init current iterator to head of list*/
    current_node = dlist->head;
    
    /*while current node is valid node:*/
    while (NULL != current_node)
    {
        /*assign prev with current.*/
        prev_node = current_node;
        /*move to next node*/
        current_node = current_node->next_node;
        /*free prev node*/
        free(prev_node);
    }
    
    current_node = NULL;
    /*free dlist*/
    free(dlist);
    /*prevent dangling*/
    dlist = NULL;
}

/******************************************************************************/
dlist_iter_ty DListBegin(const dlist_ty *list)
{
	assert(NULL != list);
	/*returns the valid head of the list*/ 
	return DListNext(list->head);

}

/******************************************************************************/
dlist_iter_ty DListNext(const dlist_iter_ty iter)
{
	assert(NULL != iter);
	/*returns the next node of the iterator */ 
	return iter->next_node;
}

/******************************************************************************/
dlist_iter_ty DListPrev(const dlist_iter_ty iter)
{
	assert(NULL != iter);
	/*returns the prev node of the iterator */ 
	return iter->prev_node;
}

/******************************************************************************/
dlist_iter_ty DListEnd(const dlist_ty *list)
{
	assert(NULL != list);
	/*returns the tail of the list*/ 
	return list->tail;

}

/******************************************************************************/
dlist_iter_ty DListInsert(void *data, dlist_iter_ty iter)
{
	/*Declare on iterator item*/
	dlist_iter_ty item = NULL;
	
	assert(NULL != iter);
	assert(NULL != data);
	/*allocate to item memory */
	item = (dlist_iter_ty)malloc(sizeof(struct dnode));
	
	if (NULL == item)
	{
		/*if the allocation failed returns the last node*/
		while (NULL != iter)
		{
			iter = DListNext(iter);
		}
		
		return iter; 
	}
	/*item gets data*/
	item->data = data;
	/*item previous node gets the iter previous node*/
	item->prev_node = DListPrev(iter);
	/*item next node gets the iter node*/
	item->next_node = iter;
	/*iter previous node get the next node be item*/
	iter->prev_node->next_node = item;
	/*iter previous node get item*/
	iter->prev_node = item;

	return item;
    
}


/******************************************************************************/
dlist_iter_ty DListSet(const dlist_iter_ty iter, void *data)
{
	assert(NULL != iter);
	assert(NULL != data);
	/*set data to the iterator*/
	iter->data = data;
	/*return iter*/
	return iter;

}
/******************************************************************************/
void *DListGet(const dlist_iter_ty iter)
{
	assert(NULL != iter);
	/*return the data of the iterator*/
	return iter->data;
}

/******************************************************************************/

dlist_iter_ty DListPushFront(void *data, dlist_ty *list)
{	
	/*declare in front node*/
	dlist_iter_ty front_node = NULL;

	assert(NULL != list);
	assert(NULL != data);
	/*front node gets the first  valid node*/
	front_node = DListBegin(list);

	/*insert the node as the other nodes and
	 return the iterator(front_node)*/
    return DListInsert(data, front_node);
}

/******************************************************************************/
dlist_iter_ty DListPushBack(void *data, dlist_ty *list)
{
	assert(NULL != list);
	assert(NULL != data);
	
	/* DListInsert to the tail and return itertor for it*/
	return DListInsert(data, DListEnd(list));
}
/******************************************************************************/
void *DListPopBack(dlist_ty *list)
{
	/*Declare on node_to_remove iterator*/
	dlist_iter_ty node_to_remove = NULL;
	/*pointer to data to return*/
	void *data = NULL;
	
	assert(NULL != list);
	
	/*node_to_remove gets the last node before the dummy in the end of the list*/
	node_to_remove =  DListPrev(DListEnd(list));
	
	/*data gets node_to_remove last node before dummy data*/
	data = node_to_remove->data;

	/*remove node_to_remove*/
	DListRemove(node_to_remove);

	/*return data*/
	return data;
	
}
/******************************************************************************/
void *DListPopFront(dlist_ty *list)
{	
	/*Declare on runner iterator*/
	dlist_iter_ty node_to_remove = NULL;
	/*pointer to data to return*/
	void *data = NULL;
	
	assert(NULL != list);
	
	/*node_to_remove get the first valid node*/ 
	node_to_remove = DListBegin(list);
	/*data gets node_to_remove data*/
	data = node_to_remove->data;
	
	/*remove runner*/
	DListRemove(node_to_remove);
	
	return data;
}

/******************************************************************************/
size_t DListSize(const dlist_ty *list)
{
	/*declart on iterator*/
	dlist_iter_ty iter = NULL;
	/*daclare on counter- count the nodes*/
	size_t counter = 0;
	
	assert(NULL != list);
	/*iterator gets the first valid node.*/
	
	iter = DListBegin(list);
	
	/*while the iterator not reach the end of the list the counter increment by
	one*/
	while (DListEnd(list) != iter)
	{
		++counter;
		iter = DListNext(iter);
	}
	/*return the counter*/
	return counter;
}

/******************************************************************************/
int DListIsSameIter(const dlist_iter_ty iter1, const dlist_iter_ty iter2)
{

	assert(NULL != iter1);
	assert(NULL != iter2);
	
	return (iter1 == iter2);
}

/******************************************************************************/
dlist_iter_ty DListRemove(dlist_iter_ty iter)
{
	/*declare on 2 iterators to next node of iter and prev*/
	dlist_iter_ty prev_node_it = NULL;
	dlist_iter_ty next_node_it = NULL;
	
	assert(NULL != iter);
	/*init the iterators to get the prev and next of the iterators*/
	
	next_node_it = DListNext(iter);
	prev_node_it = DListPrev(iter);
	
	/*prev iter node next node gets the next iter node*/
	prev_node_it->next_node = next_node_it;
	/*next iter node prev node gets the prev iter node*/
	next_node_it->prev_node = prev_node_it;
	
	/*free iterator*/
	free(iter);
	iter = NULL;
	
	return next_node_it;
}

/******************************************************************************/
dlist_iter_ty DListForEach(dlist_iter_ty from, dlist_iter_ty to, 
											  cmd_func_ty command, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != command);
	/*assert(NULL != param);*/
	
	/*while from and to iterators are not equal*/
	while (FALSE == DListIsSameIter(from, to))
	{
		/*if failure is the result of the command function returns from in the
		where failure happaned*/
		if (FAILURE == command(from->data, param))
		{
			return from;
		}
		
		from = DListNext(from);
	}
	/*return from*/
	return from; 
}
/******************************************************************************/
dlist_iter_ty DListFind(dlist_iter_ty from, dlist_iter_ty to, 
							                match_func_ty is_match, void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != is_match);
	assert(NULL != param);
	
	/*while from and to iterators are not equal*/
	while (FALSE == DListIsSameIter(from, to))
	{
		/*if there is a match  between the from iterator data and
		  the paramת return the first iterator(from) that match the criterion*/
		if (TRUE == is_match(from->data, param))
		{
			return from;
		}

		from = DListNext(from);
	}
	
	/*If not found matching iterator,
	returns the last node before the end of the list (the one before the dummy)*/

	
	
	return from;
}	
/******************************************************************************/
int DListMultiFind(dlist_ty *list_src, dlist_ty *list_out,
										    match_func_ty is_match, void *param)
{
	/*Declare ion 2 iterators from_itr and to_itr*/
	dlist_iter_ty from_itr = NULL;
	dlist_iter_ty to_itr = NULL;
	
	assert(NULL != list_src);
	assert(NULL != list_out);
	assert(NULL != is_match);
	assert(NULL != param);
	
	/*from_itr gets the first valid node in list_src */
	from_itr = DListBegin(list_src);
	/*to_itr gets the last node  of list_src*/
	to_itr = DListEnd(list_src);
	
	/*while from_itr and to_itr are not the same*/
	while (FALSE == DListIsSameIter(from_itr, to_itr))
	{
		/*find from_itr according the is_match criterion*/
		from_itr = DListFind(from_itr, to_itr, is_match, param);
		
		/*If src didn't reach to end of the list push from_itr node to list_out 
			and from_itr gets his next node*/
		if (FALSE  == DListIsSameIter(DListEnd(list_src) ,from_itr))
		{
			DListPushBack(DListGet(from_itr), list_out);
			
			if (NULL == DListPushBack(DListGet(from_itr), list_out))
			{
				return FAILURE;
			}
			from_itr = DListNext(from_itr);
		}
	}
	
	/*return SUCCESS*/
	return (SUCCESS);

}

/******************************************************************************/

dlist_iter_ty DListSplice(dlist_iter_ty from_src, dlist_iter_ty to_src, 
															dlist_iter_ty dest)
{
	/*declare  3 iterators*/
	dlist_iter_ty prev_iter_dest = NULL;
	dlist_iter_ty tail_src = NULL;
	dlist_iter_ty src_list_ptr = NULL;
	
	assert(NULL != from_src);
	assert(NULL != to_src);
	assert(NULL != dest);
	
	/*prev_iter_dest gets the prev node of dest*/
	prev_iter_dest = DListPrev(dest);	
	/*src_list_ptr gets prev node of from_src*/
	src_list_ptr = DListPrev(from_src);
	/*connect between prev_iter_dest next node to from_src*/
	prev_iter_dest->next_node = from_src;
	/*connect between from_src prev node to prev_iter_dest */
	from_src->prev_node = prev_iter_dest; 
	
	/*tail_src gets the prev node of to_src*/
	tail_src = DListPrev(to_src);
	/*connect between tail_src next next_node to dest*/
	tail_src->next_node = dest;
	/*connect between dest prev node to tail_src*/
	dest->prev_node = tail_src;
	
	/*connect  src_list_ptr nexy node and src list*/
	src_list_ptr->next_node = to_src;
	to_src->prev_node = src_list_ptr;
	
	/*return from_src*/
	return from_src;
}

/******************************************************************************/
int DListIsEmpty(dlist_ty *dlist)
{
	
	assert(NULL != dlist);
	
	return (DListSize(dlist) == EMPTY);
}

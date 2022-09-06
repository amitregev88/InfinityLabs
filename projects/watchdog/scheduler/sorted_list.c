/******************************************************************************/
/*	Project:	Sorted Array											  	  */
/*	File:		Sorted Array.c												  */
/*	Date: 		15.06.2022													  */
/*	Name: 		Sapir 														  */
/*	Reviewer:	Amit														  */
/*	Version: 	1.00														  */
/******************************************************************************/
#include <assert.h> /*assert()*/
#include <stdlib.h> /*malloc(), free()*/

#include "dlist.h" /* DListCreate(), DListNext(), DListPrev(), DListGet()
											 DListInsert(),DListIsSameIter()*/
#include "sorted_list.h"

enum {FALSE = 0, TRUE = 1};
enum {SUCCESS = 0, FAILURE = 1};

struct srlist
{
    dlist_ty *list;
    match_func_ty is_match;
};

/******************************************************************************/
srlist_ty *SortedListCreate(match_func_ty is_match)
{
	/*Create a new list*/
	srlist_ty *sorted_list = (srlist_ty*)malloc(sizeof(struct srlist));
	/*Check if the allocation failed, if failed retur null*/
	if (NULL == sorted_list)
	{
		return  NULL;
	}
	/*sorted_list->list gets dlist*/
	sorted_list->list = DListCreate();
	
	if (NULL == sorted_list->list)
	{
		free(sorted_list);
		sorted_list = NULL;
		
		return sorted_list;
	}
	/*sorted list match function gets is_match*/
	sorted_list->is_match = is_match;
	/*return sorted_list*/
	return sorted_list;
}	

/******************************************************************************/
void SortedListDestroy(srlist_ty *list)
{
	assert(NULL != list);
	/*destroy the list*/
	DListDestroy(list->list);
	
	list->list = NULL;
	/*free the list*/
	free(list);
	list = NULL;
}
/******************************************************************************/
srlist_iter_ty SortedListBegin(const srlist_ty *list)
{
	/* init iter*/
	srlist_iter_ty iter = {0}; 
	
	assert(NULL != list);
	DEBUG_ONLY(iter.list = (srlist_ty*) list;)
	/*internal_iter of iter gets the beggining of the dlist in list*/
	iter.internal_iter = DListBegin(list->list);

	
	return iter;
}

/******************************************************************************/
srlist_iter_ty SortedListNext(srlist_iter_ty iter)
{
	 assert(NULL != iter.internal_iter);
	
	/*internal_iter of iter gets the next iterator of the dlist in list*/
	iter.internal_iter = DListNext(iter.internal_iter);
	
	return iter;
}

/******************************************************************************/
srlist_iter_ty SortedListPrev(srlist_iter_ty iter)
{
	assert(NULL != iter.internal_iter);
	
	/*internal_iter of iter gets the prev iterator of the dlist in list*/
	iter.internal_iter = DListPrev(iter.internal_iter);
	
	return iter;
}

/******************************************************************************/
srlist_iter_ty SortedListEnd(const srlist_ty *list)
{
	/* init iter*/
	srlist_iter_ty iter = {0}; 
	
	assert(NULL != list);
	DEBUG_ONLY(iter.list = (srlist_ty*) list;)
	
	/*internal_iter of iter gets the end of the dlist in list*/
	iter.internal_iter = DListEnd(list->list);
	
	return iter;
}

/******************************************************************************/
srlist_iter_ty SortedListInsert(void *data, srlist_ty *list)
{
	/* init iter*/
	srlist_iter_ty iter = {0}; 
	dlist_iter_ty dlist_iter = NULL; 
		
	assert(NULL != list);
	assert(NULL != data);
	DEBUG_ONLY(iter.list = (srlist_ty*) list;)
	/*dlist_iter gets the first valid item in the list*/
	dlist_iter = DListBegin(list->list);
	
	/*while the function is not true and the iter doesn't reach the end of the 
		list dlist gets his next*/	
	while (NULL != DListNext(dlist_iter) &&
							FALSE == list->is_match(DListGet(dlist_iter),data))
	{
		dlist_iter = DListNext(dlist_iter);
	}
	
	iter.internal_iter = DListInsert(data,dlist_iter);
	
	return iter;
}

/******************************************************************************/
srlist_iter_ty SortedListRemove(srlist_iter_ty iter)
{
	assert(NULL != iter.internal_iter);
	/*internal iter of iter gets the next iter after the one that removes*/
	iter.internal_iter = DListRemove(iter.internal_iter);
	
	return iter;
}

/******************************************************************************/
void *SortedListGet(const srlist_iter_ty iter)
{
	assert(NULL != iter.internal_iter);
	
	return DListGet(iter.internal_iter);
}

/******************************************************************************/
void *SortedListPopFront(srlist_ty *list)
{
	assert(NULL != list);
	
	return DListPopFront(list->list);
}

/******************************************************************************/
void *SortedListPopBack(srlist_ty *list)
{
	assert(NULL != list);
	
	return DListPopBack(list->list);
}

/******************************************************************************/
void SortedListMerge(srlist_ty *src, srlist_ty *dest)
{

	dlist_iter_ty src_from_iter = NULL; 
	dlist_iter_ty dest_iter = NULL; 
	dlist_iter_ty src_to_iter = NULL; 
	
	assert(NULL != src);
	assert(NULL != dest);
	
	src_from_iter = DListBegin(src->list);
	dest_iter = DListBegin(dest->list);
	src_to_iter = DListNext(src_from_iter);
	
	while (FALSE == SortedListIsEmpty(src))
	{
		while ((DListEnd(dest->list)!= dest_iter) && (FALSE == dest->is_match
						 (DListGet(dest_iter) ,(void*)DListGet(src_from_iter))))
		{
			 dest_iter = DListNext(dest_iter);
		}	
		
		DListSplice(src_from_iter, src_to_iter ,dest_iter);
		src_from_iter = src_to_iter;
		src_to_iter = DListNext (src_to_iter);
	}
	
	SortedListDestroy(src);
	
	src = NULL;
}

/******************************************************************************/
srlist_iter_ty SortedListFind(srlist_ty *list, srlist_iter_ty from,
                                   srlist_iter_ty to, const void *to_find)
{
	dlist_iter_ty dlist_iter = NULL; 
	
	assert(NULL != list);
	assert(NULL != from.internal_iter);
	assert(NULL != to.internal_iter);
	assert(NULL != to_find);
	DEBUG_ONLY(assert(to.list == from.list);)
		
	dlist_iter = DListFind(from.internal_iter, to.internal_iter, 
												list->is_match, (void*)to_find);
	
	from.internal_iter = dlist_iter;

	return from;
}

/******************************************************************************/
srlist_iter_ty SortedListFindIf(match_func_ty is_match,
 		srlist_iter_ty from, srlist_iter_ty to, const void *to_find)
{
	dlist_iter_ty dlist_iter = NULL; 
		
	assert(NULL != is_match);
	assert(NULL != from.internal_iter);
	assert(NULL != to.internal_iter);
	assert(NULL != to_find);
	DEBUG_ONLY(assert(to.list == from.list);)
	
	dlist_iter = DListFind(from.internal_iter, to.internal_iter, 
													  is_match, (void*)to_find);
	
	from.internal_iter = dlist_iter;

	return from;
}
 		
/******************************************************************************/
int SortedListIsEmpty(const srlist_ty *list)
{
	assert(NULL != list);
	
	return (DListIsEmpty(list->list));
}

/******************************************************************************/
int SortedListIsSameIter(const srlist_iter_ty iter1, const srlist_iter_ty iter2)
{
	assert(NULL != iter1.internal_iter);
	assert(NULL != iter2.internal_iter);
	
	return(DListIsSameIter(iter1.internal_iter,iter2.internal_iter));
}


/******************************************************************************/
size_t SortedListSize(const srlist_ty *list)
{
	assert(NULL != list);

	return (DListSize(list->list));
}


/******************************************************************************/
srlist_iter_ty SortedListForEach(srlist_iter_ty from, srlist_iter_ty to, 
											cmd_func_ty command, void *param)
{	
	dlist_iter_ty dlist_iter = NULL; 
	
	assert(NULL != from.internal_iter);
	assert(NULL != to.internal_iter);
	assert(NULL != command);
	assert(NULL != param);
	DEBUG_ONLY(assert(to.list == from.list);)
	
	dlist_iter = DListForEach(from.internal_iter ,to.internal_iter,
																command, param);
	from.internal_iter = dlist_iter;
	
	return from;
}


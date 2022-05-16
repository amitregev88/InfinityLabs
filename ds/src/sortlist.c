/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 04.09.22
* OL124 Sorted List (base on dlinked list)
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include <assert.h>/* assert*/
#include "dlinked_list.h" 
#include "sortlist.h"

static int IsInSameSList(const sortlist_iter_ty from, const sortlist_iter_ty to);

struct sort_list
{
    dlist_ty *list;
    compare_ty compare;
};


/*************************************************************************************
*Creates Sorted list - return pointer to SortList 
**************************************************************************************/
sortlist_ty *SortLCreate(compare_ty compare)
{

	sortlist_ty *new_list = NULL;
	assert(NULL != compare);
	
	new_list = (sortlist_ty *)malloc(sizeof(sortlist_ty));
	if (NULL == new_list)
	{
		return NULL;
	}
	
	new_list->list = DListCreate();	
	if (NULL == new_list->list)
	{
		/*clean up*/
		free(new_list);
		return NULL;
	}
	
	new_list->compare = compare;
	return new_list;
}

/*************************************************************************************
*Delete Sorted List 
**************************************************************************************/
void SortLDestroy(sortlist_ty *sortlist)
{
	 DListDestroy(sortlist->list);
	 free(sortlist);

}


/*************************************************************************************
* Add node to the sorted list return iter to this node if fail -> iter.node=NULL
**************************************************************************************/
sortlist_iter_ty SortLInsert(sortlist_ty *sortlist, void *data)

{

	sortlist_iter_ty iter = {NULL};
	iter = SortLBegin(sortlist);
	
	
	
	assert(NULL != sortlist);
	assert(NULL != sortlist->compare);
	assert(NULL != data);

	iter = SortLBegin(sortlist);
	
	if(1 == SortLIsEmpty(sortlist))
	{
		
		iter.node = DListInsert(iter.node, data);
		return iter;
		
		
	
	}
		
	else
	{
		
		while (!SortLIsSameIter(iter, SortLEnd(sortlist)))
		{
			
			if (sortlist->compare(data, SortLGetData(iter)) <= 0)
			{		
				iter.node = DListInsert(iter.node, data);	
				return iter;				
			}
		
		iter = SortLGetNext(iter);
		
		}
	}
	
	iter.node = DListInsert(iter.node, data);
	
	return iter;
		
	
}
		
		
		
void SortLRemove(sortlist_iter_ty to_remove)
{
	
	assert(NULL != to_remove.node);
	
	DListRemove(to_remove.node);
	
}


/*************************************************************************************
* --- Size --- returns the size of the Sorted Linked List ----- O(n)
**************************************************************************************/
size_t SortLSize(const sortlist_ty *sortlist)
{

	assert(NULL != sortlist);
	
	return DListSize(sortlist->list);

}

/*************************************************************************************
* --- SortLIsEmpty --- returns 1 in case is empty or -0 other case ---- O(1)
**************************************************************************************/
int SortLIsEmpty(const sortlist_ty *sortlist)
{
	assert(NULL != sortlist);
	return DListIsEmpty(sortlist->list);
	
}

/*************************************************************************************
* --- SortLBegin --- returns first iter of sorted list
**************************************************************************************/
sortlist_iter_ty SortLBegin(const sortlist_ty *sortlist)
{
	sortlist_iter_ty begin = {NULL};
	
	assert(NULL != sortlist);
	
	begin.node = DListBegin(sortlist->list);
	
	return begin;
}

/*************************************************************************************
* --- SortLEnd --- returns last iter of sorted list
**************************************************************************************/
sortlist_iter_ty SortLEnd(const sortlist_ty *sortlist)
{
	sortlist_iter_ty end = {NULL};
	
	assert(NULL != sortlist);
	
	end.node = DListEnd(sortlist->list);
	
	return end;
}


/*************************************************************************************
* --- SortLGetPrev --- returns previous iter of given iter
**************************************************************************************/
sortlist_iter_ty SortLGetPrev(const sortlist_iter_ty iter)
{


	sortlist_iter_ty prev = {NULL};
	
	assert(NULL != iter.node);
	
	prev.node = DListGetPrev(iter.node);
	
	return prev;

}

/*************************************************************************************
* --- SortLGetNext --- returns next iter of given iter
**************************************************************************************/
sortlist_iter_ty SortLGetNext(const sortlist_iter_ty iter)
{


	sortlist_iter_ty next = {NULL};
	
	assert(NULL != iter.node);
	
	next.node = DListGetNext(iter.node);
	
	return next;

}

/*************************************************************************************
* --- SortLGetData --- returns data of given iter
**************************************************************************************/
void *SortLGetData(const sortlist_iter_ty iter)
{
	assert(NULL != iter.node);
	
	return DListGetData(iter.node);
}

/*************************************************************************************
* --- SortLIsSameIter --- returns 1 if the same, 0 otherwise
**************************************************************************************/
int SortLIsSameIter(const sortlist_iter_ty iter_1, const sortlist_iter_ty iter_2)
{
	assert(NULL != iter_1.node);
	assert(NULL != iter_2.node);
	
	return (DListIsSameNode(iter_1.node, iter_2.node));
}

/*************************************************************************************
* --- SortLPopBack --- remove the last iter from sorted list and return its data
**************************************************************************************/
void *SortLPopBack(sortlist_ty *sortlist)
{
	assert(NULL != sortlist);
	
	return DListPopBack(sortlist->list);

}

/*************************************************************************************
* --- SortLPopFront --- remove the first iter from sorted list and return its data
**************************************************************************************/
void *SortLPopFront(sortlist_ty *sortlist)
{
	assert(NULL != sortlist);
	
	return DListPopFront(sortlist->list);

}

/*************************************************************************************
* --- SortLForEach --- return 0 in case of success or 1 failure 
**************************************************************************************/
int SortLForEach(sortlist_iter_ty from, const sortlist_iter_ty to, int (*action)(void *data, const void *param), const void *param)
{
	assert(NULL != from.node);
	assert(NULL != to.node);
	assert(NULL != action);
	assert(IsInSameSList(from, to));
	
	
	return DListForEach(from.node, to.node, action, param);
}

/*************************************************************************************
* --- Find --- Finds the iter with data==param using  comparison function inside struct sort_list 
**************************************************************************************/
sortlist_iter_ty SortLFind(const sortlist_ty *sortlist, const sortlist_iter_ty from, const sortlist_iter_ty to, const void *param)
{
	sortlist_iter_ty iter = from;
	
	
	assert(NULL != sortlist);
	assert(NULL != sortlist->compare);
	assert(NULL != from.node);
	assert(NULL != to.node);
	assert(NULL != param);
	assert(IsInSameSList(from, to));
	
	
	while (!SortLIsSameIter(iter, to))
	{
		if (sortlist->compare(SortLGetData(iter),param) == 0)
		{
			return iter;
		}
		
		iter = SortLGetNext(iter);
	}
	
	iter.node = NULL;
	
	return iter;
	
}

/*************************************************************************************
* --- Find --- Finds the iter using USER's comparison function is_match 
**************************************************************************************/
sortlist_iter_ty SortLFindIf(const sortlist_iter_ty from, const sortlist_iter_ty to, int (*is_match)(const void *data, const void *param), const void *param)
{
	sortlist_iter_ty iter = {NULL};
	
	
	assert(NULL != from.node);
	assert(NULL != to.node);
	assert(NULL != is_match);
	assert(NULL != param);
	assert(IsInSameSList(from, to));
	
	
	
	iter.node = DListFind(from.node, to.node, is_match, param);
	
	return iter;

}
/*************************************************************************************
* --- SortLMerge --- Merge source list  into dest list, source list will be empty,  
**************************************************************************************/

void SortLMerge(sortlist_ty *_dest, sortlist_ty *_source)
{
	
	sortlist_iter_ty iter_dest = {NULL};
	
	sortlist_iter_ty src_to_iter = {NULL};
	
	int flag = 0;
	
	
	assert(NULL != _dest);
	assert(NULL != _source);
	assert(NULL != _source->compare);
	
	
	iter_dest = SortLBegin(_dest);
	
	src_to_iter = SortLGetNext(SortLBegin(_source));
	
		
	while (!SortLIsSameIter(SortLEnd(_dest),iter_dest))
	{
	
		
		while (!SortLIsSameIter(src_to_iter, SortLEnd(_source)) && (_source->compare(SortLGetData(iter_dest), SortLGetData(src_to_iter)) >= 0))
		{
			src_to_iter = SortLGetNext(src_to_iter);
			flag = 1;
		}
				
			
			
		if (flag)
		{
			DListSplice(iter_dest.node ,SortLBegin(_source).node , src_to_iter.node);

			flag = 0;
		}
		
		iter_dest = SortLGetNext(iter_dest);
		
	}
	
	if (!SortLIsEmpty(_source))
	{
		DListSplice(iter_dest.node ,SortLBegin(_source).node , SortLEnd(_source).node);
	}
}
	
		
		
			
	
static int IsInSameSList(const sortlist_iter_ty from, const sortlist_iter_ty to)
{
	sortlist_iter_ty iter = from;

	while (iter.node != NULL)
	{
		if (SortLIsSameIter(iter, to))
		{
			return 1;
		}
		
	iter = SortLGetNext(iter);
	
	}
	
	return 0;
}
















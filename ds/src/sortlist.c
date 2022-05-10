/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 04.09.22
* OL124 Sorted List (base on dlinked list)
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include "dlinked_list.h" 
#include "sortlist.h"
#include <assert.h>

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
	assert(NULL != compare);	

	sort_list *new_list = (sort_list *)malloc(sizeof(sort_list));
	
	if (NULL == new_list)
	{
		printf("Memory allocation error\n");
		return NULL;
	}
	
	assert(NULL != compare);
	
	new_list->list = DListCreate();
	
	if (NULL == new_list->list)
	{
		free(new_list);
		return NULL;
	}
	
	new_list.compare = compare;
	
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
* Add iter to the sorted list Success = 0, Fail = 1
**************************************************************************************/
int SortLInsert(sortlist_ty *sortlist, void *data);
{

	sortlist_iter_ty iter = NULL;
	iter = SortLBegin(sortlist);
	
	
	
	assert(NULL != sortlist);
	assert(NULL != sortlist->compare);
	assert(NULL != data);

	iter = SortLBegin(sortlist);
	
	if(1 == SortIsEmpty(sortlist))
	{
		
		if (NULL != DListInsert(SortLBegin(sortlist), data))
		{
			return 0;
		}
			
		else
		{
			return 1;
		}
	}
		
	else
	{
		
		while (SortLIsSmaeIter(iter, SortLEnd(sortlist)) == 0)
		{
			
			if ((sortlist->compare(data, SortGetData(iter) <= 0)
			{		
				if (NULL != DListInsert(iter, data))
				{	
					return 0;
				}
				
				else 
				{
					return 1;
				}
			}
		}
	}
}
		
		
		
void SortLRemove(sortlist_iter_ty to_remove)
{
	
	assert(NULL != to_remove);
	
	DListRemove(to_remove->node);
	
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
	sortlist_iter_ty begin = NULL;
	
	assert(NULL != sortlist);
	
	begin->node = DListBegin(sortlist->list);
	
	return begin;
}

/*************************************************************************************
* --- SortLEnd --- returns last iter of sorted list
**************************************************************************************/
sortlist_iter_ty SortLEnd(const sortlist_ty *sortlist)
{
	sortlist_iter_ty end = NULL;
	
	assert(NULL != sortlist);
	
	end->node = DListEnd(sortlist->list);
	
	return end;
}


/*************************************************************************************
* --- SortLGetPrev --- returns previous iter of given iter
**************************************************************************************/
sortlist_iter_ty SortLGetPrev(const sortlist_iter_ty iter)
{


	sortlist_iter_ty prev = NULL;
	
	assert(NULL != iter);
	
	prev->node = DListGetPrev(sortlist->list);
	
	return prev;

}

/*************************************************************************************
* --- SortLGetNext --- returns next iter of given iter
**************************************************************************************/
sortlist_iter_ty SortLGetNext(const sortlist_iter_ty iter)
{


	sortlist_iter_ty next = NULL;
	
	assert(NULL != iter);
	
	next->node = DListGetNext(sortlist->list);
	
	return next;

}

/*************************************************************************************
* --- SortLGetData --- returns data of given iter
**************************************************************************************/
void *SortLGetData(const sortlist_iter_ty iter)
{
	assert(NULL != iter);
	
	return DListGetData(iter->node);
}

/*************************************************************************************
* --- SortLIsSameIter --- returns 1 if the same, 0 otherwise
**************************************************************************************/
int SortLIsSameIter(const sortlist_iter_ty iter_1, const sortlist_iter_ty iter_2)
{
	assert(NULL != iter_1);
	assert(NULL != iter_2);
	
	return (DListIsSameNode(iter_1->node, iter_2->node));
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
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);
	
	return DListForEach(from->node, to->node, action);
}

/*************************************************************************************
* --- Find --- Finds the iter with data==param using  comparison function inside struct sort_list 
**************************************************************************************/
sortlist_iter_ty SortLFind(const sortlist_ty *sortlist, const sortlist_iter_ty from, const sortlist_iter_ty to, const void *param)
{
	assert(NULL != sortlist);
	assert(NULL != sortlist->compare);
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != param);
	
	sortlist_iter_ty iter = NULL;
	
	iter->node = DListFind(from->node, to->node, sortlist->compare, param);
	
	return iter;
}

/*************************************************************************************
* --- Find --- Finds the iter using USER's comparison function is_match 
**************************************************************************************/
 SortLFindIf(const sortlist_iter_ty from, const sortlist_iter_ty to, int (*is_match)(const void *data, const void *param), const void *param)
{
	assert(NULL != from);
	assert(NULL != to);
	assert(NULL != action);
	assert(NULL != param);
	
	sortlist_iter_ty iter = NULL;
	
	
	iter->node = DListFind(from->node, to->node, is_match, param);
	
	return iter;

}
/*************************************************************************************
* --- SortLMerge --- Merge source list  into dest list, source list will be empty,  
**************************************************************************************/
void SortLMerge(sortlist_ty *_dest, sortlist_ty *_source)
{
	assert(NULL != _dest);
	assert(NULL != _source);
	assert(NULL != _source->compare);

	
	sortlist_iter_ty iter_dest = {NULL};
	
	sortlist_iter_ty src_from_iter = {NULL};
	
	sortlist_iter_ty src_to_iter = {NULL};
	
	int flag = 0;
	
	iter_dest = SortLBegin(_dest);
	
	src_from_iter = SortLBegin(_source);
	
	src_to_iter = SortLBegin(_source);
	
		
	while (SortLIsSameIter(SortLEnd(_dest->list),iter_dest))
	{
	
		
		while (!SortLIsSameIter(src_to_iter, SortLEnd(src_to_iter)))
		{
		
		
			if (_source->compare(SortLGetData(iter_dest), SortLGetData(src_to_iter)) >= 0)
			{
				src_to_iter = SortLGetNext(src_to_iter);
				
				flag = 1;
				
			}
			
			else if (flag)
			{
				DListSplice(iter_dest.node ,src_from_iter.node , src_to_iter.node);
				src_from_iter = src_to_iter;
				flag = 0;
			}
		}
		
		if (flag)
		{
			DListSplice(iter_dest.node ,src_from_iter.node , src_to_iter.node);
			flag = 0;
		}
		
		iter_dest = SortLGetNext(iter_dest);
	}
		
	if (!SortLIsSameIter(src_to_iter, SortLEnd(src_to_iter)))
	{
		DListSplice(iter_dest.node ,src_from_iter.node , SortLEnd(_source));
	}
		
	
}
		
		
			
	
	
	














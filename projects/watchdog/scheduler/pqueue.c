/******************************************************************************/
/*	Project:	pqueue													  	  */
/*	File:		pqueue.c													  */
/*	Date: 		21.06.2022													  */
/*	Name: 		Sapir 														  */
/*	Reviewer:	Boaz														  */
/*	Version: 	1.00														  */
/******************************************************************************/
#include <assert.h> /*assert*/
#include <stdlib.h> /*malloc, free*/

#include "sorted_list.h"/* SortedListCreate(), SortedListDestroy(), 
SortedListPopFront(),SortedListBegin(), SortedListGet(),  SortedListIsSameIter*/
#include "pqueue.h"

/******************************************************************************/
enum {SUCCESS = 0, FAILURE };
enum {FALSE = 0, TRUE = 1};

struct pque			
{				
	srlist_ty *pque; 
};	
				
/******************************************************************************/
pque_ty *PQCreate(is_higher_priority is_higher)
{
	pque_ty *new_pque = (pque_ty*)malloc(sizeof( pque_ty));
	
	if (NULL == new_pque)
	{
		return NULL;
	}
	
	new_pque->pque = SortedListCreate(is_higher);
	
	if(NULL == new_pque->pque)
	{
		free(new_pque);
		new_pque = NULL;
		
		return NULL;
	}
	
	return new_pque;

}

/******************************************************************************/
void PQDestroy(pque_ty *pque)
{
	assert(NULL != pque);
	
	SortedListDestroy(pque->pque);
	
	free (pque);
	
	pque = NULL;
}

/******************************************************************************/
int PQEnqueue(pque_ty *pque, void *data)
{
	assert(NULL != pque);
	assert(NULL != data);
		
	if (FALSE == SortedListIsSameIter(SortedListEnd(pque->pque) ,
										    SortedListInsert(data, pque->pque)))
	{
		return SUCCESS;
	}
	
	return FAILURE;
}

/******************************************************************************/
void *PQDequeue(pque_ty *pque)
{
	assert(NULL != pque);
	
	return (SortedListPopBack(pque->pque));
}

/******************************************************************************/
void *PQPeek(const pque_ty *pque)
{
	assert(NULL != pque);
	
	return (SortedListGet(SortedListPrev(SortedListEnd(pque->pque))));
}

/******************************************************************************/
int PQIsEmpty(const pque_ty *pque)
{
	assert(NULL != pque);
	
	return (SortedListIsEmpty(pque->pque));
}

/******************************************************************************/
size_t PQSize(const pque_ty *pque)
{
	assert(NULL != pque);
	
	return SortedListSize(pque->pque);
}

/******************************************************************************/
void PQClear(pque_ty *pque)
{
	assert(NULL != pque);
	
	while (FALSE == SortedListIsEmpty(pque->pque))
	{
    	SortedListPopBack(pque->pque);
	}
}

/******************************************************************************/
void *PQErase(pque_ty *pque, match_func_ty is_match, void *param)
{
	srlist_iter_ty from  = {NULL};
	srlist_iter_ty to = {NULL};
    void *data = NULL;
    
	assert(NULL != pque);
	assert(NULL != is_match);
	assert(NULL != param);
	
	from = SortedListBegin(pque->pque);
	to = SortedListEnd(pque->pque);
	
	from = SortedListFindIf(is_match, from, to, param);
	
	if (TRUE == SortedListIsSameIter(from, to))
	{
		return NULL;
	}
	
	data = SortedListGet(from);
	SortedListRemove(from);
	
	return data;	
}

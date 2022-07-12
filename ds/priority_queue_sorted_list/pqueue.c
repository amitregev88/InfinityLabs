/*************************************************************************************
* Name: Amit Regev 
* Reviewer: Alexander Bor
* Date: 05.12.22
* OL124 Priority Queue project (base on Sorted List)
*************************************************************************************/

#include <assert.h>	/* assert*/
#include <stdlib.h>	/* malloc*/
#include <assert.h>	/* assert*/
#include "pqueue.h"
#include "sortlist.h"


struct pqueue
{
    sortlist_ty *list;

};


/*Creates Queue - return pointer to Que */
pqueue_ty *PQCreate(int (*cmp)(const void *, const void *))
{

	pqueue_ty *new_pqueue = NULL;
	assert(NULL != cmp);
	
	new_pqueue = (pqueue_ty *)malloc(sizeof(pqueue_ty));	
	if (NULL == new_pqueue)
	{
		return NULL;
	}
	
	new_pqueue->list = SortLCreate(cmp);
	if (NULL == new_pqueue->list)
	{
		/*clean up*/
		free(new_pqueue);
		return NULL;
	}
	
	return new_pqueue;
}



/*Delete PQue */
void PQDestroy(pqueue_ty *pqueue)
{
	 SortLDestroy(pqueue->list);
	 pqueue->list = NULL;
	 free(pqueue); 
}



/*Get node from front of the queue - return  data from node */
void *PQDeQueue(pqueue_ty *pqueue)
{
	void *data = NULL;
	assert(NULL != pqueue);
	
	data = SortLGetData(SortLBegin(pqueue->list));
	
	SortLPopBack(pqueue->list);
	
	return data;
}


/* Add node to the end of queue Success = 0, Fail = 1 */
int PQEnQueue(pqueue_ty *pqueue, void *data)
{


	sortlist_iter_ty iter = {NULL};
			
	assert(NULL != pqueue);
	assert(NULL != pqueue->list);
	assert(NULL != data);
	
	iter = SortLInsert(pqueue->list,data);
	
	
	if (iter.node)
	{
		return 0;
	}
	
	return 1;
}

/*get data of first element in queue first node */
const void *PQPeek(const pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	
	
	return SortLGetData(SortLGetPrev(SortLEnd(pqueue->list)));
}




/*Queue is empty- status 1 for empty, 0 not empty*/
int PQIsEmpty(const pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	return SortLIsEmpty(pqueue->list);

}



/*Size of Queue from tail to head*/
size_t PQSize(const pqueue_ty *pqueue)
{

	assert(NULL != pqueue);
	
	return SortLSize(pqueue->list);
}




/*Delete node by is_match and return pointer to data */

void *PQErase(pqueue_ty *pq, int (*is_match)(const void *data, const void *param), void *param)
{


	sortlist_iter_ty iter_find = {NULL};
	void *data = NULL;
	
	
	assert(NULL != pq);
	assert(NULL != is_match);

	
		
	iter_find = SortLFindIf(SortLBegin(pq->list), SortLEnd(pq->list), is_match, param);
	
	if (!iter_find.node)
	{
		return NULL;
	}
	
	data = SortLGetData(iter_find); 
	
	SortLRemove(iter_find);
	
	return data;
}
	


	
	
	
	
	

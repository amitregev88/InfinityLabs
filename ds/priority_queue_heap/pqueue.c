/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 12.07.22
* OL124 Priority Queue project (base on heap)
*************************************************************************************/

#include <assert.h>	/* assert*/
#include <stdlib.h>	/* malloc*/
#include <assert.h>	/* assert*/
#include "pqueue.h"
#include "heap.h"

struct pqueue
{
    heap_ty *heap;
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
	
	new_pqueue->heap = HEAPCreate(cmp);
	if (NULL == new_pqueue->heap)
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
	 HEAPDestroy(pqueue->heap);
	 pqueue->heap = NULL;
	 free(pqueue); 
}

/*Get node from front of the queue - return  data from node */
void *PQDeQueue(pqueue_ty *pqueue)
{
	void *data = NULL;
	assert(NULL != pqueue);
	
	data = HEAPPeek(pqueue->heap);

	HEAPPop(pqueue->heap);

	return data;
}

/* Add node to the end of queue Success = 0, Fail = 1 */
int PQEnQueue(pqueue_ty *pqueue, void *data)
{		
	assert(NULL != pqueue);
	assert(NULL != pqueue->heap);
	assert(NULL != data);
	
	return HEAPPush(pqueue->heap,data);
}

/*get data of first element in queue first node */
const void *PQPeek(const pqueue_ty *pqueue)
{
	assert(NULL != pqueue);
	
	return HEAPPeek(pqueue->heap);
}

/*Queue is empty- status 1 for empty, 0 not empty*/
int PQIsEmpty(const pqueue_ty *pqueue)
{
	assert(pqueue);
	return HEAPIsEmpty(pqueue->heap);
}


/*Size of Queue from tail to head*/
size_t PQSize(const pqueue_ty *pqueue)
{
	assert(pqueue);
	
	return HEAPSize(pqueue->heap);
}


/*Delete node by is_match and return pointer to data */

void *PQErase(pqueue_ty *pq, int (*is_match)(const void *data, const void *param), void *param)
{
	assert(pq);
	assert(is_match);	
		
	return HEAPRemove(pq->heap,param,is_match);
}
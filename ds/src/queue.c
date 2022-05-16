/*************************************************************************************
* Name: Amit Regev 
* Reviewer: Alexander Bor
* Date: 05.08.22
* OL124 Queue (base on Singly Linked List)
*************************************************************************************/
#include "stdlib.h"  /*malloc*/
#include "slinked_list.h"
#include "queue.h"  

struct queue
{
    slist_ty *list;
};




/*Creates Queue - return pointer to Que */
queue_ty *QCreate(void)
{
 	queue_ty *queue = malloc(sizeof(queue));
 	
 	if(NULL == queue)
	{
		return NULL;
	}

  	
	queue->list = SListCreate();
	
	if (NULL == queue->list)
	{
		free(queue);
		return NULL;
	}

	
	
	return queue;
}


/*Delete Que */
void QDestroy(queue_ty *queue)
{
	SListDestroy(queue->list);
	free(queue);
}

/*Get node from front of the queue - return  data from node (pop front)*/
void *QDeQueue(queue_ty *queue)
{
	return SListPopFront(queue->list);
}

/* Add node to the end of queue Success = 0, Fail = 1 (push back) */
int QEnQueue(queue_ty *queue, void *data)
{
	return (SListPushBack(queue->list, data).node != NULL) ? 0 : 1; 
}
/*get data of first element in queue first node */
const void *QPeek(const queue_ty *queue)
{
	return SListGetData(SListBegin(queue->list));
}

/*Queue is empty- status 1 for empty, 0 not empty*/
int QIsEmpty(const queue_ty *queue)
{
	return SListIsEmpty(queue->list);
}

/*Size of Queue from tail to head*/
size_t QSize(const queue_ty *queue)
{
	return SListSize(queue->list);
}

/* --- Append --- -append list2  to  the end of the list1 and
               list2 is turn EMPTY , user need to destroy it at the end of the program*/


void QAppend(queue_ty *_dest_queue, queue_ty *_src_queue)
{

	SListAppend(_dest_queue->list, _src_queue->list);
}

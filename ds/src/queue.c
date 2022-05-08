/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 05.08.22
* OL124 Queue (base on Singly Linked List)
*************************************************************************************/




/*Creates Queue - return pointer to Que */
queue_ty *QCreate(void)
{
	
 	queue_ty *queue = NULL;
	queue->list = SListCreate(queue);
	
	return queue;
	
}



/*Delete Que */
void QDestroy(queue_ty *queue)
{
	
	SListDestroy(queue);

}



/*Get node from front of the queue - return  data from node (pop front)*/
void *QDeQueue(queue_ty *queue)
{
	return SListPopFront(queue);

}



/* Add node to the end of queue Success = 0, Fail = 1 (push back) */
int QEnQueue(queue_ty *queue, void *data)
{
	return pushback(queue->list, data).node != NULL ? 0 : 1; /* */

}
/*get data of first element in queue first node */
const void *QPeek(const queue_ty *queue);
/*Queue is empty- status 1 for empty, 0 not empty*/
int QIsEmpty(const queue_ty *queue);
/*Size of Queue from tail to head*/
size_t QSize(const queue_ty *queue);
/*append source queue to end of the line of dest queue (push back) */
void QAppend(queue_ty *_dest_queue, queue_ty *_src_queue);

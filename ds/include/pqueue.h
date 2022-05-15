/*************************************************************
*OL124 Priority Queue project
*pqueue.h
*pqueue.c
* pqueue_test.c
* *
*ver 1.1
******************************************************************/

#ifndef OL124_PriorityQueue_H
#define OL124_PriorityQueue_H

#include "sortlist.h"

/*
struct pqueue
{
   sortlist_ty *list;

};

*/

typedef struct pqueue pqueue_ty;
/*Creates Queue - return pointer to Que */
pqueue_ty *PQCreate(int (*cmp)(const void *, const void *));
/*Delete Que */
void PQDestroy(pqueue_ty *pqueue);
/*Get node from front of the queue - return  data from node (pop front)*/
void *PQDeQueue(pqueue_ty *pqueue);
/* Add node to the end of queue Success = 0, Fail = 1 */
int PQEnQueue(pqueue_ty *pqueue, void *data);
/*get data of first element in queue first node */
const void *PQPeek(const pqueue_ty *pqueue);
/*Queue is empty- status 1 for empty, 0 not empty*/
int PQIsEmpty(const pqueue_ty *pqueue);
/*Size of Queue from tail to head*/
size_t PQSize(const pqueue_ty *pqueue);

/*append source queue to end of the line of dest queue (push back) */
/* void PQMerge(queue_ty *_dest_pqueue, queue_ty *_src_pqueue);*/

/*Delete node by is_match and return pointer to data */
void *PQErase(pqueue_ty *pq, int (*is_match)(const void *data, const void *param), void *param);

#endif /* OL124_PriorityQueue_H */

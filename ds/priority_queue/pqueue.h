/*************************************************************
*OL124 Priority Queue project
*pqueue.h
*pqueue.c
* pqueue_test.c
* *
*ver 1.2
******************************************************************/

#ifndef OL124_PriorityQueue_H
#define OL124_PriorityQueue_H

#include <stddef.h> /* size_t */

/*
struct pqueue
{
    sorted_list_ty *list;

};

*/
/* high priority is given by compare function from sortlist.h when the later argument  is with the higher priority.
meaning for priority as returned value of int (*compare_ty) (const void *a, const void *b) :
 - Positive - location in queue - first a, second b - higher priority belong to a
 - Negative - location in queue - first b, second a - higher priority belong to b
 - Zero  a=b - they have the same priority act as regular queue
*/
typedef struct pqueue pqueue_ty;

/*Creates Queue - return pointer to Que */
pqueue_ty *PQCreate(int (*cmp)(const void *, const void *));

/*Delete Que */
void PQDestroy(pqueue_ty *pqueue);

/*Get node from front of the queue - return  data from node */
void *PQDeQueue(pqueue_ty *pqueue);

/* Add node to the end of queue Success = 0, Fail = 1 */
int PQEnQueue(pqueue_ty *pqueue, void *data);

/*get data of first element in queue first node */
const void *PQPeek(const pqueue_ty *pqueue);

/*Queue is empty- status 1 for empty, 0 not empty*/
int PQIsEmpty(const pqueue_ty *pqueue);

/*Size of Queue from tail to head*/
size_t PQSize(const pqueue_ty *pqueue);

/*Delete node by is_match and return pointer to data */
void *PQErase(pqueue_ty *pq, int (*is_match)(const void *data, const void *params), void *params);

#endif /* OL124_PriorityQueue_H */

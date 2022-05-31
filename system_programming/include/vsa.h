/******************************************
* OL124 VSA
* vsa.h
* vsa.c
* vsa_test.c 
*
* Revision 2.0
******************************************/


#ifndef __VSA__H_
#define __VSA__H_

#include <stddef.h>
typedef struct vsa vsa_ty;

/*******************************************************************
* Create VSA - user passes pointer and memory allocation size
********************************************************************/
vsa_ty *VSAInit(void *pool, size_t pool_size);

/*******************************************************************
* Memory Allocation:
* get the pointer to the data that was asked.
* traverse the pool and return first fit for the memory that was asked.
* preforme cut and coalesce of free blocks as needed while traversing.
* in case of fail (size > largest chunk available) return NULL;
********************************************************************/
void *VSAAlloc(vsa_ty *vsa, size_t size);

/*******************************************************************
* Memory DeAllocation -O(1)
********************************************************************/
void VSAFree(void *block);

/*******************************************************************
* return largest Chunk of free bytes avilable
********************************************************************/
size_t VSALargestChunkAvailable(vsa_ty *vsa);

#endif /* __VSA__H_ */


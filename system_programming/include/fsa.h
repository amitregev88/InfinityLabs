/******************************************
* OL124 FSA
* fsa.h
* fsa.c
* fsa_tast.c 
* Revision 3.1
******************************************/

#ifndef __FSA_FREELIST_H_
#define __FSA_FREELIST_H_

#include <stddef.h> /* size_t */ 

typedef struct fsa fsa_ty;

/**********************************************************************
* How much memory should be provided to the Init() func.
* Function needs to consider the memory for the FSA memory management.
* consider memory alignment to WORD size.
* returns needed_pool_size
*********************************************************************/
size_t FSASuggestSize(size_t number_of_desired_blocks, size_t size_of_block);

/*******************************************************************
* Create FSA- user passes pointer after memory allocation
********************************************************************/
fsa_ty *FSAInit(void *pool, size_t pool_size, size_t size_of_block);

/*******************************************************************
* Memory Allocation -O(1)
* get the pointer to the data that was just allocated
********************************************************************/
void *FSAAlloc(fsa_ty *fsa);

/*******************************************************************
* Memory DeAllocation -O(1)
********************************************************************/
void FSAFree(fsa_ty *fsa, void *block);

/*******************************************************************
* count free blocks
********************************************************************/
size_t FSACountFree(fsa_ty *fsa);

#endif /* __FSA_FREELIST_H_ */

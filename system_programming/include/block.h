/*************************************************************
* OL124  VSA implementation 
* 
* block.h
* block.c
* 
* another: Amit Regev
*******************************************************************/

#ifndef OL124_VSA_BLOCK_H
#define OL124_VSA_BLOCK_H

#include <stddef.h> /* size_t */

extern const size_t WORD_SIZE;


/***********************************************************************************
*--- SetSizeOfBlock --- Sets the size of the block 
**************************************************************************************/
size_t SetSizeOfBlock(size_t size_of_block);

/***********************************************************************************
*--- IsFreeBlock - return true if block is free or false if not
**************************************************************************************/
int IsFreeBlock(void *block);

/***********************************************************************************
*--- SetOccupiedBlock --- Sets the block as Occupied
**************************************************************************************/
void SetOccupiedBlock(void *block);

/***********************************************************************************
*--- SetFreeBlock --- Sets the block as free
**************************************************************************************/
void SetFreeBlock(void *block);
/***********************************************************************************
*--- AllocBlock --- allocate block. return ptr to block or NULL in case of failure.
**************************************************************************************/
void *AllocBlock(void *block, size_t size);

/***********************************************************************************
*--- GetNextMeta ---return ptr to next meta.
**************************************************************************************/
void *GetNextMeta(void *meta);


/***********************************************************************************
*--- SetSizeOfBlock ---set size of the block.
**************************************************************************************/

size_t SetSizeOfBlock(size_t size_of_block);



#endif /* OL124_VSA_BLOCK_H */

/*

static size_t SetSizeOfBlock(size_t size_of_block);
static void CoalesceVSA(vsa_ty *vsa);
static int IsFreeBlock(void *meta);
static void SetOccupiedBlock(void *block);
static void SetFreeBlock(void *block);
static void *AllocBlock(void *meta, size_t size);
static void *GetNextMeta(vsa_ty *vsa, void *meta);






*/







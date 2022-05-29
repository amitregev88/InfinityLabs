/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 23.05.22
* Fixed Size Allocator
**************************************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include "fsa.h"

static size_t SetSizeOfBlock(size_t size_of_block);

struct fsa
{
    
    void *head;
 
    size_t free_blocks;

};


/**********************************************************************
* How much memory should be provided to the Init() func.
* Function needs to consider the memory for the FSA memory management.
* consider memory alignment to WORD size.
* returns needed_pool_size
*********************************************************************/
size_t FSASuggestSize(size_t number_of_desired_blocks, size_t size_of_block)
{
    
    
    size_t size_suggest = number_of_desired_blocks * SetSizeOfBlock(size_of_block) + sizeof(struct fsa) + sizeof(size_t)- 1;
    
    assert(size_of_block >= sizeof(size_t));
   
    return size_suggest;
}

/*******************************************************************
* Create FSA- user passes pointer after memory allocation
********************************************************************/
fsa_ty *FSAInit(void *pool, size_t pool_size, size_t size_of_block)
{
    fsa_ty *fsa = NULL;
    size_t i = 0;
    char *block_offset = NULL;
    

    assert(NULL != pool);
    assert(pool_size >= size_of_block + sizeof(fsa_ty)); 
    assert(size_of_block > 0);

    size_of_block = SetSizeOfBlock(size_of_block);

    if ((size_t)pool % sizeof(size_t))
    {
        fsa = (fsa_ty *)((size_t)pool + sizeof(size_t) - ((size_t)pool % sizeof(size_t)));
        pool_size -= sizeof(size_t) - (size_t)pool % sizeof(size_t);
    }

    else 
    {
        fsa = (fsa_ty *)pool;
    }


    block_offset = (char *) fsa + sizeof(fsa_ty);

    

    fsa->free_blocks =  (pool_size - sizeof(fsa_ty) )/ size_of_block;
      
    /*assign offset for each block*/
    for(i = 0; i < (fsa->free_blocks - 1); ++i)
    {
    
        block_offset = (char *)fsa + sizeof(fsa_ty) + i * size_of_block;

        *(size_t *)block_offset = (size_t)block_offset +  size_of_block - (size_t)fsa;

    }

    block_offset = (char *)fsa + sizeof(fsa_ty) + i * size_of_block;

    *(size_t *)block_offset = 0;

    fsa->head =  (char *)fsa + sizeof(fsa_ty);

    return fsa;
}



/*******************************************************************
* Memory Allocation -O(1)
* get the pointer to the data that was just allocated
********************************************************************/
void *FSAAlloc(fsa_ty *fsa)
{
    void *next_free_block = NULL;

    assert (NULL != fsa);
    assert (NULL != fsa->head);

    
    if (fsa->free_blocks == 0)
    {

        return NULL;
    }
    
    
    next_free_block = fsa->head;
        
    --fsa->free_blocks;

    fsa->head = (char *)fsa + *(size_t *)fsa->head;

    return next_free_block;
}


/*******************************************************************
* Memory DeAllocation -O(1)
********************************************************************/
void FSAFree(fsa_ty *fsa, void *block)
{
    assert(fsa);
    assert(block);

    ++fsa->free_blocks;

    *(size_t *)block = (size_t)fsa->head - (size_t)fsa;
    
    fsa->head = block;
}

/*******************************************************************
* count free blocks
********************************************************************/
size_t FSACountFree(fsa_ty *fsa)
{
    assert(NULL != fsa);

    return(fsa->free_blocks);

}




static size_t SetSizeOfBlock(size_t size_of_block)
{

    assert (0 != size_of_block);


    if (size_of_block % sizeof(size_t) != 0)
    {
        size_of_block = size_of_block + sizeof(size_t) - size_of_block % sizeof(size_t);

    }

    return size_of_block;

}



















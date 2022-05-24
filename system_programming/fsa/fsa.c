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
    size_t size_suggest = number_of_desired_blocks * SetSizeOfBlock(size_of_block) + sizeof(struct fsa);
    
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
    char *block_address = NULL;

    assert(NULL != pool);
    assert(pool_size >= size_of_block + sizeof(fsa_ty)); 
    assert(size_of_block > 0);

    size_of_block = SetSizeOfBlock(size_of_block);

    if ((size_t)pool % sizeof(size_t))
    {
        fsa = (fsa_ty *)((size_t)pool + sizeof(size_t) - ((size_t)pool % sizeof(size_t)));
    }

    else 
    {
        fsa = (fsa_ty *)pool;
    }


    block_address = (char *) fsa + sizeof(fsa_ty);

    fsa->free_blocks =  (pool_size - sizeof(fsa_ty)) / size_of_block;
    
    i = 0;
    
    /*assign offset for each block*/
    for(; i < fsa->free_blocks - 1; ++i)
    {
    
        block_address = (char *)pool + sizeof(fsa_ty) + i * size_of_block;

        *(size_t *)block_address = (size_t)block_address +  size_of_block - (size_t)pool;

    }

    block_address = (char *)pool + sizeof(fsa_ty) + i * size_of_block;

    *(size_t *)block_address = 0;


    return fsa;
}



/*******************************************************************
* Memory Allocation -O(1)
* get the pointer to the data that was just allocated
********************************************************************/
/*void *FSAAlloc(fsa_ty *fsa)
{
    void *free_block = NULL;

    assert (NULL != fsa) 

    free_block = fsa


}


/*******************************************************************
* Memory DeAllocation -O(1)
********************************************************************/
/*void FSAFree(fsa_ty *fsa, void *block);

/*******************************************************************
* count free blocks
********************************************************************/
/*size_t FSACountFree(fsa_ty *fsa);


*/

static size_t SetSizeOfBlock(size_t size_of_block)
{

    assert (0 != size_of_block);


    if (size_of_block % sizeof(size_t) != 0)
    {
        size_of_block = size_of_block + sizeof(size_t) - size_of_block % sizeof(size_t);

    }

    return size_of_block;

}



















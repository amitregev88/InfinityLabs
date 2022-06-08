/*************************************************************************************
* Name: Amit Regev 
* Reviewer: Yotam Aharon
* Date: 26.05.22
* Variable Size Allocator
**************************************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include "vsa.h"
#include "block.h"

static void CoalesceVSA(vsa_ty *vsa);

struct vsa
{
    void *head; /* first meta data*/
    void *tail; /* end of the pool */
};

/*******************************************************************
* Create VSA - user passes pointer and memory allocation size
********************************************************************/
vsa_ty *VSAInit(void *pool, size_t pool_size)
{
    vsa_ty *vsa = NULL;

    size_t neto = 0;
        
    assert(NULL != pool);
    assert(pool_size > 0); 

        
    if ((size_t)pool % WORD_SIZE)
    {
        vsa = (vsa_ty *)((size_t)pool + WORD_SIZE - ((size_t)pool % WORD_SIZE));
    }

    else 
    {
        vsa = (vsa_ty *)pool;
    }

    vsa->head = (char *)vsa + sizeof(vsa_ty); 
   
    vsa->tail =  (char *) pool + (pool_size);

    if((size_t)vsa->tail % WORD_SIZE != 0)
    {

        vsa->tail = (char *)vsa->tail - ((size_t)vsa->tail % WORD_SIZE);
    }

    neto = ((size_t)vsa->tail - (size_t)vsa->head) - WORD_SIZE;

    *(size_t *)(vsa->head) = neto;
    
    return vsa;
}

/*******************************************************************
* Memory Allocation:
* get the pointer to the data that was asked.
* traverse the pool and return first fit for the memory that was asked.
* preforme cut and coalesce of free blocks as needed while traversing.
* in case of fail (size > largest chunk available) return NULL;
********************************************************************/
void *VSAAlloc(vsa_ty *vsa, size_t size)
{
    void *iter = NULL;
    void *data = NULL;

    assert(NULL != vsa);
    assert(size > 0);

    iter = vsa->head;

    size = SetSizeOfBlock(size);

    CoalesceVSA(vsa);

    while(iter && iter < vsa->tail)
    {
        if (IsFreeBlock(iter) && *(size_t *)iter >= size)       /*checks if the next block is free and if the block is fit to space*/
        {
            data = AllocBlock(iter, size);

            return data;

        }     
       
        iter = GetNextMeta(iter);
        if(iter >= vsa->tail)
        {
            break;
        }

    
       
    }

    
    return data;
}

/*******************************************************************
* Memory DeAllocation -O(1)
********************************************************************/
void VSAFree(void *block)
{
    assert(NULL != block);

    SetFreeBlock(block); 


}

/*******************************************************************
* return current amount of free bytes avilable
********************************************************************/
size_t VSALargestChunkAvailable(vsa_ty *vsa)
{
    
    void* iter = NULL;
    
    size_t amount_of_bytes = 0;

    size_t temp = 0;

    assert(NULL != vsa);

    CoalesceVSA(vsa);

    iter = vsa->head;

    while (iter < vsa->tail)
    {
        
        
        for(;iter < vsa->tail && !IsFreeBlock(iter);iter = GetNextMeta(iter))
        {
            /*empty*/
        }
        
        if(iter >= vsa->tail)
        {

            return temp;
        } 

        amount_of_bytes = *(size_t *)iter;

        if (amount_of_bytes > temp)
        {
            temp = amount_of_bytes;
        }

        iter = GetNextMeta(iter);
    }
        
    return temp; 
}

/***********************************************************************************
*--- CoalesceVSA ---Coalesce from the given vsa.
**************************************************************************************/

static void CoalesceVSA(vsa_ty *vsa)
{
    
    
    size_t amount_of_bytes = 0;

    size_t counter = 0;

    void *iter = vsa->head;

    void *iter_next = NULL;

    while (iter < vsa->tail)
    {
        
        
        for(;iter < vsa->tail && !IsFreeBlock(iter);iter = GetNextMeta(iter))
        {
            /*empty*/
        }
        

        if(iter >= vsa->tail) 
        {
            return;
        }
             
        iter_next = iter;

        for(; iter_next < vsa->tail && IsFreeBlock(iter_next);iter_next = GetNextMeta(iter_next))
        {      
            amount_of_bytes += *(size_t *)iter_next;
            ++counter;
        }

         if(iter >= vsa->tail)
        {
            return;
        }

        *(size_t *)iter = amount_of_bytes + WORD_SIZE*(counter - 1);

        amount_of_bytes = 0;
        counter = 0;
        iter = GetNextMeta(iter);
    }     
}




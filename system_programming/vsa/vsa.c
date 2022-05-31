/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 26.05.22
* Variable Size Allocator
**************************************************************************************/

#include <stddef.h> /* size_t */
#include <assert.h> /* assert */
#include "vsa.h"

static size_t WORD_SIZE = sizeof(size_t);


static size_t SetSizeOfBlock(size_t size_of_block);
static void CoalesceVSA(vsa_ty *vsa);
static int IsFreeBlock(void *meta);
static void SetAllocBlock(void *block);
static void SetFreeBlock(void *block);
static void *AllocBlock(void *meta, size_t size);
static void *GetNextMeta(vsa_ty *vsa, void *meta);

struct vsa
{
    void *head; /* first meta data*/
    void *tail; /* end of the pool */
};

typedef struct meta
{
    size_t block;
}meta_ty;



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
       
        iter = GetNextMeta(vsa,iter);
       
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
        
        
        for(;iter && !IsFreeBlock(iter);iter = GetNextMeta(vsa, iter))
        {
            /*empty*/
        }
        
        if(!iter)
        {

            return temp;
        } 

        amount_of_bytes = *(size_t *)iter;

        if (amount_of_bytes > temp)
        {
            temp = amount_of_bytes;
        }

        iter = GetNextMeta(vsa, iter);
    }
        
    return temp; 
}


/*******************************************************************
* inner function - set the size of block to word or duplicates of a word
********************************************************************/
static size_t SetSizeOfBlock(size_t size_of_block)
{

    assert (0 != size_of_block);


    if (size_of_block % WORD_SIZE != 0)
    {
        size_of_block = size_of_block + WORD_SIZE - size_of_block % WORD_SIZE;

    }

    return size_of_block;

}

/*******************************************************************
* inner function - make Coalesce to the VSA
********************************************************************/

static void CoalesceVSA(vsa_ty *vsa)
{
    
    
    size_t amount_of_bytes = 0;

    size_t counter = 0;

    void *iter = vsa->head;

    void *iter_next = NULL;

    while (iter && iter < vsa->tail)
    {
        
        
        for(;iter && !IsFreeBlock(iter);iter = GetNextMeta(vsa, iter))
        {
            /*empty*/
        }
        
        iter_next = iter;

        if(!iter)
        {
            return;
        }
             
        for(; iter_next && IsFreeBlock(iter_next);iter_next = GetNextMeta(vsa, iter_next))
        {      
            amount_of_bytes += *(size_t *)iter_next;
            ++counter;
        }

         if(!iter_next)
        {
            return;
        }

        *(size_t *)iter = amount_of_bytes + WORD_SIZE*(counter - 1);

        amount_of_bytes = 0;
        counter = 0;
        iter = GetNextMeta(vsa, iter);
    }     
}


/*******************************************************************
* inner function - checks the given block is available
********************************************************************/
static int IsFreeBlock(void *meta)
{
    return (*(size_t *)meta % 2 == 0);

}


/*******************************************************************
* inner function - set the given block to be occupied.
********************************************************************/

static void SetAllocBlock(void *block)
{
    
    void *meta = NULL;
    
    assert(block);
  
    meta = (char *)block - WORD_SIZE;

    *(size_t *)meta |= 0x01;

}

/*******************************************************************
* inner function - set the given block to be free.
********************************************************************/

static void SetFreeBlock(void *block)
{
    
    void *meta = NULL;
          
    meta = (char *)block - WORD_SIZE;

    *(size_t *)meta -= (*(size_t *)meta & 0x01);

}
/*******************************************************************
* inner function - 
********************************************************************/

static void *AllocBlock(void *meta, size_t size)
{
    
    
    void *data = NULL;
    void *next_meta = NULL;

    assert(meta);
    
    data = (char *)meta + WORD_SIZE;
    
    if (*(size_t *)meta >= size + 2 * WORD_SIZE) 
    {
    
        next_meta = (char *)data + size;

        *(size_t *)next_meta =  *(size_t *)meta - size - WORD_SIZE;
   
        *(size_t *)meta = size;

        SetFreeBlock(next_meta);
        
    }

  
    SetAllocBlock(data);
    

    return data;


    
}

/*******************************************************************
* inner function - GetNextBlock
********************************************************************/
static void *GetNextMeta(vsa_ty *vsa, void *meta)
{
    if ((void *)((char *)meta + *(size_t *)meta + WORD_SIZE  - (*(size_t *)meta & 0x01)) < vsa->tail)
    {
        return (void *)((char *)meta + *(size_t *)meta + WORD_SIZE  - (*(size_t *)meta & 0x01));

    }

    return NULL;

    
}
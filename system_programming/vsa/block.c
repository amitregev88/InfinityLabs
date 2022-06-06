
#include <stddef.h> /* size_t */
#include <assert.h>

const size_t WORD_SIZE = sizeof(size_t);



/***********************************************************************************
*--- SetSizeOfBlock --- Sets the size of the block 
**************************************************************************************/
size_t SetSizeOfBlock(size_t size_of_block)
{

    assert (0 != size_of_block);


    if (size_of_block % WORD_SIZE != 0)
    {
        size_of_block = size_of_block + WORD_SIZE - size_of_block % WORD_SIZE;

    }

    return size_of_block;

}




/***********************************************************************************
*--- IsFreeBlock - return true if block is free or false if not
**************************************************************************************/
int IsFreeBlock(void *meta)
{
    return (*(size_t *)meta % 2 == 0);

}


/***********************************************************************************
*--- SetOccupiedBlock --- Sets the block as Occupied
**************************************************************************************/

void SetOccupiedBlock(void *block)
{
    
    void *meta = NULL;
    
    assert(block);
  
    meta = (char *)block - WORD_SIZE;

    *(size_t *)meta |= 0x01;

}

/***********************************************************************************
*--- SetFreeBlock --- Sets the block as free
**************************************************************************************/

void SetFreeBlock(void *block)
{
    
    void *meta = NULL;
          
    meta = (char *)block - WORD_SIZE;

    *(size_t *)meta -= (*(size_t *)meta & 0x01);

}
/***********************************************************************************
*--- AllocBlock --- allocate block. return ptr to block or NULL in case of failure.
**************************************************************************************/

void *AllocBlock(void *meta, size_t size)
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

  
    SetOccupiedBlock(data);
    

    return data;


    
}

/***********************************************************************************
*--- GetNextBlock ---return ptr to next block or NULL in case of out of range.
**************************************************************************************/
void *GetNextMeta(void *meta)
{
    return (void *)((char *)meta + *(size_t *)meta + WORD_SIZE  - (*(size_t *)meta & 0x01));
}

    

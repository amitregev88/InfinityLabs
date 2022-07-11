/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 11/7/22 
* OL124 heap implementation (base on dynamic vector)
*******************************************************************/
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h>/*assert*/
#include <stddef.h> /*size_t*/
#include "heap.h"
#include "dynamic_vector.h"

#define CAPACITY 30

/* max heap - root is maximum*/
struct heap
{
    dynamic_vector_ty *vector;
    compare_ty *cmp;    
};

/***********************************************************
 * --- HEAPCreate ---
 * Function creates a new binary tree heap data structure.
 *	return NULL if malloc fails
 ***********************************************************/
heap_ty *HEAPCreate(compare_ty compare)
{
    dynamic_vector_ty *dvector = NULL;
    heap_ty *new_heap = NULL;
    
    assert(compare);

    new_heap = malloc(sizeof(heap_ty));
    if(!new_heap)
    {
        return NULL;
    }

    dvector = VectorCreate(CAPACITY, sizeof(void *));
    if (!dvector)
    {
        /*clean up*/
        free(new_heap);
        return NULL;
    }

    new_heap->vector = dvector;
    new_heap->cmp = compare;

    return new_heap;
}

/***********************************************************
 * --- HEAPDestroy ---
 * Function frees all the alements in the tree.
 ***********************************************************/
void HEAPDestroy(heap_ty* heap)
{
    assert(heap);

    VectorDestroy(heap->vector);

    free(heap);
    heap = NULL;
}

/***********************************************************
 * --- HEAPPush ---
 * push new element to the tree. return 0 if succeed, 1 if fail
 ***********************************************************/
int HEAPPush(heap_ty* heap, void *to_push);

/***********************************************************
 * --- HEAPPop ---
 * remove the root 
 ***********************************************************/
void HEAPPop(heap_ty* heap);

/***********************************************************
 * --- HEAPPeek ---
 * return the data of the root
 ***********************************************************/
void *HEAPPeek(heap_ty* heap)
{
    assert(heap);
    return VectorGetAccessToElement(heap->vector,0);
}

/***********************************************************
 * --- HEAPSize ---
 * Function returns the number of items stored in HEAP
 ***********************************************************/
size_t HEAPSize(const heap_ty *heap)
{
    assert(heap);
    return VectorSize(heap->vector);
}

/***********************************************************
 * --- HEAPIsEmpty ---
 * Function returns 1 - if Empty, 0 - not Empty
 ***********************************************************/
int HEAPIsEmpty(const heap_ty *heap)
{
    assert(heap);
    return VectorIsEmpty(heap->vector);
}

/***********************************************************
 * --- HEAPRemove ---
 * Function returns pointer to *to_remove
 ***********************************************************/
void* HEAPRemove(heap_ty *heap, void *to_remove, int (*is_match)(const void *data, const void *to_remove));

static HeapifyUp()


static void HeapifyDown(heap)
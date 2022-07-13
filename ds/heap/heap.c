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


static void HeapifyUp(heap_ty *heap);
static void HeapifyDown(heap_ty *heap);
static void *HisParent(heap_ty *heap, size_t index);
static void Swap(void *data1, void *data2);
static void *HisMaxChild(heap_ty *heap, size_t index);
static int HasOnlyOneChild(heap_ty *heap, size_t index);
static int IsALeaf(heap_ty *heap, size_t index);
static void LiftToRoot(heap_ty *heap, size_t index);


/* max heap - root is maximum*/
struct heap
{
    dynamic_vector_ty *vector;
    compare_ty cmp;    
};

/***********************************************************
 * --- HEAPCreate ---
 * Function creates a new binary tree heap data structure.
 *	return NULL if malloc fails
 ***********************************************************/
heap_ty *HEAPCreate(compare_ty compare)
{
    heap_ty *new_heap = NULL;
    
    assert(compare);

    new_heap = malloc(sizeof(heap_ty));
    if(!new_heap)
    {
        return NULL;
    }

    new_heap->vector = VectorCreate(CAPACITY, sizeof(void *));
    if (!new_heap->vector)
    {
        /*clean up*/
        free(new_heap);
        return NULL;
    }

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
int HEAPPush(heap_ty* heap, void *to_push)
{
    assert(heap);
    assert(to_push);

    if (VectorPushBack(heap->vector, &to_push))
    {
        return 1;
    }

    HeapifyUp(heap);

    return 0;
}

/***********************************************************
 * --- HEAPPop ---
 * remove the root 
 ***********************************************************/
void HEAPPop(heap_ty* heap)
{
	void *last_elem_dvector = NULL;
    void *root = NULL;

    assert(heap);

    if(HEAPIsEmpty(heap))
    {
        return;
    }

	root = VectorGetAccessToElement(heap->vector,0);
    last_elem_dvector = VectorGetAccessToElement(heap->vector, HEAPSize(heap) - 1);

    Swap(root,last_elem_dvector);
	
    VectorPopBack(heap->vector);

	HeapifyDown(heap);
}



/***********************************************************
 * --- HEAPPeek ---
 * return the data of the root
 ***********************************************************/
void *HEAPPeek(heap_ty* heap)
{
    assert(heap);
    return (void *)(*(size_t *)VectorGetAccessToElement(heap->vector,0));
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
void* HEAPRemove(heap_ty *heap, void *to_remove, int (*is_match)(const void *data, const void *to_remove))
{
    void *data = NULL, *iter_to_remove = NULL;
    size_t index_to_remove = 0;

    assert(heap);
    assert(to_remove);
    assert(is_match);
    
    iter_to_remove = VectorGetAccessToElement(heap->vector, index_to_remove);

     /* find "to_remove" node */
    for(index_to_remove = 0; index_to_remove < HEAPSize(heap); ++index_to_remove)
    {
        iter_to_remove = VectorGetAccessToElement(heap->vector, index_to_remove);

        if (is_match((void *)(*(size_t *)iter_to_remove), to_remove))
        {
            LiftToRoot(heap,index_to_remove);

            data = HEAPPeek(heap);

            HEAPPop(heap);

            return data;
        }
    }
    return NULL;
}

static void HeapifyUp(heap_ty *heap) /*for push*/
{
    void *parent_iter = NULL, *data = NULL;

    size_t index = 0;

    index = VectorSize(heap->vector) - 1;

    data = VectorGetAccessToElement(heap->vector,index);

    parent_iter = HisParent(heap,index);

    while(parent_iter && heap->cmp((void *)*(size_t *)data, (void *)*(size_t *)parent_iter) > 0)
    {
        Swap(data, parent_iter);
        index = (index -1)/ 2;
        data = parent_iter;
        parent_iter = HisParent(heap,index);
    }
}

static void HeapifyDown(heap_ty *heap) /*for pop*/
{

    void *max_child = NULL, *data = NULL;

    size_t index_root = 0;

    data = VectorGetAccessToElement(heap->vector,index_root);

    max_child = HisMaxChild(heap, index_root);


    while(max_child && heap->cmp((void *)(*(size_t *)data), (void *)(*(size_t *)max_child)) < 0)
    {
        Swap(data, max_child);

        if(VectorGetAccessToElement(heap->vector, 2 * index_root + 1) == data)
        {
            index_root = 2 * index_root + 1;
        }

        else
        {
           index_root = 2 * index_root + 2; 
        }

        max_child = HisMaxChild(heap,index_root);

    }
}

static void *HisParent(heap_ty *heap, size_t index)
{
    return index == 0 ? NULL : VectorGetAccessToElement(heap->vector,(index - 1) / 2);
}

static void Swap(void *data1, void *data2)
{
    size_t *ptr1 = NULL, *ptr2 = NULL;
    size_t tmp;

    ptr1 = (size_t *)data1;
    ptr2 = (size_t *)data2;

    tmp = *ptr1;
	*ptr1 = *ptr2;
	*ptr2 = tmp;
}

static void *HisMaxChild(heap_ty *heap, size_t index)
{
    if (HasOnlyOneChild(heap, index))
    {
        return VectorGetAccessToElement(heap->vector,2 * index +1);
    } 
    
    else if (IsALeaf(heap, index))
    {
        return NULL;

    }
        
    if (heap->cmp(*(void **)VectorGetAccessToElement(heap->vector,2 * index +1),*(void **)VectorGetAccessToElement(heap->vector,2 * index + 2)) > 0)
    {
        return VectorGetAccessToElement(heap->vector,2 * index +1);
    }

    else
    {
        return VectorGetAccessToElement(heap->vector,2 * index +2);
    }
}

static int HasOnlyOneChild(heap_ty *heap, size_t index)
{
    return ((index * 2 + 1) < VectorSize(heap->vector) && (index*2 + 2) == VectorSize(heap->vector));
}

static int IsALeaf(heap_ty *heap, size_t index)
{
    return ((index * 2 + 1) >= VectorSize(heap->vector));
}

static void LiftToRoot(heap_ty *heap, size_t index)
{
    size_t index_parent = 0;
    
    while (0 != index) /*swap to_remove with his parent until root*/
    {
        index_parent = (index - 1) / 2;

        Swap(VectorGetAccessToElement(heap->vector,index) , HisParent(heap,index));

        index = index_parent;
    }
}

 
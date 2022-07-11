/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 11/7/22 
* OL124 heap implementation (base on dynamic vector)
*******************************************************************/

#include<stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h>/*assert*/
#include "dynamic_vector.h"


/***************************
 * OL124 HEAP TREE project
 * heap.h
 * heap.c
 * heap_test.c
 *
 * version 1.4
 ***************************/


#ifndef __HEAP_TREE_H__
#define __HEAP_TREE_H__

#include <stddef.h> /*size_t*/

/* max heap - root is maximum*/
typedef struct heap heap_ty;


/***********************************************************
 * --- HEAPCreate ---
 * Function creates a new binary tree heap data structure.
 *	return NULL if malloc fails
 ***********************************************************/
heap_ty *HEAPCreate(compare_ty compare)
{




}

/***********************************************************
 * --- HEAPDestroy ---
 * Function frees all the alements in the tree.
 ***********************************************************/
void HEAPDestroy(heap_ty* heap);

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
void *HEAPPeek(heap_ty* heap);

/***********************************************************
 * --- HEAPSize ---
 * Function returns the number of items stored in HEAP
 ***********************************************************/
size_t HEAPSize(const heap_ty *heap);

/***********************************************************
 * --- HEAPIsEmpty ---
 * Function returns 1 - if Empty, 0 - not Empty
 ***********************************************************/
int HEAPIsEmpty(const heap_ty *heap);

/***********************************************************
 * --- HEAPRemove ---
 * Function returns pointer to *to_remove
 ***********************************************************/
void* HEAPRemove(heap_ty *heap, void *to_remove, int (*is_match)(const void *data, const void *to_remove));


#endif /* __HEAP_TREE_H__ */
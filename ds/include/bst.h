/***************************
 * OL124 BST project
 * bst.h
 * bst.c
 * bst_test.c
 * version 4
 ***************************/


#ifndef __BINARY_SEARCH_TREE_H__
#define __BINARY_SEARCH_TREE_H__

#include <stddef.h> /*size_t*/

typedef struct bst_node bst_node_ty;
typedef struct bst bst_ty;
typedef struct bst_iter
{
    bst_node_ty *iter_node;
} bst_iter_ty;

/*
  if data1 > data2 return 1;
  if data2 > data1 return -1;
  if data1 == data2 return 0;
*/
typedef int(*compare_ty)(const void* data1,const void *data2);

/*the function creates a new binary tree sata structure
return NULL if malloc fails */
bst_ty *BSTCreate(compare_ty compare);

/* the function frees all the alements in the tree*/
void BSTDestroy(bst_ty* bst);

/*the function returns the number of items stored in BST*/
size_t BSTSize(const bst_ty *bst);

/*1- is Empty, 0- not Empty*/
int BSTIsEmpty(const bst_ty *bst);

/*if fail return NULL */
bst_iter_ty BSTInsert(bst_ty *bst, void *data); 

/* removes node. returns iter's data */
void *BSTRemove(bst_ty *bst , bst_iter_ty iter); 

/* returns leftest leaf */
bst_iter_ty BSTBegin(const bst_ty *bst); 

/* refer to the position after the last element (righ-most element)  */
bst_iter_ty BSTEnd(const bst_ty *bst); 

/* returns iter to previous element */
bst_iter_ty BSTPrev(bst_iter_ty iter); 

/* returns iter to next element  */
bst_iter_ty BSTNext(bst_iter_ty iter); 

/* the function checks if the 2 iterators are equal.
return 1 if equal 0 for not */
int BSTIter_Is_Equal(bst_iter_ty iter1, bst_iter_ty iter2); 

/*the function gets iter and returns the dara at the location */
void *BSTGet_Data(const bst_iter_ty iter);

/* Find data in BST according to the compare function.*/
bst_iter_ty BSTFind(const bst_ty *bst, void *what_to_find);

int BSTForeach(const bst_iter_ty from, const bst_iter_ty to, int (*action)(void *data, const void *param), const void *param);

#endif /* __BINARY_SEARCH_TREE_H__ */
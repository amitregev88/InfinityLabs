/***************************
 * OL124 AVL TREE project
 * avl.h
 * avl.c
 * avl_test.c
 * version 4
 ***************************/


#ifndef __AVL_TREE_H__
#define __AVL_TREE_H__

#include <stddef.h> /*size_t*/
typedef enum order{pre_order, in_order, post_order} order_ty;
typedef struct avl avl_ty;

/*
  if key1 > key2 return 1;
  if key2 > key1 return -1;
  if key1 == key2 return 0;
*/
typedef int(*compare_ty)(const void *key1,const void *key2);

/*Function creates a new binary tree sata structure
return NULL if malloc fails */
avl_ty *AVLCreate(compare_ty compare);

/*Function frees all the alements in the tree*/
void AVLDestroy(avl_ty* avl);

/*Function returns the number of items stored in AVL*/
size_t AVLSize(const avl_ty *avl);

/*Return 1 - is Empty, 0 - not Empty*/
int AVLIsEmpty(const avl_ty *avl);

/*Success return 0 */
int AVLInsert(avl_ty *avl, void *key, void *val); 

/*Returns pointer to val to remove */
void* AVLRemove(avl_ty *avl , void *key); 

/*Find data in AVL according to the compare function and returns pointer to val.*/
void* AVLFind(const avl_ty *avl, void *key);

/*Return height 0 - 64  */
int AVLHeight(const avl_ty *avl);

/*Success return 0 */
int AVLForeach(avl_ty *avl, int (*action)(void *val, const void *param), const void *param, order_ty order_of_action);


#endif /* __AVL_TREE_H__ */

/*************************************************************************************
* OL124 DLinked List Project
* dlinked_list.h
* dlinked_list.c
* dlinked_list_test.c
*
*   
*************************************************************************************/
#ifndef OL124_LINKED_LIST_H
#define OL124_LINKED_LIST_H

#include <stddef.h>
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc */

/*


struct doubly_list
{
    doubly_node *begin;
    doubly_node *end;
}

struct doubly_node 
{
    void *data; 
    doubly_node *next;
    doubly_node *prev;
};
*/

typedef struct doubly_list dlist_ty;
typedef struct doubly_node dlist_node_ty;


/*************************************************************************************
* --- ListCreate --- returns *list that points *head == NULL and *end == NULL
**************************************************************************************/
dlist_ty *DListCreate(void);

/*************************************************************************************
* --- ListDestroy --- free() all the NODES and LIST itself
**************************************************************************************/
void DListDestroy(dlist_ty *list);

/*************************************************************************************
* --- DListInsert --- receives the <node_ty *node> next to which make's the insert, return prev
**************************************************************************************/
dlist_node_ty *DListInsert(dlist_node_ty *where, void *data);

/*************************************************************************************
* --- Remove --- Removes the NODE next to <node_ty *node> 
* return NEXT NODE
**************************************************************************************/
dlist_node_ty *DListRemove(dlist_node_ty *to_remove);

/*************************************************************************************
* --- PushBack --- add's a NODE at the END of the linked list 
* return LAST NODE
**************************************************************************************/
dlist_node_ty *DListPushBack(dlist_ty *list, void *data);

/*************************************************************************************
* --- PushFront --- add's a NODE at the FRONT of the linked list 
* return 1 in case of success or 0 in case of failure
**************************************************************************************/
dlist_node_ty *DListPushFront(dlist_ty *list, void *data);

/*************************************************************************************
* --- PopBack --- POP's the LAST NODE 
* returns pointer to DATA
**************************************************************************************/
void *DListPopBack(dlist_ty *list);

/*************************************************************************************
* --- PopFront --- POP's the FIRST NODE 
* returns pointer to DATA
**************************************************************************************/
void *DListPopFront(dlist_ty *list);

/*************************************************************************************
* --- Size --- returns the size of the Linked List ----- O(n)
**************************************************************************************/
size_t DListSize(const dlist_ty *list);
/*************************************************************************************/

/*************************************************************************************
* --- DListIsEmpty --- returns 1 in case is empty or -0 other case ---- O(1)
**************************************************************************************/
int DListIsEmpty(const dlist_ty *list);

/*************************************************************************************
* --- GetData --- Gets the DATA from a NODE 
**************************************************************************************/
void *DListGetData(const dlist_node_ty *node);

/*************************************************************************************
* --- SetData --- Sets the DATA to a NODE 
**************************************************************************************/
void DListSetData(dlist_node_ty *node, void *data);

/*************************************************************************************
* --- GetNext --- Gets a pointer to the NEXT NODE to <node> 
**************************************************************************************/
dlist_node_ty *DListGetNext(const dlist_node_ty *node);

/*************************************************************************************
* --- GetPrev --- Gets a pointer to the PREV NODE to <node> 
**************************************************************************************/
dlist_node_ty *DListGetPrev(const dlist_node_ty *node);

/*************************************************************************************
* --- DListFind --- Finds the Node using USER's comparison function 
**************************************************************************************/
dlist_node_ty *DListFind(const dlist_node_ty *from, const dlist_node_ty *to, int (*is_match)(const void *data, const void *param), const void *param);

/*************************************************************************************
* --- DListBegin --- gets the first node 
**************************************************************************************/
dlist_node_ty *DListBegin(const dlist_ty *list);

/*************************************************************************************
* --- DListEnd --- gets the next of last node return the DUMMY
**************************************************************************************/
dlist_node_ty *DListEnd(const dlist_ty *list);

/*************************************************************************************
* --- DListForEach --- * return 1 in case of success or o  
**************************************************************************************/
int DListForEach(const dlist_node_ty *from, const dlist_node_ty *to, int (*action)(void *list_data, void *param), void *param);

/*************************************************************************************
* --- DListSplice ---  
**************************************************************************************/
void DListSplice(dlist_node_ty *dest, dlist_node_ty *from, dlist_node_ty *to);

/*************************************************************************************
* --- DListMultiFind --- Finds the Node using USER's comparison function 
**************************************************************************************/
dlist_ty *DListMultiFind(const dlist_node_ty *from, const dlist_node_ty *to, int (*is_match)(const void *data, const void *param), const void *param);


#endif /*OL124_LINKED_LIST_H*/


















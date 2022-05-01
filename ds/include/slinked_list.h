/*************************************************************************************
* OL124 SLinked List Project
* slinked_list.h
* slinked_list.c
* slinked_list_test.c
*
*   
*************************************************************************************/
#ifndef OL124_LINKED_LIST_H
#define OL124_LINKED_LIST_H

#include <stddef.h>
/*
struct sin_list
{
    sin_node head;
    sin_node tail;
}

struct sin_node 
{
    void *data; 
    sin_node *next;
};

struct slist_iter
{
    slist_node_ty *node;
    
} slist_iter_ty;

typedef struct sin_node slist_node_ty;*
*/

typedef struct sin_list slist_ty;
typedef struct slist_iter slist_iter_ty;



/*************************************************************************************
* --- ListCreate --- returns *list that points *head == NULL 
**************************************************************************************/
slist_ty *SListCreate(void);

/*************************************************************************************
* --- ListDestroy --- free() all the NODES and LIST itself O(n)
**************************************************************************************/
void SListDestroy(slist_ty *list);

/*************************************************************************************
* --- Insert --- receives the "where" and inserts before the "where" O(1)
**************************************************************************************/
slist_iter_ty SListInsert(slist_ty *list, slist_iter_ty where, void *data);

/*************************************************************************************
* --- Remove --- Removes the NODE next to <node_ty *node> 
* return NEXT NODE **to_remove -o(n), prev_remove -o(1)***
**************************************************************************************/
slist_iter_ty SListRemove(slist_ty *list, slist_iter_ty prev_remove);

/*************************************************************************************
* --- PushBack --- add's a NODE at the END of the linked list 
* return LAST NODE O(1)
**************************************************************************************/
slist_iter_ty SListPushBack(slist_ty *list, void *data);

/*************************************************************************************
* --- PushFront --- add's a NODE at the FRONT of the linked list 
* return 1 in case of success or o in case of O(1)
**************************************************************************************/
slist_iter_ty SListPushFront(slist_ty *list, void *data);

/*************************************************************************************
* --- PopBack --- POP's the LAST NODE 
* returns pointer to DATA O(n)
**************************************************************************************/
void *SListPopBack(slist_ty *list);

/*************************************************************************************
* --- PopFront --- POP's the FIRST NODE 
* returns pointer to DATA O(1)
**************************************************************************************/
void *SListPopFront(slist_ty *list);

/*************************************************************************************
* --- Size --- returns the size of the Linked List ----- O(n)
**************************************************************************************/
size_t SListSize(const slist_ty *list); 
/*************************************************************************************/

/*************************************************************************************
* --- DListIsEmpty --- returns 1 in case is empty or -0 other case ---- O(1)
**************************************************************************************/
int SListIsEmpty(const slist_ty *list);

/*************************************************************************************
* --- GetData --- Gets the DATA from a NODE 
**************************************************************************************/
void *SListGetData(const slist_iter_ty node);

/*************************************************************************************
* --- SetData --- Sets the DATA to a NODE 
**************************************************************************************/
void SListSetData(slist_iter_ty node, void *data);

/*************************************************************************************
* --- GetNext --- Gets a pointer to the NEXT NODE to <node> 
**************************************************************************************/
slist_iter_ty SListGetNext(const slist_iter_ty node);

/*************************************************************************************
* --- Find --- Finds the Node using USER's comparison function 
**************************************************************************************/
slist_iter_ty SListFind(const slist_iter_ty from, const slist_iter_ty to, int (*is_match)(const void *data, const void *param), const void *param);

/*************************************************************************************
* --- Begin --- gets the before the first node O(1)
**************************************************************************************/
slist_iter_ty SListBegin(const slist_ty *list);

/*************************************************************************************
* --- End --- gets the last connected node O(n), **bonus O(1)
**************************************************************************************/
slist_iter_ty SListEnd(const slist_ty *list);

/*************************************************************************************
* --- ForEach --- * return 1 in case of success or 0  O(n)
**************************************************************************************/
int SListForEach(const slist_iter_ty from, const slist_iter_ty to, int (*action)(void *list_data, void *param), void *param);


#endif /*OL124_LINKED_LIST_H*/


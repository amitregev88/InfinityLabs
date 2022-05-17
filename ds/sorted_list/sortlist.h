/*************************************************************
* OL124  project Sorted List
* 
* sortlist.h
* sortlist.c
* sortlist_test.c
* 
*
******************************************************************/

#ifndef OL124_SORT_LIST_H
#define OL124_SORT_LIST_H

#include <stddef.h>

#include "dlinked_list.h"

/*
struct sort_list
{
    dlist_ty *list;
    compare_ty compare;
};
*/
typedef struct sort_list sortlist_ty;

typedef struct sort_list_iter
{
    dlist_node_ty *node;
}sortlist_iter_ty ;


/* Negative- a->b/a<b  (first a, second b)  , Positive- b->a/ b<a (first b, second a) , Zero- a=b */
/*if result is negative then a, next b. elseif result is positive then b next a. else the order is not matter*/
typedef int (*compare_ty)(const void *a, const void *b);


/*************************************************************************************
*Creates Sorted list - return pointer to SortList 
**************************************************************************************/
sortlist_ty *SortLCreate(compare_ty compare);

/*************************************************************************************
*Delete Sorted List 
**************************************************************************************/
void SortLDestroy(sortlist_ty *sortlist);

/*************************************************************************************
* Add node to the sorted list return iter to this node if fail -> iter.node=NULL
**************************************************************************************/
sortlist_iter_ty SortLInsert(sortlist_ty *sortlist, void *data);

/*************************************************************************************
*Remove element
**************************************************************************************/
void SortLRemove(sortlist_iter_ty to_remove);

/*************************************************************************************
* --- Size --- returns the size of the Sorted Linked List ----- O(n)
**************************************************************************************/
size_t SortLSize(const sortlist_ty *sortlist);

/*************************************************************************************
* --- SortLIsEmpty --- returns 1 in case is empty or -0 other case ---- O(1)
**************************************************************************************/
int SortLIsEmpty(const sortlist_ty *sortlist);

/*************************************************************************************
* --- SortLBegin --- returns first iter of sorted list
**************************************************************************************/
sortlist_iter_ty SortLBegin(const sortlist_ty *sortlist);

/*************************************************************************************
* --- SortLEnd --- returns last iter of sorted list
**************************************************************************************/
sortlist_iter_ty SortLEnd(const sortlist_ty *sortlist);

/*************************************************************************************
* --- SortLGetPrev --- returns previous iter of given iter
**************************************************************************************/
sortlist_iter_ty SortLGetPrev(const sortlist_iter_ty iter);

/*************************************************************************************
* --- SortLGetNext --- returns next iter of given iter
**************************************************************************************/
sortlist_iter_ty SortLGetNext(const sortlist_iter_ty iter);

/*************************************************************************************
* --- SortLGetData --- returns data of given iter
**************************************************************************************/
void *SortLGetData(const sortlist_iter_ty iter);

/*************************************************************************************
* --- SortLIsSameIter --- returns 1 if the same, 0 otherwise
**************************************************************************************/
int SortLIsSameIter(const sortlist_iter_ty iter_1, const sortlist_iter_ty iter_2);

/*************************************************************************************
* --- SortLPopBack --- remove the last iter from sorted list and return its data
**************************************************************************************/
void *SortLPopBack(sortlist_ty *sortlist);

/*************************************************************************************
* --- SortLPopFront --- remove the first iter from sorted list and return its data
**************************************************************************************/
void *SortLPopFront(sortlist_ty *sortlist);

/*************************************************************************************
* --- SortLForEach --- return 0 in case of success or 1 failure 
**************************************************************************************/
int SortLForEach(sortlist_iter_ty from, const sortlist_iter_ty to, int (*action)(void *data, const void *param), const void *param);

/*************************************************************************************
* --- Find --- Finds the iter with data==param using  comparison function inside struct sort_list 
**************************************************************************************/
sortlist_iter_ty SortLFind(const sortlist_ty *sortlist, const sortlist_iter_ty from, const sortlist_iter_ty to, const void *param);

/*************************************************************************************
* --- Find --- Finds the iter using USER's comparison function is_match 
**************************************************************************************/
sortlist_iter_ty SortLFindIf(const sortlist_iter_ty from, const sortlist_iter_ty to, int (*is_match)(const void *data, const void *param), const void *param);

/*************************************************************************************
* --- SortLMerge --- Merge source list  into dest list, source list will be empty,  
**************************************************************************************/
void SortLMerge(sortlist_ty *_dest, sortlist_ty *_source);

#endif /* OL124_SORT_LIST_H */



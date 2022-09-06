/****************************************************************************/
/*	Project:	Sorted list API											  	*/
/*	File:		sorted_list.h												*/
/*	Date: 		19.06.2022													*/
/*	Name: 		HRD25														*/
/*	Reviewer:	Liel														*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __ILRD_SORTLIST_H__
#define __ILRD_SORTLIST_H__


#include <stddef.h>   /* size_t */

#include "dlist.h"
#include "function.h"

/****************************************************************************/
typedef struct srlist srlist_ty;

typedef struct sr_iter srlist_iter_ty;

/***************************Function Prototypes******************************/
srlist_ty *SortedListCreate(match_func_ty is_match);
/********************************DListCreate()*******************************
* Function Description: Creates a new list.

*Arguments: None.

*Return value: 	An iterator to head of a new list
				Returns NULL if function failed.

*Notes: Must use DListDestroy function after usage.

*Time complexity: O(1)
*****************************************************************************/
void SortedListDestroy(srlist_ty *list);
/********************************DListDestroy()******************************
* Function Description: Delete the list.

*Arguments: A list to delete.

*Return value: None.

*Notes: Argument must be valid.

*Time complexity: O(n). n is number of items in the list.
*****************************************************************************/
srlist_iter_ty SortedListBegin(const srlist_ty *list);
/**********************************DListBegin()******************************
* Function Description: Finds the beginning of the linked list.

*Arguments: A linked list.

*Return value: Iterator to the first item.
			   Returned iterator cannot be removed.

*Notes: List must be previously created and valid, else behaviour is undefined.

*Time complexity: O(1)
*****************************************************************************/
srlist_iter_ty SortedListNext(const srlist_iter_ty iter);
/**********************************DListNext()*******************************
* Function Description: Gets the next item in the linked list.

*Arguments: An iterator to an item.

*Return value: 	An iterator to the next item in the list.
				If the iterator is in the last item, behaviour is undefined. 

*Notes: Iterator must be to a valid list.

*Time complexity: O(1)
*****************************************************************************/
srlist_iter_ty SortedListPrev(const srlist_iter_ty iter);
/**********************************DListPrev()*******************************
* Function Description: Gets the previous item in the linked list.

*Arguments: An iterator to an item.

*Return value: 	An iterator to the previous item in the list.
				If the iterator is in the first item, behaviour is undefined. 

*Notes: Iterator must be to a valid list.

*Time complexity: O(1)
*****************************************************************************/
srlist_iter_ty SortedListEnd(const srlist_ty *list);
/***********************************DListEnd()*******************************
* Function Description: Gets the last item in the linked list.

*Arguments: A list's handler.

*Return value: An iterator to the dummy node.

*Notes: List must be previously created and valid.
		Returned iterator cannot be removed.

*Time complexity: O(1)
*****************************************************************************/
srlist_iter_ty SortedListInsert(void *data, srlist_ty *list);
/********************************SortedListInsert()***************************
* Function Description: Inserts a new item to a sorted list.

*Arguments: A list's handler.
			A pointer to a datum.

*Return value: 	An iterator to the new item.
				Returns iterator to last item in case of failure.

*Notes: Both data and list must be valid.

*Time complexity: O(n) - worst case n = num of elements.                                                                
*****************************************************************************/
srlist_iter_ty SortedListRemove(srlist_iter_ty iter);
/********************************SortedListRemove()***************************
* Function Description: Removes the item at iterator.

*Arguments: An iterator to the item.

*Return value: An iterator to the next item.

*Notes: Iterator must be valid. undefined behaviour if trying to remove first
		or last item.

*Time complexity: O(1) 
*****************************************************************************/
void *SortedListPopFront(srlist_ty *list);
/******************************Sorted`ListPopFront()***************************
* Function Description: Removes the item in front of the list.

*Arguments: The list.

*Return value: The poped item's data.

*Notes: List must be valid.
		List must not be empty.

*Time complexity: O(1) 
*****************************************************************************/
void *SortedListPopBack(srlist_ty *list);
/*******************************SortedListPopBack()**************************
* Function Description: Removes the item at the end of the list.

*Arguments: The list.

*Return value: The poped item's data.

*Notes: List must be valid.
		List must not be empty.

*Time complexity: O(1) 
*****************************************************************************/
void SortedListMerge(srlist_ty *src, srlist_ty *dest);
/*******************************SortedListMerge()****************************
* Function Description: Merges two sorted lists to a single sorted list.

*Arguments: Two sorted list's handlers.

*Return value: None.

*Notes: Lists must be valid.
		Lists must be sorted in the same manner.
		Function invalidates src list.

*Time complexity: O(n + m). n = num of elements in list src.
						m = num of elements in list dest.
*****************************************************************************/
void *SortedListGet(const srlist_iter_ty iter);
/********************************SortedListGet()******************************
* Function Description: Gets the value of the item at the iterator.

*Arguments: An iterator to the item.

*Return value: The value of the requested item.

*Notes: Iterator must be valid to an item previously inserted.

*Time complexity: O(1)
*****************************************************************************/
srlist_iter_ty SortedListFind(srlist_ty *list, srlist_iter_ty from,
                                   srlist_iter_ty to, const void *to_find);
/********************************SortedListFind()*****************************
* Function Description: Runs the defult compare function for each item between 
						iterator 'from' to 'to'.

*Arguments: A list 
			Iterator to a beginning item,
			iterator to an ending item ,
			Pointer to a data to find.

*Return value: Iterator to the found item.
			   Returns iterator "to" if not found.

*Notes: Iterators must be valid and from the same list.
		cmp_func pointer must be valid.

*Time complexity: O(n). n is the number of items between 'from' to 'to'.
*****************************************************************************/
srlist_iter_ty SortedListFindIf(match_func_ty is_match,
 		srlist_iter_ty from, srlist_iter_ty to, const void *to_find);
/**********************************SortedListFindIf()*************************
* Function Description: Runs a modified compare function for each item between 
						iterator 'from' to 'to'.

*Arguments: Iterator to a beginning item,
			iterator to an ending item ,
			A pointer to comparison function.
			Pointer to a data to find.

*Return value: Iterator to the found item.
			   Returns iterator "to" if not found.

*Notes: Iterators must be valid and from the same list.
		cmp_func pointer must be valid.

*Time complexity: O(n). n is the number of items between 'from' to 'to'.
*****************************************************************************/ 		
int SortedListIsSameIter(const srlist_iter_ty iter1, const srlist_iter_ty iter2);
/********************************SortedListIsSameIter()***********************
* Function Description: Compares iterators to each other. Finds if they are 
						the same.

*Arguments: Two iterators to compare.

*Return value: 	Returns 1 if both iterators are the same.
				Returns 0 otherwise.

*Notes: None.

*Time complexity: O(1)
*****************************************************************************/
size_t SortedListSize(const srlist_ty *list);
/*****************************SortedListSize()********************************
* Function Description: Counts the number of items in the list.

*Arguments: A list.

*Return value: 	The number of items in the list.

*Notes: List must be valid.

*Time complexity: O(n). n is number of items in the list.
*****************************************************************************/
int SortedListIsEmpty(const srlist_ty *list);
/*****************************SortedListIsEmpty()*****************************
* Function Description: Checks if the dlist is empty.

*Arguments: A handler to a list.

*Return value: 	Returns 1 if list is empty.
				Returns 0 otherwise.

*Notes: list must be previously created and valid.

*Time complexity: O(1) 
*****************************************************************************/
srlist_iter_ty SortedListForEach(srlist_iter_ty from, srlist_iter_ty to, 
										cmd_func_ty command, void *param);
/**********************************DListForEach()*****************************
* Function Description: Runs cmd_func for each item between iterator "from" 
						to iterator "to".

*Arguments: Iterator to a beginning item,
			Iterator to an ending item ,
			A pointer to cmd_func_ty type function,
			Pointer to a out parameter.

*Return value: Iterator to the ending item.
			   If fails return iterator to the node where failure occure.

*Notes: Iterators must be valid and from the same list.

*Time complexity: O(n). n is number of items between "from" to "to".
*****************************************************************************/

/***********************Noting to see here mr!!!!!!!!*************************/
/*#define NDEBUG *//*put in comment while debug*/

/*think about both options*/
	
/*
#ifndef NDEBUG 
#define DEBUG_ONLY(item) item

#else
#define DEBUG_ONLY(item)
*/

/*option 2*/
#ifdef NDEBUG
#define DEBUG_ONLY(item) 

#else
#define DEBUG_ONLY(item) item

#endif

struct sr_iter
{
	dlist_iter_ty internal_iter;
	DEBUG_ONLY(srlist_ty *list;)
};

#endif /*	ifndef __ILRD_SORTLIST_H__										*/

/*********************************End Of Header******************************/ 

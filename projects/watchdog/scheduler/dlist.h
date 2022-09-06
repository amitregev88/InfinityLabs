/******************************************************************************/
/*		Project:	Doubly linked list										  */
/*		File:		Doubly linked list.h									  */
/*		Date: 		15.06.2022												  */
/*		Name: 		HRD25													  */
/*		Reviewer:	Liel													  */
/*		Version: 	1.00													  */
/******************************************************************************/

#ifndef __ILRD_DLIST_H__
#define __ILRD_DLIST_H__

#include <stddef.h>   /* size_t */
#include "function.h"

#define __CMDNMATCH_H__
/******************************************************************************/

typedef struct dlist dlist_ty;

typedef struct dnode *dlist_iter_ty;

/***************************Function Prototypes********************************/

dlist_ty *DListCreate(void);
/********************************DListCreate()*********************************
* Function Description: Creates a new list.

*Arguments: None.

*Return value: 	An iterator to head of a new list
				Returns NULL if function failed.

*Notes: Must use DListDestroy function after usage.

*Time complexity: O(1)
*******************************************************************************/

void DListDestroy(dlist_ty *dlist);
/********************************DListDestroy()*********************************
* Function Description: Delete the list.

*Arguments: A list to delete.

*Return value: None.

*Notes: Argument must be valid.

*Time complexity: O(n). n is number of items in the list.
*******************************************************************************/

dlist_iter_ty DListBegin(const dlist_ty *dlist);
/**********************************DListBegin()*********************************
* Function Description: Finds the beginning of the linked list.

*Arguments: A linked list.

*Return value: Iterator to the first valid node.
			   Returned iterator cannot be removed.

*Notes: List must be previously created and valid, else behaviour is undefined.

*Time complexity: O(1)
*******************************************************************************/

dlist_iter_ty DListNext(const dlist_iter_ty iter);
/**********************************DListNext()**********************************
* Function Description: Gets the next item in the linked list.

*Arguments: An iterator to an item.

*Return value: 	An iterator to the next item in the list.
				If the iterator is in the last item, behaviour is undefined. 

*Notes: Iterator must be to a valid list.

*Time complexity: O(1)
*******************************************************************************/

dlist_iter_ty DListPrev(const dlist_iter_ty iter);
/**********************************DListPrev()**********************************
* Function Description: Gets the previous item in the linked list.

*Arguments: An iterator to an item.

*Return value: 	An iterator to the previous item in the list.
				If the iterator is in the first item, behaviour is undefined. 

*Notes: Iterator must be to a valid list.

*Time complexity: O(1)
*******************************************************************************/

dlist_iter_ty DListEnd(const dlist_ty *dlist);
/***********************************DListEnd()**********************************
* Function Description: Gets the last item in the linked list.

*Arguments: A list's handler.

*Return value: An iterator to the dummy node.

*Notes: List must be previously created and valid.
		Returned iterator cannot be removed.

*Time complexity: O(1)
*******************************************************************************/

dlist_iter_ty DListInsert(void *data, dlist_iter_ty iter);
/**********************************DListInsert()********************************
* Function Description: Inserts a new item to the list

*Arguments: An iterator to where to insert an item, a pointer to a datum.

*Return value: 	An iterator to the new item.
				Returns iterator to last item in case of failure.
																
*Notes: Data_size must be > 0. Both data and iterator must be valid.
		For insert to the front or back use the relevant push function
		otherwise undefine behaviour.

*Time complexity: O(1).                                                                 
*******************************************************************************/

dlist_iter_ty DListPushFront(void *data, dlist_ty *dlist);
/**********************************DListPushFront()*****************************
* Function Description: Inserts a new item to the front of the list.

*Arguments: A pointer to the list.
			A pointer to a datum.

*Return value: 	An iterator to the new item.
				Returns iterator to last item in case of failure.

*Notes: Data_size must be > 0. Both data and iterator must be valid.
																							
*Time complexity: O(1).
*******************************************************************************/

dlist_iter_ty DListPushBack(void *data, dlist_ty *dlist);
/**********************************DListPushBack()******************************
* Function Description: Inserts a new item to the back of the list.

*Arguments: A pointer to the list.
			A pointer to a datum.

*Return value: 	An iterator to the new item.
				Returns iterator to last item in case of failure.

*Notes: Data_size must be > 0. Both data and iterator must be valid.
																						
*Time complexity: O(1).
*******************************************************************************/

dlist_iter_ty DListRemove(dlist_iter_ty iter);
/**********************************DListRemove()********************************
* Function Description: Removes the item at iterator.

*Arguments: An iterator to the item.

*Return value: An iterator to the next item.

*Notes: Iterator must be valid. undefined behaviour if trying to remove first
		or last item.

*Time complexity: O(1) 
*******************************************************************************/

void *DListPopFront(dlist_ty *dlist);
/**********************************DListPopFront()******************************
* Function Description: Removes the item in front of the list.

*Arguments: The list.

*Return value: The value of the next item.

*Notes: List must be valid.

*Time complexity: O(1) 
*******************************************************************************/

void *DListPopBack(dlist_ty *dlist);
/**********************************DListPopBack()*******************************
* Function Description: Removes the item at the end of the list.

*Arguments: The list.

*Return value: The value of the previous item.

*Notes: List must be valid.

*Time complexity: O(1) 
*******************************************************************************/

dlist_iter_ty DListSplice(dlist_iter_ty from_src, dlist_iter_ty to_src, 
															dlist_iter_ty dest);
/**********************************DListSplice()********************************
* Function Description: Linked items from a sorce list to a dest list.
					    splices from 'from' to 'to' excluding to.
					    Linking the sorce list at the end of operation.
*Arguments: Iterator to a beginning item, iterator to an ending item - in the
			sorce list.
			Iterator to an item to insert before - in the dest list.

*Return value: An iterator to the first item spliced.

*Notes: Iterators must be valid.

*Time complexity: O(1) 
*******************************************************************************/

void *DListGet(const dlist_iter_ty iter);
/************************************DListGet()*********************************
* Function Description: Gets the value of the item at the iterator.

*Arguments: An iterator to the item.

*Return value: The value of the requested item.

*Notes: Iterator must be valid to an item previously inserted.

*Time complexity: O(1)
*******************************************************************************/

dlist_iter_ty DListSet(const dlist_iter_ty iter, void *data);
/************************************DListSet()*********************************
* Function Description: Changes the value of the data at the iterator.

*Arguments: An iterator, a pointer to data.

*Return value: 	Iterator to the item with the set value.

*Notes: Item_size must be > 0. Iterator and data address must be valid.

*Time complexity: O(1)
*******************************************************************************/

dlist_iter_ty DListForEach(dlist_iter_ty from, dlist_iter_ty to, 
											  cmd_func_ty command, void *param);
/**********************************DListForEach()*******************************
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
*******************************************************************************/

dlist_iter_ty DListFind(dlist_iter_ty from, dlist_iter_ty to, 
							               match_func_ty is_match, void *param);
/************************************DListFind()********************************
* Function Description: Runs the compare function for each item between iterator
						'from' to 'to'.

*Arguments: Iterator to a beginning item,
			iterator to an ending item ,
			A pointer to match_func_ty type function,
			Pointer to a out parameter.

*Return value: Iterator to the found item.
			   Returns iter to last item if not found.

*Notes: Iterators must be valid and from the same list.
		cmp_func pointer must be valid.

*Time complexity: O(n). n is the number of items between 'from' to 'to'.
*******************************************************************************/

int DListMultiFind(dlist_ty *dlist_src, dlist_ty *dlist_out,
										  match_func_ty is_match, void *param);
/********************************DListMultyFind()*******************************
* Function Description: Copies all matching data refrences from list src to
						list out.

*Arguments: A sorce list.
			An out list.
			A pointer function to match function.
			An out param.

*Return value: 	0 In Success.
				In case of failure return 1.           

*Notes: Lists must be valid. If match is found a new item will be adding to out
		list.
		Match function pointer must be valid.

*Time complexity: O(n) n is the number of items in source list.
*******************************************************************************/ 

int DListIsSameIter(const dlist_iter_ty iter1, const dlist_iter_ty iter2);
/**********************************DListIsSameIter()****************************
* Function Description: Compares iterators to each other. Finds if they are the
						same.

*Arguments: Two iterators to compare.

*Return value: 	Returns 1 if both iterators are the same.
				Returns 0 otherwise.

*Notes: None.

*Time complexity: O(1)
*******************************************************************************/

size_t DListSize(const dlist_ty *dlist);
/*********************************DListSize()***********************************
* Function Description: Counts the number of items in the list.

*Arguments: A list.

*Return value: 	The number of items in the list.

*Notes: List must be valid.

*Time complexity: O(n). n is number of items in the list.
*******************************************************************************/

int DListIsEmpty(dlist_ty *dlist);
/*******************************DListIsEmpty()**********************************
* Function Description: Checks if the given list is empty.

*Arguments: A list.

*Return value: 	1 if list is empty.
				0 otherwise.

*Notes: List must be valid.

*Time complexity: O(1)
*******************************************************************************/

#endif /*	ifndef __ILRD_DLIST_H__											  */

/*********************************End Of Header********************************/ 

/******************************************************************************/
/*	Project:   Priority queue                          						  */
/*  Name:      HRD25        		                                    	  */
/*	Date:      21.06.2022 						                              */
/*  File:	   pqueue.h                                      				  */
/*	Version:   2.0										                  */
/*	Reviewer:  Rina                                                     	  */
/******************************************************************************/
#ifndef	__ILRD_PQUE_H__
#define	__ILRD_PQUE_H__	

#include <stddef.h>  /* size_t */	

#include "function.h"

typedef struct pque pque_ty;

/*****************************API Functions**********************************/
/****************************************************************************
* Function Description: Creates a new priority queue
*Arguments: priority function.
*Return value: pointer to the new pqueue, if failed returns NULL.
*Notes: User must use destroy at the end of use
*Time complexity: O(1)
*****************************************************************************/
pque_ty *PQCreate(is_higher_priority is_higher); 

/****************************************************************************
* Function Description: Destroys the given pqueue
*Arguments: a pointer to pqueue
*Return value: None.
*Notes: pqueue must be valid otherwise undefined behavior.
*Time complexity: O(n)
*****************************************************************************/
void PQDestroy(pque_ty *pque);

/****************************************************************************
* Function Description: Adds a new element to the pqueue 
*Arguments: A pqueue, data to add and it's priority value
*Return value: Return 0 on success, otherwise 1.
*Notes: pqueue must be valid otherwise undefined behavior.
*Time complexity: O(n)
*****************************************************************************/
int PQEnqueue(pque_ty *pque, void *data);

/****************************************************************************
* Function Description: Removes the element from the pqueue with the 
						higher priorty.
*Arguments: A pointer to a pqueue
*Return value: A pointer to the data stored in the removed element
*Notes: pqueue must be valid otherwise undefined behavior.
*Time complexity: O(1)
*****************************************************************************/
void *PQDequeue(pque_ty *pque);

/****************************************************************************
* Function Description: Returns the value of the element with the higher 
						priority in the pqueue
*Arguments: A pointer to a pqueue.
*Return value: A pointer to the data stored in the first element.
*Notes: pqueue must be valid otherwise undefined behavior.
*Time complexity: O(1)
*****************************************************************************/
void *PQPeek(const pque_ty *pque);

/****************************************************************************
* Function Description: Checks if the Pqueue is empty
*Arguments: A pointer to a pqueue
*Return value: Return 1 if true, otherwise 0.
*Notes: pqueue must be valid otherwise undefined behavior.
*Time complexity: O(1)
*****************************************************************************/
int PQIsEmpty(const pque_ty *pque);

/****************************************************************************
* Function Description: Returns the number of elements stored in the pqueue.
*Arguments: A pointer to a pqueue.
*Return value: The number of elements stored in the pqueue.
*Notes: pqueue must be valid otherwise undefined behavior.
*Time complexity: O(n)
*****************************************************************************/
size_t PQSize(const pque_ty *pque);

/****************************************************************************
* Function Description: Removes all the elements stored in the pqueue.
*Arguments: A pointer to a pqueue
*Return value: None
*Notes: pqueue must be valid otherwise undefined behavior.
*Time complexity: O(n)
*****************************************************************************/
void PQClear(pque_ty *pque);

/****************************************************************************
* Function Description: Removes the first matched element according to the is 
						match function. (with lower priority).
*Arguments: A pointer to a pqueue ,a match function pointer and pointer to 
			param. 
*Return value: A pointer to the data stored in the removed element, 
		if not found return null
*Notes: pqueue and match function must be valid otherwise undefined 
		behavior.
*Time complexity: O(n)
*****************************************************************************/
void *PQErase(pque_ty *pque, match_func_ty is_match, void *param);

/****************************************************************************/
 #endif     /* __ILRD_PQUE_H__                                              */ 
/****************************************************************************/

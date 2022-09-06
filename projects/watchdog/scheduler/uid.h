/****************************************************************************/
/*	Project:   UID                                   						*/
/*  Name:      HRD25        		                                    	*/
/*	Date:      21.06.2022 						                            */
/*  File:	   uid.h                                         				*/
/*	Version:   1.0											                */
/*	Reviewer:  Rina                                                     	*/
/****************************************************************************/

#ifndef	__ILRD_UID_H__
#define	__ILRD_UID_H__

#include <sys/types.h>	/*pid_t   */ 
#include <stddef.h>		/* size_t */
#include <time.h>		/* time_t */

typedef struct uid
{
	pid_t pid;
	size_t counter;
	time_t timestamp;
}ilrd_uid_ty;	

extern const ilrd_uid_ty BadUID;


/****************************************************************************
* Function Description: Creates a new uid.

*Arguments: None.

*Return value: Returns the new uid, in case of failure return BadUID.

*Notes: None.

*Time complexity: O(1)
*****************************************************************************/
ilrd_uid_ty UIDCreate(void);
/****************************************************************************
* Function Description: Checks if the two given uids are equal.

*Arguments: Two uids. 

*Return value: Returns 1 if true,
			   otherwise 0.	

*Notes: None.

*Time complexity: O(1)
*****************************************************************************/
int UIDIsEqual(ilrd_uid_ty uid1, ilrd_uid_ty uid2);
/****************************************************************************/
 #endif     /* __ILRD_UID_H__                                               */ 
/****************************************************************************/

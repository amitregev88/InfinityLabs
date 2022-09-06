/******************************************************************************/
/*	Project:	UID														  	  */
/*	File:		uid.c														  */
/*	Date: 		15.06.2022													  */
/*	Name: 		Sapir 														  */
/*	Reviewer:	Haggai														  */
/*	Version: 	1.00														  */
/******************************************************************************/
#include <assert.h> /*assert()*/
#include <unistd.h> /*getpid()*/
#include "uid.h" 

enum {FALSE = 0, TRUE = 1};
enum {SUCCESS = 0, FAILURE = 1};

const ilrd_uid_ty BadUID = {0}; 
/******************************************************************************/
ilrd_uid_ty UIDCreate(void)
{
	static size_t count = 0;
	
	ilrd_uid_ty uid = {0};
	uid.pid = getpid();
	uid.counter = count;
	
	if (0xFFFFFFFF == count)
	{
		return BadUID;	
	}
	uid.timestamp = time(NULL);
	
	++count;
	return uid;
}

/******************************************************************************/
int UIDIsEqual(ilrd_uid_ty uid1, ilrd_uid_ty uid2)
{
	
	if ((uid1.pid == uid2.pid) && (uid1.counter == uid2.counter) && 
											 (uid1.timestamp == uid2.timestamp))
	{
		return (TRUE);
	}
	return (FALSE);
}


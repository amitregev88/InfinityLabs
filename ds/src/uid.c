/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 05.11.22
* OL124 UID
*************************************************************************************/
#include <time.h>   /*time_t*/
#include <unistd.h> /*pid_t*/
#include <uid.h>   
#include <stdio.h>


const uid_ty UID_INVALID = {0,0,0};

/* Return 1 if UID number is valid and 0 if not valid */
uid_ty GetUID(void)
{
	static unsigned long count = 0;
	
	uid_ty new_uid = {0,0,0};
	
	new_uid.timestamp = time(NULL);
	
	if (new_uid.timestamp >= 0)
	{
		new_uid.counter = ++count;
		new_uid.pid = getpid();
	}
								
	else			
	{
		new_uid.timestamp = 0;	
	}
	
	return new_uid;
}



/*return 1 if two UUID are same and 0 otherwise*/
int UIDIsSame(uid_ty uid1, uid_ty uid2)
{
	return ((uid1.counter == uid2.counter) && (uid1.timestamp == uid2.timestamp) && (uid1.pid == uid2.pid));
}







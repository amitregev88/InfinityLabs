/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 05.11.22
* OL124 UID
*************************************************************************************/
#include <time.h>   /*time_t*/
#include <unistd.h> /*pid_t*/

#include <pthread.h> /*_atomic_fetch_add*/


#include "uid.h"   


const uid_ty UID_INVALID = {0,0,0}; /* UID to check the Validity vs */

/* Return UID */
uid_ty GetUID(void)
{
	static unsigned long count = 1;
	
	uid_ty new_uid = {0,0,0};
	
	time_t t = time(NULL);
	
	if (-1 != t)
	{
		new_uid.counter = __atomic_fetch_add(&count,__ATOMIC_SEQ_CST);
		new_uid.pid = getpid();
		new_uid.timestamp = t;
	}
	
	return new_uid;
}



/*return 1 if two UUID are same and 0 otherwise*/
int UIDIsSame(uid_ty uid1, uid_ty uid2)
{
	return ((uid1.counter == uid2.counter) && (uid1.timestamp == uid2.timestamp) && (uid1.pid == uid2.pid));
}







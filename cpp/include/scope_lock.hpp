/****************************************************************************/
/*	Project:	Scope Lock												    */
/*	File:		scope_lock.hpp												*/
/*	Date: 		30/10/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:														        */
/****************************************************************************/

#ifndef __ILRD_HRD25_SCOPELOCK_HPP__
#define __ILRD_HRD25_SCOPELOCK_HPP__

namespace ilrd 
{

class ScopeLock
{
public:

	ScopeLock(Thread_Mutex_Guard *);
	~ScopeLock();
	
private:    
	acquire();
	realese();
	Thread_Mutex_Guard *m_guard;
	ScopeLock(const Thread_Mutex_Guard&) //do not impliment. cctor is disable.
	ScopeLock& operator=(ScopeLock& other_) //assigment operator is disable.
}

ScopeLock::ScopeLock()

}

/****************************************************************************/
#endif 	//__ILRD_HRD25_SCOPELOCK_HPP__							
/*********************************End Of Header******************************/

/****************************************************************************/
/*	Project:	Scope Lock												    */
/*	File:		scope_lock.hpp												*/
/*	Date: 		30/10/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:														        */
/****************************************************************************/

#ifndef __ILRD_HRD25_SCOPELOCK_HPP__
#define __ILRD_HRD25_SCOPELOCK_HPP__

#include <iostream>
#include <pthread.h>

namespace ilrd 
{

template <typename LOCK> /*Class LOCK has a lock  and unlock method*/
class ScopeLock
{
public:

	explicit ScopeLock(LOCK& lock);
	~ScopeLock();
	
private:    

	LOCK& m_lock;
	ScopeLock(const ScopeLock&); //do not impliment. cctor is disable.
	ScopeLock& operator=(ScopeLock& other_); //assigment operator is disable.
};

template <typename LOCK>
ScopeLock<LOCK>::ScopeLock(LOCK& lock_): 
 m_lock(lock_)
{
    m_lock.Lock();
}

template <typename LOCK>
ScopeLock<LOCK>::~ScopeLock()
{
    m_lock.Unlock();
}

} // namespace ilrd
/****************************************************************************/
#endif 	//__ILRD_HRD25_SCOPELOCK_HPP__							
/*********************************End Of Header******************************/

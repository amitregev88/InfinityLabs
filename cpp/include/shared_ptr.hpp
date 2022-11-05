/*******************************************************************************
*								   								               *
*	PROJECT: shared_ptr            		    					               *
*	DATE: 2022-10-31						   					               *
*	AUTHOR: SAAEB SHIBLI cw(202				   					               *
*	REVIEWER: 						   							               *
*	VERSION: 1.0 						   						               *
*								   								               *
*******************************************************************************/

#ifndef __ILRD_HRD25_SHARED_PTR_HPP__
#define __ILRD_HRD25_SHARED_PTR_HPP__

#include "utility.hpp"
namespace ilrd
{

template <typename T>
class SharedPtr
{
public:
	explicit SharedPtr(T* ptr = NULL_PTR);
	SharedPtr(SharedPtr<T> &o_);
	~SharedPtr() NO_EXCEPT;

	T& operator*() const;
	T* operator->() const;
	SharedPtr<T>& operator=(T* ptr);
	bool operator==(SharedPtr<T>&);
	bool operator!=(SharedPtr<T>&);
	bool operator!(SharedPtr<T>&);



private:
	void * operator new(size_t);	//DO NOT IMP
	T* m_ptr;
	size_t *m_count;
	RCPtr *m_rcp;
};

template <typename T>
class RCPtr
{
public:
	explicit RCPtr(T *ptr_ = NULL_PTR);
	RCPtr(const RCPtr& o_);
	~RCPtr() NOEXCEPT;
	
	RCPtr<T>& operator=(const RCPtr<T>&);
	T* Get();
private:
	void Inc();
	void Dec();
	T* m_ptr;
	size_t m_count;
};

/**********************************************IMP***********************************************/

template <typename T>
SharedPtr<T>::SharedPtr(T*ptr): m_ptr(ptr), m_count(new size_t[1])
{};

template <typename T>
SharedPtr<T>::SharedPtr(SharedPtr<T> &o_):m_ptr(o_.m_ptr), m_count(++*o_.m_count)
{};


template <typename T>
SharedPtr<T>::~SharedPtr() NO_EXCEPT
{
	--m_count;
	if (!m_count)
	{
		delete m_ptr;
		delete ptr;
	}
};

template <typename T>
T& SharedPtr<T>:: operator*() const
{
	return *m_ptr;
}

template <typename T>
T* SharedPtr<T>:: operator->() const
{
	return m_ptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(T* ptr)
{
	m_ptr = ptr;
	m_count = new size_t(1);
}

} //end ilrd
#endif // end __ILRD_HRD25_SHARED_PTR_HPP__
/*********************************End Of Header******************************/
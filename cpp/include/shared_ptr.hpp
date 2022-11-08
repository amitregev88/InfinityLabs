/*******************************************************************************
**	PROJECT: Shared Pointer        		    					               *
*	DATE: 31/10/22							   					               *
*	AUTHOR: Amit Regev						   					               *
*	REVIEWER: 						   							               *
*	VERSION: 1.0 						   						               *
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
    SharedPtr(const SharedPtr<T> &o_);
    ~SharedPtr() NO_EXCEPT;

    SharedPtr<T>& operator=(const SharedPtr<T> &o_);
    T& operator*() const;
    T* operator->() const;
    bool operator==(const SharedPtr<T>&) const;
    bool operator!=(const SharedPtr<T>&) const;
    operator bool() const;

    template <typename C>
    operator SharedPtr<C>() { SharedPtr<C> ret(new T( *(m_ptr) )); return ret; }

private:
    T *m_ptr;
    size_t *m_rc;

    void Inc() const;
    void DecNDelete() NO_EXCEPT;
    void* operator new(size_t);    //DO NOT IMP
};

/*******************************NOTHING TO SEE HERE****************************/
template <typename T>
SharedPtr<T>::SharedPtr(T* ptr):
 m_ptr(ptr),
 m_rc( new size_t(1) )
{}

template <typename T>
SharedPtr<T>::SharedPtr(const SharedPtr<T> &o_):
 m_ptr(o_.m_ptr),
 m_rc(o_.m_rc)
{
    Inc();    
}

template <typename T>
SharedPtr<T>::~SharedPtr() NO_EXCEPT
{
    DecNDelete();
}

template <typename T>
void SharedPtr<T>::DecNDelete() NO_EXCEPT
{
    --*m_rc;

    if (0 == *m_rc)
    {
        delete m_ptr;
        delete m_rc;
    }
}

template <typename T>
void SharedPtr<T>::Inc() const
{
    ++*m_rc;
}

template <typename T>
T& SharedPtr<T>::operator*() const
{
    return *m_ptr;
}

template <typename T>
T* SharedPtr<T>::operator->() const
{
    return m_ptr;
}

template <typename T>
SharedPtr<T>& SharedPtr<T>::operator=(const SharedPtr<T> &o_)
{
    o_.Inc();
    DecNDelete();

    m_ptr = o_.m_ptr;
    m_rc = o_.m_rc;

    return *this;
}

template <typename T>
bool SharedPtr<T>::operator==(const SharedPtr<T>& o_) const
{
    return (m_ptr == o_.m_ptr);
}

template <typename T>
bool SharedPtr<T>::operator!=(const SharedPtr<T>& o_) const
{
    return (m_ptr != o_.m_ptr);
}

template <typename T>
SharedPtr<T>::operator bool() const
{
    return m_ptr;
}
/******************************************************************************/
} // namespace ilrd
#endif //  __ILRD_HRD25_SHARED_PTR_HPP__

/****************************************************************************/
/*	Project:	OstreamIter											        */
/*	File:		ostream_iter.hpp											*/
/*	Date: 		28/09/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:														        */
/****************************************************************************/

#ifndef __ILRD_HRD25_OSTREAMITER_HPP__
#define __ILRD_HRD25_OSTREAMITER_HPP__

#include <iostream> // ostream


namespace ilrd 
{

template <typename T> // T should support ostream's << operator.

class OstreamIter
{
private:
    
    class Proxy;
    

public:
    
    inline explicit OstreamIter(std:: ostream &o_);

    inline OstreamIter& operator++();
    inline Proxy operator*();
    //generated cctor
    //disable assignment operator

private:

    std:: ostream& m_stream;

}
/*******************************************************************/
template<typename T>
class OstreamIter::Proxy // no assignment.
{
public:

    inline explicit Proxy(std::ostream&);
    //generated cctor and dtor
    //disable assignment operator

    inline const T& operator=(const T&);

private:

    std:: ostream& m_stream;

}
/**************************************************/
template<typename T>
inline OstreamIter:: OstreamIter(std:: ostream &o_):m_stream(o_)
{};
/**************************************************/
template<typename T>

inline OstreamIter<T>& OstreamIter<T>::operator++(){return *this;};

/****************************************************/
template<typename T>

inline OstreamIter<T>::Proxy OstreamIter<T>::operator*()
{
   return Proxy(m_stream);
}
/****************************************************/
template<typename T>

inline  OstreamIter<T>::Proxy Proxy(std::ostream& o_):m_stream(o_)
{};
/***************************************************/
template<typename T>
inline const T& OstreamIter<T>::Proxy::operator=(const T& num_)
{
	m_stream << num_;

	return (num_);
}

} //namespace ilrd

#endif 	//ifndef __ILRD_HRD25_OstreamITER_HPP__								
/*********************************End Of Header******************************/
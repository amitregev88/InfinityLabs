/****************************************************************************/
/*	Project:	RCstring												    */
/*	File:		rcstring.hpp												*/
/*	Date: 		21/09/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:   Saaeb Shibli										        */
/****************************************************************************/

#include <iostream> //cout
#include <cassert>  // assert
#include <cstring> //strlen , memcpy

#include "utility.hpp"
 #include "rcstring.hpp"


namespace ilrd
{

String::String(const char *str_): m_str(AllocNcpy(str_)) {} 

char *String:: AllocNcpy(const char *s_) //static
{
    assert(s_);


    size_t len = strlen(s_) + 1;
    size_t buff_size = len + sizeof(size_t);

    size_t *pool = static_cast<size_t *>(operator new(buff_size));

    *pool = 1;
    
    char *ret = reinterpret_cast<char *>(pool + 1);
    
    memcpy(ret, s_, len);
    
    return ret;
}
/****************copy constractor func************************/
String::String(const String& other_) 
{
    m_str = other_.m_str;
    Inc();
}
/*******************************************************/
void String:: Inc() const
{
    ++GetMetaData();
}
/******************************************************/
size_t& String::GetMetaData() const
{  
    return *(reinterpret_cast<size_t *>(m_str) -1);
}
/************************Dtor****************************/
String::~String() NO_EXCEPT 
{
    DecNDelete();
}
/********************************************************/
void String:: DecNDelete() NO_EXCEPT //static
{  
    size_t& rc = GetMetaData();
    --rc;
    if (0 == rc)
    {
        operator delete(&rc);       
    }
}
/***************operator assingment func********************/
String& String::operator=(String& other_)
{  
    //handels self assignment
    other_.Inc();

    DecNDelete();

    m_str = other_.m_str;

    return *this;      
}
 /***************operator [] func**************************/ 
 String::CharProxy String::operator[](size_t idx_)
 {
    assert (idx_ < Length());

    return CharProxy(this, idx_);
 }
 /***************operator [] func const**************************/ 
 char String::operator[](size_t idx_) const
 {
    assert (idx_ < Length());

    return Get(idx_);
 }
 /******************************************************************/
 String::CharProxy::CharProxy(String *str_, size_t idx_): m_str(str_), m_idx(idx_) {}
/***************operator char()*****************************************/ 
 String::CharProxy::operator char() const
{
	return m_str->Get(m_idx);
}
/****************************************************************************/
char String::CharProxy::operator=(const CharProxy& o_)
{
	return operator=(o_.operator char());
}
/****************************************************************************/
 char String::Get(size_t idx_) const
{
	assert(idx_ < Length());

	return m_str[idx_];
}
/*************************************************************************/
char String::CharProxy::operator=(char ch_)
{
    return m_str->Set(ch_, m_idx);
}
/****************************************************************************/
char String::Set(char ch_, size_t idx_)
{
	if (1 < GetMetaData())
	{
		DecNDelete();
		m_str = AllocNcpy(m_str); //copy on right
	}

	m_str[idx_] = ch_;

	return ch_;
}
/***********************************************************************/

}//namespace ilrd 



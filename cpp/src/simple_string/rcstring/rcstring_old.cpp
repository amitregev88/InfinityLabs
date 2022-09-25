#include <iostream> //cout
#include <cassert> 
#include <cstring> //strlen , memcpy
#include "rcstring.hpp"

#include "utility.hpp"



using namespace ilrd;



char * String:: AllocNcpy(const char *s)
{
    assert(s);
    size_t buff_size = strlen(s) + 1 + sizeof(size_t);

    char *pool = static_cast<char *>(operator new(buff_size));

    memset(pool,0,sizeof(size_t));

    return pool + sizeof(size_t);
}

/*******************************************************/
void String:: Inc()
{
    ++CountImp();
    
}
/******************************************************/
 size_t CountImp()
{  
    *(reinterpret_cast<size_t *>(m_str) -1);
}
/******************************************************/
void String:: DecNdelete() NO_EXCEPT
{  
    if ( 0 == --CountImp())
    {

        delete(&CountImp());
    }
}
/************************Ctor*****************************/
String::String(const char *str)
{   
    size_t len = strlen(str) + 1 ;
    
    m_str = AllocNcpy(str);

    memcpy(m_str,str, len);

    Inc();
}
/************************Dtor****************************/
String::~String()
{
    DecNdelete();
}
/***************operator assingment func********************/
String& String::operator=(const String& other_str)
{
    
    if(other_str.Cstr() != m_str)
    {
        m_str = other_str.m_str;
        Inc();
    } 

    return *this;      
}    
/****************copy constractor func************************/
String::String(const String& other_str) 
{
    m_str = other_str.m_str;
    Inc();
}
/***************member function*****************************/
size_t String:: Length() const
{
    return strlen(m_str);
}
/***************member function****************************/
const char *String::Cstr()const
{
    return m_str;
}
/******************member function*****************************/
bool operator==(const String&s1, const String&s2)
{
    return(0 == (strcmp(s1.Cstr(), s2.Cstr())));
}
/******************member function*****************************/
bool operator==(const String&s1, const char *s)
{
    return(0 == (strcmp(s1.Cstr(), s)));
}
/******************member function*****************************/
bool operator==(const char *s, const String& s1)
{
    return(0 == (strcmp(s, s1.Cstr())));
}
/******************member function*****************************/
bool operator<(const String& s1, const String& s2)
{
    return(0 > (strcmp(s1.Cstr(), s2.Cstr())));
}
/******************member function*****************************/
bool operator<(const String&s1, const char* s)
{
    return(0 > (strcmp(s1.Cstr(), s)));
}
/******************member function*****************************/
bool operator<(const char *s, const String& s1)
{
    return(0 > (strcmp(s, s1.Cstr())));
}
/******************member function*****************************/
bool operator>(const String& s1, const String& s2)
{
    return(0 < (strcmp(s1.Cstr(), s2.Cstr())));
}
/******************member function*****************************/
bool operator>(const String&s1, const char* s)
{
    return(0 < (strcmp(s1.Cstr(), s)));
}
/******************member function*****************************/
bool operator>(const char *s, const String& s1)
{
    return(0 < (strcmp(s, s1.Cstr())));
}
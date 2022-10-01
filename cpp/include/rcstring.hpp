/****************************************************************************/
/*	Project:	RCstring												    */
/*	File:		rcstring.hpp												*/
/*	Date: 		21/09/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:														        */
/****************************************************************************/

#ifndef __ILRD_HRD25_RCSTRING_HPP__
#define __ILRD_HRD25_RCSTRING_HPP__

#include <iostream> // ostream
#include <cstring> // strcmp

#include "utility.hpp"

namespace ilrd 
{

class String;

inline bool operator==(const String&, const String&);
inline bool operator==(const String&, const char*);
inline bool operator==(const char*, const String&);

inline bool operator<(const String&, const String&);
inline bool operator<(const String&, const char*);
inline bool operator<(const char*, const String&);

inline bool operator>(const String&, const String&);
inline bool operator>(const String&, const char*);
inline bool operator>(const char*, const String&);
inline std::ostream& operator<<(std::ostream& os_, const String& str_);


class String
{

private:    
    class CharProxy;

    
public:

    explicit String(const char *str_= "");
    String(const String& other_);
    ~String() NO_EXCEPT;
    
    String& operator=(String& other_);
    CharProxy operator[](size_t idx_);
    char operator[](size_t idx_) const;

      
    inline size_t Length() const;
    inline const char *Cstr() const;

    char Get(size_t idx_) const;
    char Set(char ch_, size_t idx_);

private:    
    static char *AllocNcpy(const char *str_);
    void DecNDelete() NO_EXCEPT;
    void Inc() const;
    size_t& GetMetaData() const;

    char *m_str;
};

class String::CharProxy
{
public:
    explicit CharProxy(String *str_, size_t idx_);
    operator char() const;
    char operator=(char c_);
    char operator=(const CharProxy& o_);

private:
    String *const m_str;
    const size_t m_idx;
};
/****************************************************************************/
inline size_t String::Length() const
{
	return strlen(m_str);
}
/****************************************************************************/
inline const char *String::Cstr() const
{
	return m_str;
}
/*************************************************************/
inline bool operator==(const String&s1, const String&s2)
{
    return(0 == (strcmp(s1.Cstr(), s2.Cstr())));
}
/**************************************************************/
inline bool operator==(const String&s1, const char *s)
{
    return(0 == (strcmp(s1.Cstr(), s)));
}
/**************************************************************/
inline bool operator==(const char *s, const String& s1)
{
    return(0 == (strcmp(s, s1.Cstr())));
}
/**************************************************************/
inline bool operator<(const String& s1, const String& s2)
{
    return(0 > (strcmp(s1.Cstr(), s2.Cstr())));
}
/**************************************************************/
inline bool operator<(const String&s1, const char* s)
{
    return(0 > (strcmp(s1.Cstr(), s)));
}
/**************************************************************/
inline bool operator<(const char *s, const String& s1)
{
    return(0 > (strcmp(s, s1.Cstr())));
}
/**************************************************************/
inline bool operator>(const String& s1, const String& s2)
{
    return(0 < (strcmp(s1.Cstr(), s2.Cstr())));
}
/**************************************************************/
inline bool operator>(const String&s1, const char* s)
{
    return(0 < (strcmp(s1.Cstr(), s)));
}
/**************************************************************/
inline bool operator>(const char *s, const String& s1)
{
    return(0 < (strcmp(s, s1.Cstr())));
}
/****************************************************************************/
inline std::ostream& operator<<(std::ostream& os_, const String& str_)
{
	return os_ << str_.Cstr();
}
/****************************************************************************/

}//namespace ilrd
/****************************************************************************/
#endif 	//ifndef __ILRD_HRD25_RCSTRING_HPP__								
/*********************************End Of Header******************************/

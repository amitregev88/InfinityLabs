/****************************************************************************/
/*	File:		string.cpp													*/
/*	Date: 		15/09/2022													*/
/*	Name: 		Amit Regev												    */
/****************************************************************************/
#include <cassert>	// assert()
#include <cstddef>	// size_t
#include <cstring>	// strlen(), memcpy()

#include "simple_str.hpp"
#include "utility.hpp"		

namespace ilrd	
{
/*******************************Function Definitions*************************/
String::String(const char *str_): m_str(AllocAndCopyIMP(str_))
{}  	
/****************************************************************************/
String::~String() NO_EXCEPT
{
	delete[] m_str;
	m_str = NULL_PTR; 
}
/****************************************************************************/
String::String(const String& o_): m_str(AllocAndCopyIMP(o_.m_str))
{}
/****************************************************************************/
String & String::operator=(const String& o_)
{
	// Handles self assignment
	char *to_delete = m_str;
	m_str = AllocAndCopyIMP(o_.m_str);

	delete[] to_delete;

	return *this;
}
/****************************************************************************/
size_t String::Length() const
{
	return (strlen(m_str));
}
/****************************************************************************/
const char *String::Cstr() const
{
	return (m_str);
}
/*****************************Operators**************************************/
bool operator==(const char *literalstr_, const String& str_)
{
	assert(str_.Cstr());

	return (!strcmp(literalstr_, str_.Cstr()));
}
/****************************************************************************/
bool operator==(const String& str_, const char *literalstr_)
{
	return (!strcmp(str_.Cstr(),literalstr_));
}
/****************************************************************************/
bool operator==(const String& s1_, const String& s2_)
{
	return (!strcmp(s1_.Cstr(),s2_.Cstr()));
}
/****************************************************************************/
bool operator>(const String& s1_, const String& s2_)
{
	return (strcmp(s1_.Cstr(), s2_.Cstr()) > 0);
}
/****************************************************************************/
bool operator>(const String&s1_, const char* str_)
{
	return (strcmp(s1_.Cstr(), str_) > 0);
}
/****************************************************************************/
bool operator>(const char* str_, const String& s1_)
{
	return (strcmp(str_, s1_.Cstr()) > 0);
}
/****************************************************************************/

bool operator<(const String& s1_, const String& s2_)
{
	return (strcmp(s1_.Cstr(), s2_.Cstr()) < 0);
}
/****************************************************************************/
bool operator<(const String& s1_, const char* str_)
{
	return (strcmp(s1_.Cstr(), str_) < 0);
}
/****************************************************************************/
bool operator<(const char* str_, const String& s1)
{
	return (strcmp(str_, s1.Cstr()) < 0);
}
/****************************************************************************/
std::ostream& operator<<(std::ostream& os_, const String& str_)
{
	return os_ << str_.Cstr();
}
/****************************************************************************/

//static
char* String::AllocAndCopyIMP(const char *str_)
{
	assert(str_);
	// get string length
	size_t length = strlen(str_) + 1;
	
	// allocate new buffer
	char *dest = new char[length];
	// copy
	memcpy(dest, str_, length);

	return dest;
}

} //end ilrd namespace 
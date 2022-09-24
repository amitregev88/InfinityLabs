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
String::~String()
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
	assert(str_);

	return (!strcmp(literalstr_, str_.m_str));
}

/****************************************************************************/
bool String::operator>(const String& o_) const
{
	return (strcmp(m_str, o_.m_str,r) > 0);
}
/****************************************************************************/
bool String::operator<(const String &o_) const
{
	return (strcmp(m_str, o_.m_str,r) < 0);
}

/****************************************************************************/
bool String::operator==(const String& o_) const
{
	
	return (strcmp(m_str, o_.m_str,r) == 0);
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

}
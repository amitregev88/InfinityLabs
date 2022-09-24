/****************************************************************************/
/*	Date: 		15/09/2022													*/
/*	Name: 		Amit Regev   												*/
/*	Reviewer:																*/
/****************************************************************************/

#ifndef __SIMPLE_STR__
#define __SIMPLE_STR__

#include <iostream>	// ostream
#include <cstddef>  // size_t

namespace ilrd
{

class String;

std::ostream& operator<<(std::ostream& os_, const String& string_);
bool operator==(const char *literalString_, const String& string_);

/*******************************Function Prototypes*************************/
class String
{
public:
	explicit String(const char *);	// no NULL allowed.
	String(const String& o_);
	~String();

	size_t Length() const;
	const char *Cstr() const;

    String &operator=(const String& o_);
	bool operator==(const String& o_) const;
	bool operator>(const String& o_) const;
	bool operator<(const String &o_) const;

private:
	char *m_str;
    size_t m_arraySize;
	size_t m_stringLength;
	
	friend bool operator==(const char *literalString_, const String& string_);
	static char* AllocAndCopyIMP(const char *string_);
};
}	// namespace ilrd
#endif /*	ifndef __SIMPLE_STR_HPP__									*/
/*********************************End Of Header******************************/


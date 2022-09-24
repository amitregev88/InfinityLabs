/****************************************************************************/
/*	Date: 		15/09/2022													*/
/*	Name: 		Amit Regev   												*/
/*	Reviewer:																*/
/****************************************************************************/

#ifndef __ILRD25__SIMPLE_STR__
#define __ILRD25__SIMPLE_STR__

#include <iostream>	// ostream
#include <cstddef>  // size_t
#include "utility.hpp"  


namespace ilrd
{

class String;

std::ostream& operator<<(std::ostream& os_, const String& str_);
bool operator==(const String&, const char*);
bool operator==(const char*, const String&);
bool operator==(const String&, const String&);

bool operator>(const String&, const String&);
bool operator>(const String&, const char*);
bool operator>(const char*, const String&);

bool operator<(const String&, const String&);
bool operator<(const String&, const char*);
bool operator<(const char*, const String&);

/*******************************Function Prototypes*************************/
class String
{
public:
	explicit String(const char *str_ = "");	// no NULL allowed.
	String(const String& str_);
	~String() NO_EXCEPT;

	String& operator=(const String& o_str);

	size_t Length() const;
	const char *Cstr() const;


private:
	char *m_str;

	static char* AllocAndCopyIMP(const char *str_);
};
}	// namespace ilrd
#endif //ifndef __SIMPLE_STR_HPP__		
/*********************************End Of Header******************************/


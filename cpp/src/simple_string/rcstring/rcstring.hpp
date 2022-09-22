#ifndef __RCSTRING__
#define __RCSTRING__

#include<cstddef>
namespace ilrd
{
class String;

bool operator==(const String&, const String&);
bool operator==(const String&, const char*);
bool operator==(const char*, const String&);

bool operator<(const String&, const String&);
bool operator<(const String&, const char*);
bool operator<(const char*, const String&);

bool operator>(const String&, const String&);
bool operator>(const String&, const char*);
bool operator>(const char*, const String&);

class String
{
public:

    String(const char *str=""); // no explicit on purpose.  

    String(const String& other_str);  

    String& operator=(const String& other_str); 

    ~String(); 

    size_t Length() const; 
    const char *Cstr()const;
   

private:
    static char*AllocNcpy(const char *s);
    void Inc();
    void DecNdelete();

    char *m_str; 
};
}

#endif



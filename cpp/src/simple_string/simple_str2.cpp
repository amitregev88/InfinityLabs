#include <cstddef>
#include <iostream> //cout
#include <cassert> 
#include <cstring> //strlen , memcpy

using namespace std;

class String
{
public:

    explicit String(const char *str);  // default Ctor

    String(const String& other_str); //copy constractor func


    String& operator=(const String& other_str); //operator assingment func

    ~String(); //Dtor

    size_t Length() const; // member function
    const char *Cstr()const; // member function
    bool operator==(const String& o_) const; // member function
    bool operator==(const char *str) const; // member function
    bool operator<(const String& o_) const; // member function
    bool operator>(const String& o_) const; // member function
   

private:
    char *m_str;
    static char *AllocNcopyIMP(const char *o_);
};

/************************Ctor*******************************/
String::String(const char *str)
{   
    m_str = AllocNcopyIMP(str);
}
/************************Dtor*******************************/
String::~String()
{
    delete[] m_str;
    m_str = nullptr;    
}
/***************operator assingment func********************/
String& String::operator=(const String& other_str)
{
    //handels assignment with himself
    char *to_delete = m_str;
    m_str = AllocNcopyIMP(other_str.m_str);
    delete [] to_delete;

    return *this;
}
/****************copy constractor func************************/
String::String(const String& other_str) 
{
    m_str = AllocNcopyIMP(other_str.m_str);
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
bool String:: operator==(const String& o_) const
{
    return((strcmp(o_.m_str, m_str) == 0) ? 1 : 0);
}
/******************member function*****************************/
bool String:: operator==(const char *str) const
{
    return((strcmp(str, m_str) == 0) ? 1 : 0);
}
/******************member function*****************************/
bool String:: operator<(const String& o_) const
{
    return((strcmp(m_str, o_.m_str) < 0) ? 1 : 0);
}
/******************member function*****************************/
bool String:: operator>(const String& o_) const
{
    return((strcmp(m_str, o_.m_str) > 0) ? 1 : 0);
}
/******************main function*****************************/
int main()
{
    String s1("hello");

    String s2(s1);
    s1 = s2;

    cout << "length of string:" << s1.Length()<< endl;

    const char *str= s1.Cstr();
    cout << "str is: " << str << endl;

    return 0;
}

char *String:: AllocNcopyIMP(const char *o_)
{
    assert(o_);
    size_t len = strlen(o_) + 1;

    char *str = new char[len];
    memcpy(str, o_, len);

    return str;
}
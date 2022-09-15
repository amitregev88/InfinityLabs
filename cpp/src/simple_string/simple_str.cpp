class String
{
public:

    String(char *);  // default Ctor

    String(const String& other_str); //copy init func

    int Length(char*) const; // member function 

    String operator=(const String& other_str);

    char *Cstr

    

private:
    char *m_str;
};



int main ()
{

    String s1 ("hello")


}
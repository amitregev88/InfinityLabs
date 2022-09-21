#include <iostream>
#include <exception>
#include <cstring>
#include <cstdlib>

using namespace std;

struct BadDog : public runtime_error
{
    BadDog(const string& s_ = "This is a bad dog") : runtime_error(s_){}
};

class X
{
    
    public:
        X();
        ~X();

        friend void Foo();

    private:
        int m_x1;
};

X::X() : m_x1(100)
{
    cout << "ex33 Ctor " << endl;
}

X::~X()
{
    cout << "ex33 Dtor " << endl;
}


void Fifi()
{
    //throw "throw fro Fifi()";
    throw BadDog("bad pup");
    cerr << "Fifi() after throw" << endl;
}

void Foo()
{
    //X m_x1;
    Fifi();
    cerr<< "Foo() after Fifi()" << endl;
}

void Bar()
{
    Foo();
    cerr<< "Bar() after Foo()" << endl;
}


int main()
{
    try
    {
        Bar();
    }
    catch(bad_alloc&)
    {
        cerr << "Out of memory! exiting."; 
        exit(2);
    }
    // catch(BadDog& b)
    // {
    //     cerr << "Bad Dog exception: "<< b.what();
    //     exit(3);
    // }
    catch(exception& r)
    {
        cerr << "Unknown exception: "<< r.what();
        exit(4);
    }
    //catch(...)
    //{
    //    cout << "default catch " << endl;
    //}
    
    return 0;
}









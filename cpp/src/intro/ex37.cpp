#include <iostream>
#include <exception>
#include <cstring>
#include <cstdlib>

using namespace std;



class X
{
    
    public:
        X();
        ~X();
        int Foo(int n) throw (bad_alloc)
        {
            std::cout << " Foo() " << std:: endl;
            //int *d = new int [100000000000000000];
            throw bad_alloc();


        }

        

    private:
        int m_a;
};




X::X() : m_a(100)
{
    std::cout << "ex33 Ctor " << std:: endl;
}

X::~X()
{
    std::cout << Foo(m_a)<< std:: endl;
}

void Bar() throw (bad_cast)
{  
    cerr<< "Bar() " << endl;
    //int g =4;
    //g/=0;
 //   throw bad_cast();
}

void Fifi()
{
    X x1;
    Bar();   
}


int main()
{
    
    try
    {
        Fifi();
    }
    catch(...)
    {
        cout << "bla\n";
    }
    return 0;
}


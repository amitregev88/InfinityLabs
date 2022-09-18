#include <iostream>
#include <dlfcn.h> //dlopen

#include "header.hpp"


using namespace std;

typedef void(*func)();
int main()
{
    char ch = 98;
    unsigned char uch = 115;
    const char *df = "a";

    float f = 10.7;
    int i = 55;
    void *handler = nullptr;

    func func_ptr = nullptr;
        
    handler = dlopen("/home/amit/git/cpp/src/intro/ex12_so/libfoo.so",RTLD_LAZY);
    if(handler == NULL)
    {
        cout<<"dlopen failed\n";
    }

    func_ptr = reinterpret_cast<func> (dlsym(handler, "_Z3Foov"));
    if(func_ptr == NULL)
    {
         cout<<"dlsym= failed\n";
    }
    func_ptr();

   /* Foo();
    
    Foo(i);

    Foo(ch);

    Foo(uch);

    Foo(f);

    Foo(df);*/

    //Foo(nullptr);


    return 0;
}
#include<iostream>
#include "header.hpp"

using namespace std;


void Foo()
{
    cout<<"Hello from Foo - no parameters"<<endl;

}

void Foo(int i)
{
    cout<<"Hello from Foo -  int parameter = "<<i<<endl;
}

void Foo(char c)
{
    cout<<"Hello from Foo -  char parameter = "<<c<<endl;
}

void Foo(unsigned char c)
{

    cout<<"Hello from Foo -  unsigned char = "<<c<<endl;

}

void Foo(float f)
{
    cout<<"Hello from Foo -  float  = "<<f<<endl;

}

void Foo(const char *v)
{
    cout<<"Hello from Foo -  char pointer = "<< *v<<endl;
}

void Foo(void *v)
{
    cout<<"Hello from Foo -  void pointer = "<< v<<endl;
}
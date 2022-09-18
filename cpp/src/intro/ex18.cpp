#include<iostream>

typedef struct 
{
    char num;
}ex18_ty;


int& foo(int param);
int main()
{
    int i = 8;
    int& ip = i;
    ip = 9;
    char f;
    std::cout<< i<<std::endl; 

    ex18_ty stam;

    stam.num = 'b';
    char& ref = stam.num;
    ref = 1000;

    std::cout<< stam.num<<std::endl; 
    std::cout<< ref<<std::endl; 

    std::cout<< "size of ref var "<< sizeof(ref)<<std::endl; 

    std::cout<< "  " << foo(5555) << std::endl;
    return 0;
}

int& foo(int param)
{
    int& i = param;
    std::cout<<"\n hello from foo  "<<param;
    param =8888;
    return i;
}
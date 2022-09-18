#include<iostream>

template<typename T>
void foo(T t)
{
    std::cout << t <<"Generic foo for " << typeid(t).name() << std::endl;
}

void foo(int t)
{
    std::cout<< t << "Specialized foo (for int param)\n";
}

template<typename T1>
T1 add1(T1 t)
{
   return t *1;
}



int main()
{
    foo(4.2);
    foo(5);
    foo<int>(5);

    std::cout<<'\n'<< add1("foo")<<'\n';

    return 0;
}
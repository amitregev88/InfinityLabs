#include<iostream>


class Base
{
    public:
    Base(){std::cout<<"Ctor of Base class"<<std::endl;};
    
    private:
    int x;
    int y;  
};

class Derived : public Base
{
    
    public:
    Derived(){std::cout<<"Ctor of Derived class"<<std::endl;};

    private:
    int z;

};

int main ()
{
    Derived tmp;

    

    

    


    return 0;

}
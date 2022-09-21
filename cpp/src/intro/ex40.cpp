#include <iostream>
#include <typeinfo>
class X
{
    public:
        virtual ~X() {std::cerr << "X dtor" << std:: endl;}
        virtual void Print() const {std::cout << "im X\n";}
    private:
        double m_a;
};

class Y : public X
{
    public:
        void Print() const {std::cout << "im better than X\n";}
    
    private:
        int m_b;
};

void Foo(const X& x){x.Print();}


int main()
{
    //X *xp = new  Y[5];

    //delete[] xp;

    Y y1;
    Foo(y1);

    return 0;
}
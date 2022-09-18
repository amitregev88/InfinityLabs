#include <iostream>



struct X
{
  explicit X(int);
  ~X();

  void Foo(); //member function Inc()
  void Bar() const; //member function Dec()
  
  int m_a;  // member a
  int *m_p;  //member b

};

//constructor 
X::X(int a_) : m_a(a_) , m_p(new int(a_)) 
{


}

//
X::~X()
{
    delete m_p;
    m_p = 0;
}

//constructor _ZN1XC1Eii
void X::Foo()
{
   
   
   ++m_a;
   --(*m_p);
   // m_a = 0;
   // m_p = 0;
   // *m_p = 0;
   // Foo();
}

void Fifi(const X& x_)
{
   //x_.Foo();
   x_.Bar();
}

void X::Bar() const
{
   std::cout << "m_a " << m_a << std::endl;
   std::cout << "*m_p " << *m_p << std::endl;
   std::cout << "m_p " << m_p << std::endl;
   //m_a = 0; // --1--
   //m_p = 0; //--2--
   //*m_p = 0;
   Foo(); 


}




int main()
{
    X x1(1); // default constructor
   
    x1.Foo();
    Fifi(x1);

    return 0;

}
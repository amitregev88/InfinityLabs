#include <iostream>

struct X
{
  X(int a_ , int b_);

  void Inc();
  void Dec();

  int m_a;
  int m_b;


 

};this = djfodjs;  
//constructor - default Ctor
X::X(int a_, int b_) : m_a(a_) , m_b(b_)
{
  

}

//object func
void X::Inc()
{
    ++m_a;
    ++m_b;
 


}

//object func
void X::Dec()
{
    --m_a;
    --m_b;
  
}

//global func
void Inc()
{

}

int main()
{
    X x1(7, -55);
    X x2(x1); /*maybe generic copy func ???*/


    Inc();
    x1.Inc();
    x1.Inc();
    x2.Dec();

    return 0;

}


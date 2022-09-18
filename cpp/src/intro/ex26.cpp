#include <iostream>

struct X
{
   public:
      explicit X(int a_);
      void Foo();
      void Set(int val);
      int Get() const;
  

   private:
        int m_a;  // member



};

//constructor 
X::X(int a_)
   : m_a(a_) 
{
   /* code */
}


//method foo amit.regev
void X::Foo()
{
  printf("%d\n", m_a);
}
// friend foo
void Foo(const X& x_)
{
   printf("%d\n", x_.Get()); //private!
}

void X::Set(int val)
{
    m_a = val;

}


int X::Get() const
{
    return m_a;
}


int main()
{
    X x1; // default constructor doesnt fit - there is no generic Ctor

   
    x1.Foo();
    printf("%d\n", x1.Get());
    Foo(x1);

    return 0;

}
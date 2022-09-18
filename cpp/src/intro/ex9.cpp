#include <iostream>
using namespace std;

void foo(int j, int i = 3, float = 4);

int main()
{
    foo(3);
    foo(6,5);
    foo(4,7, 8.7); 

    
    return 0;
}

void foo (int j , int i, float f)
{

    cout<<"\nj = "<<j<<"\ni = "<<i<<"\nf = "<<f<<endl;
}
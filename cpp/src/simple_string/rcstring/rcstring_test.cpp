#include<iostream>
#include<cassert>

#include "rcstring.hpp"

using namespace ilrd;
using namespace std;

int main()
{
    String c1;
    String c2("Hi");
    String c3(c2);
    String c4("Hello");

    c1 = c4;

    cout << "C1 : " << c1.Cstr() << endl;
    cout << "C2 : " << c2.Cstr() << endl;
    cout << "C3 : " << c3.Cstr() << endl;
    cout << "C4 : " << c4.Cstr() << endl;




    return 0;
}
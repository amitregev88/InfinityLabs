/********************************************************************************
* PROJECT: Factory                                                              *
* FILE: factory_test.cpp                                                        *
* DATE: 10/11/2022                                                              *   
* NAME: Amit Regev                                                              *
* REVIEWER:                                                                     *
* VERSION: 1.00                                                                 *
*********************************************************************************/
#include <iostream>
#include <string>

#include "factory.hpp"

using namespace std;
using namespace ilrd;

string AddFamilyName(string to_add_);


int main()
{
    Factory<string, int, string> tmp;

    tmp.Add(555, AddFamilyName);

    string tmp2  = tmp.Create(555, " r");


    cout << tmp2 << '\n';
    
    
    string tmp3 = tmp.Create(555, " Regev");

    cout << tmp3 << '\n';

    return 0;
}

string AddFamilyName(string to_add_)
{
    string str("Amit");
    str += to_add_;

    return str;
}
/******************************************************************************/
/*    Project:    RCString Test                                                  */
/*    File:        rcstring_test.cpp                                              */
/*    Date:         21/09/2022                                                      */
/*    Name:         Haggai                                                          */
/*    Reviewer:    Sapir                                                          */
/*    Version:     1.00                                                          */
/******************************************************************************/
#include <iostream>
#include <cstring>

#include "rcstring.hpp"

using namespace std;
using namespace ilrd;
/****************************************************************************/
int OperatorsTest(void);

int main()
{
    int status = OperatorsTest();
  
    if (status != 0)
    {
        cout<<"error in : "<<status <<" tests"<<endl;
    }
    else
    {
        cout<<"All tests have passed"<<endl;   
    }

    return 0;
}

int OperatorsTest(void)
{
    int state = 0;
    String str("SAPIR");
    String str2(str);
    String str3("NOT_SAPIR");

    if(false == (str == str2))
    {
        cout << "error in == between char* and String" << endl;
        state += 1;
    }

    if (str == str3)
    {
        cout << "error in == between 2 Strings" << endl;
        state += 1;
    }

    if (false == (str == "SAPIR"))
    {
        cout << "error in == between str and char* " << endl;
        state += 1;
    }

    if (false == ("SAPIR" == str))
    {
        cout << "error in == between str and char* " << endl;
        state += 1;
    }

    if (str == "kalsfm")
    {
        cout << "this should not be printed" << endl;
        state += 1;

    }

    if (str < str3)
    {
        cout << "error in < operator" << endl;
        state += 1;
    }


    return state;
}
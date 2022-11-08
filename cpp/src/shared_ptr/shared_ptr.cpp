/****************************************************************************
*	Project:	shared pointer test 								        *
*	Date: 		5/11/22				    					        		*
*	Name: 		Amit														*
*	Reviewer:	   														    *
*	Version: 	1.00														*
****************************************************************************/
#include <iostream>

#include "shared_ptr.hpp"

using namespace ilrd;
using namespace std;

class Amit
{
public:
    int regev;
    virtual ~Amit() {}
};

class Neta: public Amit
{
public:
    int sweety;
    virtual ~Neta() {}
};

/****************************************************************************/

int SharedPtrTest();

int main()
{
    SharedPtrTest();
    
    return 0;
}
/****************************************************************************/
int SharedPtrTest()
{
    int *tmp = new int;
    int *tmp2 = new int;

   
    *tmp = 123;
    *tmp2 = 456;


    SharedPtr<int> p1(tmp);
    SharedPtr<int> p2(p1);
    SharedPtr<int> p3;
    SharedPtr<int> p4(tmp2);


    p3 = p1;

    if(*p1 == 123)
    {
        cout << "* operator passed\n";
    }
    else
    {
        cout << "* operator failed\n";
    }

    if(p3)
    {
        cout << "operator bool passed\n";
    }

    else
    {
        cout << "operator bool failed\n";
        
    }

    if(p3 == p2)
    {
        cout << "operator == passed\n";
    }
    else
    {
        cout << "operator == failed\n";
    }

    if(p3 == p1)
    {
        cout << "operator == passed\n";
    }
    else
    {
        cout << "operator == failed\n";
    }

    if(p4 != p1)
    {
        cout << "operator !=  passed\n";
    }
    else
    {
        cout << "operator !=  failed\n";
    }


    SharedPtr<Neta> my_neta(new Neta);

    SharedPtr<Amit> me(my_neta);


    me = my_neta;
    
    me->regev = 999;

    if(me->regev == 999)
    {
        cout << "operator -> passed\n";
    }
    else
    {
        cout << "operator -> failed\n";
    }

    return 0;
}



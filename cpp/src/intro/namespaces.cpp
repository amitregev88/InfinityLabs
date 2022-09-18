/****************************************************************************/
/*	Project:																*/
/*	File:		namespaces.cpp													*/
/*	Date: 		11/09/2022													*/
/*	Name: 		Amit Regev												*/
/*	Reviewer:																*/
/*	Version: 	1.00														*/
/****************************************************************************/
#include <iostream>
#include <cassert>

enum {SUCCESS = 0, FAILURE = 1};

namespace useless
{
	unsigned int g_wasteful[400];
	extern int g_notthere;
	void Foo() {std::cout << "useless foo()\n";}

namespace wasteoftyme
{
	void Foo() {std::cout << "wasteoftyme foo()\n";}	
}//namespace wasteoftyme
}//namespace useless

namespace stupid
{
	void Foo() {std::cout << "stupid foo()\n";}
	void Bar() {}
	void DoNothing(unsigned int) {}
}//namespace stupid

namespace useless
{
	void DoNothing(int) {}
}

using namespace useless;

void DoStuff()
{
	stupid::Bar();
	Foo();
	using stupid::Foo;
	Foo();
	DoNothing(g_wasteful[3] + 1);
}

void Foo() {std::cout << "general foo\n";}

using namespace stupid;

namespace comeon = useless::wasteoftyme;

void DoMoreStuff()
{
	comeon::Foo();
	//Foo(); //comment to remove.
	Bar();
	DoNothing(g_wasteful[3] + 1);
}

namespace useless
{
	void DoUselessStuff()
	{
		DoNothing(g_wasteful[3] + 1);
	}
}
/***********************************Main*************************************/

int main()
{
	DoStuff();
	DoMoreStuff();
	DoUselessStuff();
	
	return 0;
}

/*******************************Function Definitions*************************/



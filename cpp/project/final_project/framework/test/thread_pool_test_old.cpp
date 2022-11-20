/******************************************************************************/
/*	Project:	Thread Pool 										    	  */
/*	File:		thread_pool.cpp												  */
/*	Date: 		06/11/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	Binyamin													  */
/*	Version: 	1.1													    	  */
/******************************************************************************/

#include <iostream>
#include <thread> //get_id()
#include "thread_pool.hpp"


using namespace ilrd;
using namespace std;


void Stam()
{
    cout << "hello , thread id: \n"<<std::this_thread::get_id();  
}

int main()
{
   
    ThreadPool tmp(5, 0);    
    tmp.AddTask(Stam);
    tmp.Run();
    tmp.Pause();
    tmp.Run();

    return 0;
}
/******************************************************************************/
/*	Project:	Thread Pool 										    	  */
/*	File:		thread_pool.cpp												  */
/*	Date: 		06/11/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	Binyamin													  */
/*	Version: 	1.1														      */
/******************************************************************************/

#include <iostream>
#include <cassert>
#include <thread>
#include "thread_pool.hpp"

using namespace std;
using namespace ilrd;

int CreatePosixThread(size_t numOfThreads_, int nice_)
{


}

int ThreadPool:: CreateStdThread(size_t numOfThreads_)
{
    for (size_t i = 0; i < numOfThreads_; ++i)
    {
        m_threads.push_back(thread(bla)); 
    }
}
 
ThreadPool::ThreadPool(size_t numOfThreads_, int nice_)
{
    assert(numOfThreads_);

    CreateStdThread(numOfThreads_);

}


ThreadPool::~ThreadPool() noexcept
{

    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i].join();
    }
};


//void ThreadJob 

// void SetNumOfThreads(size_t numOfThreads_)
//{
//    thread t(fn)

//}

void ThreadPool:: AddTask(function<void()> const& action, int priority = MEDIUM)
{
   Task task(action,priority);  
   m_waitQue.Push(task);
} 


/*----------------------------------------------*/

Task::Task(std::function<void()> const& action, int priority) : m_func(action), prior(priority)
{
}

Task::Task(const Task &o_) : m_func(o_.m_func)
{
}

Task &Task::operator=(const Task &o_)
{
    this->m_func = o_.m_func;

    return *this;
} 

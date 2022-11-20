/******************************************************************************/
/*	Project:	Thread Pool 										    	  */
/*	File:		thread_pool.cpp												  */
/*	Date: 		06/11/2022													  */
/*	Name: 		Amit Regev     												  */
/*	Reviewer:	        													  */
/*	Version: 															      */
/******************************************************************************/

#include <iostream>
#include <cassert>
#include <thread>
#include "thread_pool.hpp"

using namespace std;
using namespace ilrd;

void Dummy();

//int CreatePosixThread(size_t numOfThreads_, int nice_)

void ThreadPool:: CreateStdThread(size_t numOfThreads_)
{
    for (size_t i = 0; i < numOfThreads_; ++i)
    {
        m_threads.push_back(thread(&ThreadPool:: ThreadJob , this)); 
    }
}
 
ThreadPool::ThreadPool(size_t numOfThreads_, int nice_)
{
    assert(numOfThreads_);

    /*TODO try and catch*/

    CreateStdThread(numOfThreads_);
}

void ThreadPool:: ThreadJob()
{
    while( !m_should_stop) 
    {      
        while (!m_should_pause)
        {
            Task _task;
            m_waitQue.Pop(_task);
            _task();       
        }
        
    }
}

ThreadPool::~ThreadPool() noexcept
{
    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i].join();
    }
};

 //void SetNumOfThreads(size_t numOfThreads_)
//{
 // thread t(fn)

void ThreadPool:: AddTask(function<void()> const& action, int priority)
{
   Task task(action,priority);  
   m_waitQue.Push(task);
} 

void ThreadPool:: Run()
{
    m_should_stop = false;
    m_should_pause = false;
}

void ThreadPool:: Stop()
{
    m_should_pause = false;
    m_should_stop = true;

    AddTask(Dummy,HIGH + 1);

    m_cv.notify_all();

    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        m_threads[i].join();
    }
}

void ThreadPool:: Pause()
{
    m_should_pause = true;
    m_should_stop = false;


}

/*----------------------------------------------*/

Task::Task(std::function<void()> const& action, int priority) : m_func(action), m_priority(priority)
{}


Task::Task(const Task &o_) : m_func(o_.m_func)
{}

Task::~Task()noexcept
{}

Task &Task::operator=(const Task &o_)
{
    this->m_func = o_.m_func;
    return *this;
} 

bool Task::operator<(const Task &o_) const
{
    return m_priority < o_.m_priority;
} 

void Task::operator()()
{
    m_func();
}

void Dummy()
{
    cout << "I'm dummy task\n";
}
/*/*timespec time_out ={time(NULL) + }*/
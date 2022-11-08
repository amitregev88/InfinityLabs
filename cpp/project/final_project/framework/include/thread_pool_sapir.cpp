/******************************************************************************/
/*	Project:	Thread pool API										    	  */
/*	File:		thread_pool.cpp												  */
/*	Date: 		06/11/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	Binyamin													  */
/*	Version: 	1.00														  */
/******************************************************************************/
#include <thread>   //thread

#include "thread_pool.hpp"
#include "waitable_queue.hpp"

using namespace std;

namespace ilrd
{

Task::Task(std::function<void()> action_):m_func(action_)
{}

Task& Task::operator=(const Task &o_)
{
    this->m_func = o_.m_func;

    return *this;
}

Task::Task(const Task &o_):m_func(o_.m_func)
{}

void Task::operator()()
{
    m_func();
}


ThreadPool::ThreadPool(std::size_t numOfThreads_ , int nice_)
{
    // create threads
    for(std::size_t i = 0; i < numOfThreads_; ++i)
    {
        Task task; 
        std::thread tr(std::ref(task)); 
        sched_param sch;
        int policy;
        
        pthread_getschedparam(tr.native_handle(), &policy, &sch);
        sch.sched_priority = nice_;
        
        pthread_setschedparam(tr.native_handle(), SCHED_FIFO, &sch); 
                                                           
        m_threads.push_back(tr);
        m_threads.at(i).join();

    }

 
    
}

void ThreadPool::AddTask(std::function<void()> action_,int priority_)
{

}
}//namespace ilrd


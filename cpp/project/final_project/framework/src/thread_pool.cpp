/******************************************************************************/
/*	Project:	Thread Pool 										    	  */
/*	File:		thread_pool.cpp												  */
/*	Date: 		06/11/2022													  */
/*	Name: 		Amit Regev     												  */
/*	Reviewer:	        													  */
/*	Version: 															      */
/******************************************************************************/

//gd+ ./test/thread_pool_test2.cpp ./src/thread_pool2.cpp -I ./include/ -lpthread -lboost_thread -lboost_chrono

#include <iostream> //cout
#include <cassert> //assert
#include <boost/thread.hpp> //boost thread

#include "thread_pool2.hpp"
#include "waitable_queue.hpp"

using namespace std;
using namespace ilrd;

static void Dummy();

/*-----------------------------Thread Pool-----------------------------*/
//int CreatePosixThread(size_t numOfThreads_, int nice_)

void ThreadPool:: CreateThreads(size_t numOfThreads_, int priority_)
{
    for (size_t i = 0; i < numOfThreads_; ++i)
    {
        
        m_threads_should_remove.push_back(false);
        
        m_threads.push_back(boost::thread(ThreadJob , this, m_threads.size() )); 
    
        int ret = pthread_setschedprio(m_threads[i].native_handle(), priority_);

        if (ret != 0)
        {
            throw(std::runtime_error("set scheduler priority failed\n"));
        }
    }
}
/**********************************************************************************/
 
ThreadPool::ThreadPool(size_t numOfThreads_, int nice_)
{
    assert(numOfThreads_);

    m_should_stop = false;
    m_should_pause = true;

    try 
    {
        CreateThreads(numOfThreads_, nice_);
    }
    
    catch (...)
    {
        cout << "got exception!\n";
    }
}
/***************************************************************************/
void ThreadPool:: ThreadJob(ThreadPool *this_ , size_t thread_i_stop_) //static
{
    
    Task task;

    while (!this_->m_should_stop)
    {
        
        {
            unique_lock<mutex> lock(this_->m_run_task_guard);
            this_->m_cv.wait(lock, [this_]{ return !this_->m_should_pause; });
        }

        if (this_->m_threads_should_remove[thread_i_stop_] || (this_->m_should_stop))
        {
            cout << "poped\n";
            return;
        }

        this_->m_waitQue.Pop(task);
        task();
    }
       
    cout << "stoped\n";
    
    /*
    while( !m_should_stop) 
    {      
        while (!m_should_pause)
        {
            Task _task;
            m_waitQue.Pop(_task);
            _task();       
        }
        
    }
    */
}

ThreadPool::~ThreadPool() noexcept
{
    for_each(m_threads.begin(), m_threads.end(),[this](boost::thread &m_threads) { if(m_threads.joinable()) m_threads.detach(); });
};

size_t ThreadPool::HowMuchThreadsAvailibale() const
{
    size_t ret = 0;

    for_each(m_threads_should_remove.begin(), m_threads_should_remove.end(), [&ret](bool is_stopped_) { if(!is_stopped_) ++ret; });

    return ret;
}

void ThreadPool::SetNumOfThreadsToRemove(size_t num_of_th_)
{
    fill(m_threads_should_remove.begin(), m_threads_should_remove.begin() + num_of_th_, true);
}

void ThreadPool::SetNumOfThreads(std::size_t numOfThreads_)
{
    size_t curr_threads = HowMuchThreadsAvailibale();

    if (numOfThreads_ > curr_threads)
    {
        sched_param thread_priority = {0};
        int policy;
        int ret = pthread_getschedparam(m_threads[0].native_handle(), &policy, &thread_priority);

        if (0 != ret)
        {
            throw(runtime_error("get scheduler priority failed\n"));
        }

        CreateThreads(numOfThreads_ - curr_threads, thread_priority.sched_priority);
    }

    else if ( numOfThreads_ < m_threads.size() )
         {
             SetNumOfThreadsToRemove(m_threads.size() - numOfThreads_);
         }
}

void ThreadPool:: AddTask(function<void()> const& action_, int priority_)
{
   Task task(action_,priority_);  
   m_waitQue.Push(task);
} 

void ThreadPool:: Run()
{
    m_should_stop = false;
    m_should_pause = false;
    m_cv.notify_all();
}

bool ThreadPool:: Stop(boost::chrono::milliseconds timeout_)
{
    m_should_pause = false;
    m_should_stop = true;

/*     AddTask(Dummy,HIGH + 1);
 */

    AddDummyTasks();
    m_cv.notify_all();

    bool ret = true;

    for (size_t i = 0; i < m_threads.size(); ++i)
    {
        if(m_threads[i].try_join_for(timeout_))
        {
            ret = false; 
        }
    }

    return ret;
}

void ThreadPool:: Pause()
{
    m_should_pause = true;
    m_should_stop = false;

    /* AddTask(Dummy,HIGH + 1); */
    AddDummyTasks();
}

static void Dummy()
{
    cout << "I'm dummy task\n";
}

void ThreadPool:: AddDummyTasks()
{
    size_t curr_threads = HowMuchThreadsAvailibale();

    for (size_t i = 0; i < curr_threads; ++i)
    {
        AddTask( Dummy, numeric_limits<int>::max() );
    }
}

/*-----------------------Task Obj----------------------*/

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

void Task::operator()() const
{
    m_func();
}
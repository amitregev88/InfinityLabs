/******************************************************************************/
/*	Project:	Thread pool API										    	  */
/*	File:		thread_pool.hpp												  */
/*	Date: 		06/11/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	Binyamin													  */
/*	Version: 	1.1														  */
/******************************************************************************/

#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <mutex>    //mutex
#include <queue>    //queue
#include <thread>   //thread
#include <condition_variable>      //condition_variable
#include <functional>      


#include "waitable_queue.hpp"

enum PRIORITY {LOW, MEDIUM, HIGH};

namespace ilrd
{

class Task; 
class ThreadPool

{

public:

    explicit ThreadPool(std::size_t numOfThreads_ , int nice_);
    ThreadPool& operator = (const ThreadPool& o_)= delete;
    ThreadPool(const ThreadPool& o_)= delete;
    ~ThreadPool()noexcept;

    
    void AddTask(std::function<void()> const& action, int priority = MEDIUM); 
    void Run(); 
    void Pause();
    void Stop();
    void SetNumOfThreads(std::size_t numOfThreads_);

private:

    int CreateStdThread(size_t numOfThreads_);
    std::vector<std::thread> m_threads;
    WaitQueue<std::priority_queue/*<std::shared_ptr*/<Task> >/*>*/  m_waitQue; 
    
};


class Task
{
public:
    explicit Task(std::function<void()> const& action_ = nullptr, int priority);
    ~Task()noexcept= default;
    Task(const Task &o_);
    Task& operator=(const Task &o_);
    void operator()();

private:
    std::function<void()> m_func;
    int prior;
};



} // namespace ilrd

#endif //	ifndef __THREAD_POOL_HPP__									
/**********************************End Of Header*******************************/
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



namespace ilrd
{

template<typename T>
class PQUEWRAPPER : private std :: priority_queue <T>
{

public:
    const T& front()
    {
        return std:: priority_queue<T>::top();
    }

    using std::priority_queue<T>::pop;
    using std::priority_queue<T>::push;
    using std::priority_queue<T>::reference;
    using std::priority_queue<T>::value_type;
    using std::priority_queue<T>::empty;
    using std::priority_queue<T>::size;
    using std::priority_queue<T>::emplace;
    using std::priority_queue<T>::swap;
};

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
    void ThreadJob();
    void CreateStdThread(size_t numOfThreads_);
    std::vector<std::thread> m_threads;
    std:: size_t m_should_stop;
    std:: size_t m_should_pause;
    WaitableQueue<PQUEWRAPPER<Task> >  m_waitQue; 
    std::condition_variable m_cv;
    enum PRIORITY {LOW, MEDIUM, HIGH};
        
};



class Task
{
public:
    Task() : m_func(), m_priority(){}
    explicit Task(std::function<void()> const& action_, int priority);
    ~Task()noexcept;
    Task(const Task &o_);
    Task& operator=(const Task &o_);
    void operator()();
    bool operator<(const Task &o_) const;
    

private:
    std::function<void()> m_func;
    int m_priority;
};



} // namespace ilrd

#endif //	ifndef __THREAD_POOL_HPP__									
/**********************************End Of Header*******************************/
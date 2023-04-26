/******************************************************************************/
/*	Project:	Thread pool API										    	  */
/*	File:		thread_pool.hpp												  */
/*	Date: 		06/11/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	Binyamin													  */
/*	Version: 	1.1												    		  */
/******************************************************************************/

#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <mutex>    //mutex
#include <queue>    //queue
#include <thread>   //thread
#include <condition_variable>      //condition_variable
#include <functional>      //function

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "waitable_queue.hpp"



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

    explicit ThreadPool(std::size_t numOfThreads_ , int nice_ = 0);
    ThreadPool& operator = (const ThreadPool& o_)= delete;
    ThreadPool(const ThreadPool& o_)= delete;
    ~ThreadPool()noexcept;
    
    void AddTask(std::function<void()> const& action, int priority = 0); 
    void Run(); 
    void Pause();
    bool Stop(boost::chrono::milliseconds ms);
    void SetNumOfThreads(std::size_t numOfThreads_);

private:

    static void ThreadJob(ThreadPool *this_ , std::size_t thread_i_stop_);
    void CreateThreads(size_t numOfThreads_, int priority_);
    std:: size_t HowMuchThreadsAvailibale() const;
    void SetNumOfThreadsToRemove(size_t num_of_th_);
    void AddDummyTasks();


    std::vector<boost::thread> m_threads;
    std::vector<bool> m_threads_should_remove;
    std::mutex m_run_task_guard;
    bool m_should_stop;
    bool m_should_pause;
    WaitableQueue<PQUEWRAPPER<Task> >  m_waitQue; 
    std::condition_variable m_cv;   
         
};



class Task
{
public:
    explicit Task(std::function<void()> const& action_=nullptr, int priority =  0);
    ~Task()noexcept;
    Task(const Task &o_);
    Task& operator=(const Task &o_);
    
    void operator()() const;
    bool operator<(const Task &o_) const;
        

private:
    std::function<void()> m_func;
    int m_priority;
};



#endif //	ifndef __THREAD_POOL_HPP__									
/**********************************End Of Header*******************************/
/****************************************************************************/
/*	Project:	Thread Pool API												*/
/*	File:		bitarray.hpp												*/
/*	Date: 		06/11/2022													*/
/*	Name: 		ILRD25      												*/
/*	Reviewer:	Binyamin													*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __THREAD_POOL_HPP__
#define __THREAD_POOL_HPP__

#include <iostream>
#include <queue>
#include <thread> 

namespace ilrd
{


    class ThreadPool
    {
    public:
    
    ThreadPool(void *);
    void AddTask();
    void Start();
    void QueueTask(const std::function<void()>& task);
    void Stop();
    void Unavailable();


    private:
    

    Mutex& guard;

    bool should_terminate = false;           // Tells threads to stop looking for jobs
    //std::condition_variable mutex_condition; // Allows threads to wait on new jobs or termination 
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> tasks;
    std:: size_t max_threads;

    TreadPool& ThreadPool(ThreadPool&); //cctor is disable. do not imp
    TreadPool& operator=(ThreadPool&); //operator=  is disable. do not imp 
    };




    class Mutex
    {
    public:
        Mutex();
        void lock();
        void unlock();
        Mutex get();Mutex
        bool isLocked();
    private:
        std::mutex queue_mutex;                  // Prevents data races to the job queue

    };

    class ConditonVariable
    {
        ConditonVariable();
        void wait(Mutex mutex);
        void signal();
        void broadcast();
    }
} // namespace ilrd

#endif //	ifndef __BITARRAY_HPP__

/*********************************End Of Header******************************/
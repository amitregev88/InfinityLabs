/****************************************************************************/
/*	Project:	WAITABLE QUEUE API  										*/
/*	File:		bitarray.hpp												*/
/*	Date: 		06/11/2022													*/
/*	Name: 		ILRD25      												*/
/*	Reviewer:	Binyamin													*/
/*	Version: 	1.00														*/
/****************************************************************************/

#ifndef __WAITABLE_QUEUE_HPP__
#define __WAITABLE_QUEUE_HPP__

#include <iostream>
#include <queue>
#include <thread> 
#include <mutex>
#include <condition_variable> 

namespace ilrd
{

    template<class Queue>
    class WaitQueue
    {
    public:

        ~WaitQueue() = default;
        explicit WaitQueue() = default;
        WaitQueue(WaitQueue&) = delete; 
        WaitQueue& operator=(WaitQueue&) = delete; 

        void Push(const typename Queue::value_type& Data);
        void Pop(typename Queue::value_type& _out);
        bool Pop(typename Queue::value_type& _out, std::chrono::milliseconds); //pop timeout
        
    private:
        std::mutex m_guard;
        std::condition_variable m_cv;
        Queue m_queue;
     
    };

/***************************************************************************************/


template<class Queue>
void WaitQueue<Queue>:: Push(const typename Queue::value_type& data)
{
    std::unique_lock<std::mutex>lock(m_guard);
    m_queue.push(data);
    m_cv.notify_one();                                                                                                                                                                                                                                                                                                                                                                      
}


template<class Queue>
void WaitQueue<Queue>:: Pop(typename Queue::value_type& _out)
{   
    std::unique_lock<std::mutex>lock(m_guard);
    while(m_queue.empty())
    {
        m_cv.wait(lock);
    }
    _out = m_queue.front(); 
    m_queue.pop();   
}

/* template<class Queue>
bool WaitQueue<Queue>:: Pop(typename Queue::value_type& _out, std::chrono::milliseconds)
{
    std::unique_lock<std::mutex>lock(m_guard);
    while(m_queue.empty())
    {
        m_cv.wait_for();
    }
    _out = m_queue.front(); 
    m_queue.pop();   



} */

} // namespace ilrd

#endif //	ifndef __WAITABLE_QUEUE_HPP__

/*********************************End Of Header******************************/



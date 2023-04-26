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

#include <queue>
#include <thread> 
#include <mutex>
#include <condition_variable> 
#include <chrono>

    template<class Queue>
    class WaitableQueue
    {
    public:

        ~WaitableQueue() = default;
        explicit WaitableQueue() = default;
        WaitableQueue(WaitableQueue&) = delete; 
        WaitableQueue& operator=(WaitableQueue&) = delete; 

        void Push(const typename Queue::reference data);
        void Pop(typename Queue::reference _out);
        bool Pop(typename Queue::reference _out, std::chrono::milliseconds); //pop timeout
        
    private:
        using locking =  std::unique_lock<std::mutex>;
        std::mutex m_guard;
        std::condition_variable m_que_no_empty;
        Queue m_queue;
     
    };

    template<typename T, typename Container = std::vector<T>, typename Compare = std::less<typename Container::value_type> >
    class PQueWrap: private std::priority_queue<T, Container, Compare>
    {
    public:
        typedef void    difference_type;
        typedef T       value_type;
        typedef T*      pointer;
        typedef T&      reference;
    
        explicit PQueWrap() = default;
        ~PQueWrap() noexcept = default;

        const T& front() { return this->top(); }

        using std::priority_queue<T>::pop;
        using std::priority_queue<T>::push;
        using std::priority_queue<T>::empty;
    };


/***************************************************************************************/

template<class Queue>
void WaitableQueue<Queue>::Push(const typename Queue::reference data)
{
    {
        std::unique_lock<std::mutex> lock(m_guard);
        m_queue.push(data);
    }

    m_que_no_empty.notify_one();
                                                                                                                                                                                                                                                                                                                                                                  
}

template<class Queue>
void WaitableQueue<Queue>:: Pop(typename Queue::reference _out)
{
    std::unique_lock<std::mutex> lock(m_guard);

    m_que_no_empty.wait(lock, [this]{ return !m_queue.empty(); });

    _out = m_queue.front();
    m_queue.pop();
}

template<class Queue>
bool WaitableQueue<Queue>:: Pop(typename Queue::reference _out, std::chrono::milliseconds ms_)
{
    std::unique_lock<std::mutex> lock(m_guard);

    bool res = m_que_no_empty.wait_for(lock, ms_, [this]{ return !m_queue.empty(); });

    if (!res)
    {
        return false;
    }

    _out = m_queue.front();
    m_queue.pop();

    return true;
} 



#endif //	ifndef __WAITABLE_QUEUE_HPP__
/*********************************End Of Header******************************/



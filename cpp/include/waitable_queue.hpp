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
#include <mutex>
#include <condition_variable> 


namespace ilrd
{

    template<class Queue>
    class WaitQueue
    {
    public:

    
        ~WaitQueue();
        explicit WaitQueue();
        WaitQueue(WaitQueue&) = delete; 
        WaitQueue&operator=(WaitQueue&) = delete; 

        void Push(const Data&);
        void Pop(Data& _out);
        bool Pop(Data& _out, std::chrono::milliseconds); //pop timeout
        
    private:
        std::mutex m_guard;
        std::condition_variable m_cv;
        Queue m_queue;
     
    };


} // namespace ilrd

#endif //	ifndef __BITARRAY_HPP__

/*********************************End Of Header******************************/
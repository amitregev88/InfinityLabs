/*******************************************************************************
* PROJECT: Thread Pool
* FILE: thread_pool_test.cpp
* DATE: 08/11/2022
* NAME: Amit Regev
* REVIEWER: 
* VERSION: 1.00
*******************************************************************************/
#include <iostream>
#include <thread>
#include <chrono>

#include <boost/thread.hpp>
#include <boost/chrono.hpp>

#include "thread_pool2.hpp"

using namespace std;
/******************************************************************************/
static void MediumPriorityTask()
{
    cout << "this is medium praiority task\n";
    this_thread::sleep_for(chrono::seconds(3));
}

static void HighPriortyTask()
{
    cout << "this is high praiority task\n";
    this_thread::sleep_for(chrono::seconds(3));
}
/******************************************************************************/
int main()
{
    using namespace ilrd;

    ThreadPool tp(4, 0);

    tp.SetNumOfThreads(2);

    tp.AddTask(MediumPriorityTask, 1);
    tp.AddTask(MediumPriorityTask, 1);
    tp.AddTask(MediumPriorityTask, 1);
    tp.AddTask(HighPriortyTask, 2);

    tp.Run();
    this_thread::sleep_for(std::chrono::milliseconds(30));

    tp.Pause();
    tp.AddTask(HighPriortyTask, 2);
    tp.AddTask(HighPriortyTask, 2);
    this_thread::sleep_for(std::chrono::milliseconds(3000));

    tp.Run();
    this_thread::sleep_for(std::chrono::milliseconds(30));

    tp.Stop( boost::chrono::milliseconds(3000) );

    return 0;
}

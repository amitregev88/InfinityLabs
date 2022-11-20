/****************************************************************************/
/*	Project:			    												*/
/*	File:		dispatcher.hpp												*/
/*	Date: 		16/11/2022													*/
/*	Name: 		HRD25       												*/
/*	Reviewer:																*/
/*	Version: 	1.00														*/
/****************************************************************************/
#ifndef __DISPATCHER_HPP__
#define __DISPATCHER_HPP__

#include <functional>   //  std::function
#include <vector>       //  std::vector
#include <algorithm>    //  std::for_each

namespace ilrd
{
template <typename EVENT>
class Dispatcher;

template <typename EVENT>
class Callback
{
public:
    explicit Callback(std::function<void(EVENT)> cb_, std::function<void()> 
                                                    df_, Dispatcher<EVENT>&);
    ~Callback() noexcept;

    Callback(const Callback&) = delete;
    Callback& operator=(const Callback&) = delete;

    void OnEvent(EVENT event_);
    void OnDeath();

private:
    std::function<void(EVENT)> m_onEvent;
    std::function<void()> m_onDeath;
    Dispatcher<EVENT> &m_dispatcher;
};

/****************************************************************************/
template <typename EVENT>
class Dispatcher
{
public:
    explicit Dispatcher() = default;
    ~Dispatcher() noexcept;

    void Subscribe(const Callback*);
    void Unsubscribe(const Callback*);
    void Notify(EVENT);

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

private:
    std::vector<Callback<EVENT>*> m_callbacks;    
};

/***********************Class Dispatcher Functions***************************/


/***********************Class Callback Functions*****************************/
template <typename EVENT>
Callback<EVENT>::Callback(std::function<void(EVENT)> cb_, 
 std::function<void()> df_, Dispatcher<EVENT> &dispatcher_):
 m_onEvent(cb_), m_onDeath(df_), m_dispatcher(dispatcher_)
{}

template <typename EVENT>
Callback<EVENT>::~Callback() noexcept
{
    m_dispatcher.Unsubscribe(this);
}

template <typename EVENT>
void Callback<EVENT>::OnEvent(EVENT event_)
{
    m_onEvent(event_);
}

template <typename EVENT>
void Callback<EVENT>::OnDeath()
{
    m_onDeath();
}
} // namespace ilrd

#endif //	ifndef __DISPATCHER_HPP__									
/*********************************End Of Header******************************/
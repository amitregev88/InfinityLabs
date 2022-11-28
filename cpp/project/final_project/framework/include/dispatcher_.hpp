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
    void SetSubscription();
    void RemoveSubscription();

private:
    std::function<void(EVENT)> m_onEvent;   
    std::function<void()> m_onDeath;
    Dispatcher<EVENT> &m_dispatcher;

    bool m_HasSubscrition;
};

/****************************************************************************/
template <typename EVENT>
class Dispatcher
{
public:
    explicit Dispatcher() = default;
    ~Dispatcher() noexcept;

    void Subscribe(const Callback<EVENT>*);
    void Unsubscribe(const Callback<EVENT>*);
    void Notify(EVENT);

    Dispatcher(const Dispatcher&) = delete;
    Dispatcher& operator=(const Dispatcher&) = delete;

private:
    std::vector<Callback<EVENT>*> m_callbacks;    
};

/***********************Class Dispatcher Functions***************************/

template <typename EVENT>
Dispatcher<EVENT>::~Dispatcher() noexcept
{
    std:: for_each(m_callbacks.begin(), m_callbacks.end(), [](Callback<EVENT> * cb_) {cb_->RemoveSubscription(); cb_->OnDeath();});
}

template <typename EVENT>
void Dispatcher<EVENT>:: Subscribe(const Callback<EVENT> *cb_)
{      
    cb_->SetSubscription();
    m_callbacks.push_back(cb_);
}

template <typename EVENT>
void Dispatcher<EVENT>::Unsubscribe(const Callback<EVENT> *cb_)
{
    m_callbacks.erase(std::find(m_callbacks.begin(), m_callbacks.end(), cb_));
}

template <typename EVENT>
void Dispatcher<EVENT>::Notify(EVENT event_)
{
    std::for_each(m_callbacks.begin(), m_callbacks.end(), [event_](Callback<EVENT> *cb_) { cb_->OnEvent(event_);});
}


/***********************Class Callback Functions*****************************/
template <typename EVENT>
void Callback<EVENT>::SetSubscription()
{
    m_HasSubscrition = true;
}

template <typename EVENT>
void Callback<EVENT>::RemoveSubscription()
{
    m_HasSubscrition = false;
}

template <typename EVENT>
Callback<EVENT>::Callback(std::function<void(EVENT)> cb_, 
 std::function<void()> df_, Dispatcher<EVENT> &dispatcher_):
 m_onEvent(cb_), m_onDeath(df_), m_dispatcher(dispatcher_)
{}

template <typename EVENT>
Callback<EVENT>::~Callback() noexcept
{
    if (m_HasSubscrition)
    {
        m_dispatcher.Unsubscribe(this);
        RemoveSubscription();
    }
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
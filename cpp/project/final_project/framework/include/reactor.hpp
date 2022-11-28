/******************************************************************************/
/*	Project:	REACTOR API    										    	  */
/*	File:		reactor.hpp		    										  */
/*	Date: 		13/11/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	Binyamin													  */
/*	Version: 	1.00														  */
/******************************************************************************/

#ifndef __REACTOR_HPP__
#define __REACTOR_HPP__

#include <utility>  //pair
#include <map> //map
#include <functional> // std::function
#include <vector>  //vector
#include <atomic>

namespace ilrd
{
enum fdMode{READ,WRITE, EXE};
using FdNMode = std::pair<int, fdMode>;
using ACTION = std::function<void()>;

class Selector;

class Selector
{
public:
    explicit Selector() = default;
    ~Selector() = default;
    Selector &operator=(const Selector& o_) = delete;
    Selector(const Selector& o_) = delete;
    int Listen(std::vector<FdNMode> &fdsAndModes_);

private:
    void SplitVector(std::vector<FdNMode> &fdsAndModes_ ,std::vector<int> &fds_,
                                                      std::vector<int> &modes_);
};

template<typename Selector>
class Reactor
{
public:
    explicit Reactor();
    ~Reactor() = default;
    Reactor(const Reactor& o_) = delete;
    Reactor& operator=(const Reactor& o_) = delete;

    void Remove(int fd_, fdMode mode_);
    void Add(ACTION action_, int fd_, fdMode mode_ );
    void Stop();
    void Run();
    
private:

    std::map<FdNMode,ACTION > m_fdVNmodeToFunc;
    Selector m_selector;
    std::atomic<bool> m_shouldStop;
};
/************************************************/
template<typename Selector>
Reactor<Selector>::Reactor(): m_shouldStop(true)
{}
/*************************************************/
template<typename Selector>
void Reactor<Selector>::Add(std::function<void()> func_, int fd_, MODES mode_)
{
    m_fdVNmodeToFunc.insert(std::make_pair(std::make_pair(fd_, mode_), action_)); 
}
/*****************************************************/
template<typename Selector>
void Reactor<Selector>::Remove(int fd_, fdMode mode_)
{
    m_fdVNmodeToFunc.erase(m_fdVNmodeToFunc.find(std::make_pair(fd_, mode_)));
}
/******************************************************/
template<typename Selector>
void Reactor<Selector>::Stop()
{
    m_shouldStop.store(true);
}
/*****************************************************/
template<typename Selector>
void Reactor<Selector>::Run()
{
    if (true == m_shouldStop)
    {
        return;
    }

    

}



}//ilrd

#endif //	ifndef __REACTORHPP__									
/**********************************End Of Header*******************************/


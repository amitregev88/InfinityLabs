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
#include <sys/select.h>


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
/***************************************/
void Selector::SplitVector(std::vector<FdNMode> &fdsAndModes_ ,
                               std::vector<int> &fds_, std::vector<int> &modes_)
{
    for (auto fdmode_ : fdsAndModes_)
    {
        fds_.push_back(fdmode_.first);
        modes_.push_back(fdmode_.second);
    }
}

/*****************************************************/
int Selector::Listen(std::vector<FdNMode> &fdsAndModes_)
{
    std::vector<int> fds;
    std::vector<int> modes;
    fd_set read;
    fd_set write;
    fd_set execute;




    Setfd()






}


static void Setfd(fd_set &fds_)
{
    FD_ZERO(&fds_);
    FD_SET(0, &fds_);
}




template<typename Selector>
void Reactor<Selector>::Run()
{
    std::vector<FdNMode> fds_listen;
    

    std::transform(m_fdVNmodeToFunc.begin(),m_fdVNmodeToFunc.end(),
    std::inserter(fds_listen.begin(),fds_listen.end()),[](const auto iter) 
    { return iter.first;});
   
    
    if (true == m_shouldStop)
    {
        return;
    }

    m_shouldStop(0);

    while(!m_shouldStop)
    {

        std::vector<FdNMode>runner(m_selector.Listen(fdsListen));
    
      
      
      select -->fd ready
      serach fd in map 

      handler exec 






    } 


    

    


}



}//ilrd

#endif //	ifndef __REACTORHPP__									
/**********************************End Of Header*******************************/


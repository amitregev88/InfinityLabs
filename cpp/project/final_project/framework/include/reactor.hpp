/******************************************************************************/
/*	Project:	REACTOR API    										    	  */
/*	File:		reactor.hpp		    										  */
/*	Date: 		13/11/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	Binyamin													  */
/*	Version: 	1.00														  */
/******************************************************************************/

#ifndef __REACTOR_HPP__
#define __REACTORHPP__

#include <pair>   //pair
#include <functional> // std::function

namespace ilrd
{

class Selector;
enum fdMode{READ,WRITE, EXE};

class Reactor
{
public:
    exlpicit Reactor(Selector selector_);
    ~Reactor() = default;
    Reactor(const Reactor& o_) = delete;
    Reactor& operator=(const Reactor& o_) = delete;

    void Remove(int fd_, enum mode_);
    void Add(std::function<void()> function_, int fd_, fdMode);
    void Stop();
    void Run();
    
private:

    std::pair<int, fdMode> m_fdVNmode;
    Selector m_selector;
    
    bool m_shouldStop;
};

class Selector
{
public:
    exlpicit Selector() = default;
    ~Selector() = default;
    Selector &operator=(const Selector& o_) = delete;
    Selector(const Selector& o_) = delete;

    std::pair<int> Select(std::pair<int,fdMode> );
};


}//ilrd

#endif //	ifndef __REACTORHPP__									
/**********************************End Of Header*******************************/


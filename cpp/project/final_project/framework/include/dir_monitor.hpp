/****************************************************************************
*	Project:	DirMon								    	                *
*	File:		dirmon.hpp                    	    				       	*
*	Date: 		2022-11-20									        		*
*	Name: 		HRD25														*
*	Reviewer:	   	    													*
*	Version: 	1.00														*
****************************************************************************/
#ifndef _ILRD_DIRMON_
#define _ILRD_DIRMON_

#include <iostream>
#include <memory>
#include <map>

#include "dispatcher.hpp"
/****************************************************************************/
namespace ilrd
{

class DirMonitor
{   //  Blocked copy & assignment
public:
    using PluginDispatcher = ilrd::Dispatcher<std::string>; 

public:
    explicit DirMonitor(const std::string &dirPath_);
    ~DirMonitor() noexcept = default;
    
    DirMonitor(const DirMonitor&) = delete;
    DirMonitor& operator=(const DirMonitor&) = delete;

    void Subscribe(Callback<std::string,DirMonitor>*);
    void Unsubscribe(Callback<std::string,DirMonitor>*);

private:
    std::string m_dir;
    PluginDispatcher m_dispatcher;
};
/****************************************************************************/

class DlLoader
{
public:

    class SharedObject
    {
    public:
        SharedObject();
        ~SharedObject();

        template<typename T>
        T GetSymbol(std::string symbol_);
        // also legit :T *GetSymbol(std::string symbol_);

    private:

    };

public:
    using SoPtr = std::shared_ptr<SharedObject>; 

    explicit DlLoader();
    ~DlLoader() noexcept;

    DlLoader(const DlLoader&) = delete;
    DlLoader& operator=(const DlLoader&) = delete;

    SoPtr Load(std::string name_);
private:
    using LibMap = std::map<std::string, SoPtr>;  
    LibMap m_loaded;
};

/****************************************************************************/
}
/****************************************************************************/
#endif //_ILRD_DIRMON_

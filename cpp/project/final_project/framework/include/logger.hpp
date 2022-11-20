/*******************************************************************************
*								   								               *
*	PROJECT: lab              		    					               *
*	DATE: 2022-11-15					   					               *
*	AUTHOR: SAAEB SHIBLI					   					               *
*	REVIEWER: 						   							               *
*	VERSION: 1.0 						   						               *
*								   								               *
*******************************************************************************/
#ifndef __LOGGER_H__
#define __LOGGER_H__
/******************************************************************************/
#include <iostream>
#include <string>
#include <queue>
#include <atomic>

#include "singleton.hpp"
#include "wait_que.hpp"
/******************************************************************************/
namespace ilrd
{
class Logger	//must be singlton
{
private:
	friend class Singleton<Logger>;
public:
	enum Level_ty {DEBUG, ERROR, WARNING, INFO};

	~Logger() noexcept;
	void operator=(const Logger&) = delete;
	Logger(const Logger&) = delete;
	
	void SetLevel(Level_ty lvl_);
	void SetStream(std::string&);
	void Log(std::string str_, Level_ty lvl_);
private:
	explicit Logger() = default;
	std::atomic<std::ostream&> m_stream;
	std::atomic<Level_ty> m_level;
	WaitableQue<std::queue<std::string> > m_logsQ;
};
/******************************************************************************/
}	//NAMESPACE ILRD
/******************************************************************************/
#endif
/******************************************************************************/


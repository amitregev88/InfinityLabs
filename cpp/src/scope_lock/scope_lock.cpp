/****************************************************************************/
/*	Project:    Scope Lock													*/
/*	Date: 		30/10/2022													*/
/*	Name: 		Amit Regev      											*/
/*	Reviewer:																*/
/*	Version: 	1.00														*/
/****************************************************************************/

#include <iostream>	 	//	cout																	
#include <pthread.h>	// 	pthread_t
#include "scope_lock.hpp"

#include "utility.hpp" 	

class Guard
{
public:
	Guard();
	~Guard() {};
	void Lock();
	void Unlock();

private:
	pthread_mutex_t m_guard;
};

Guard::Guard()
{
	pthread_mutex_init(&m_guard, NULL);
}

void Guard::Lock()
{
	pthread_mutex_lock(&m_guard);
}

void Guard::Unlock()
{
	pthread_mutex_unlock(&m_guard);
}
/****************************************************************************/
Guard g_guarder;

static void PrintNumOfCalls();
static void *ThreadAct(void *no_need_);




static void *ThreadAct(void *no_need_)
{
	(void)no_need_;
	
	try
	{
		PrintNumOfCalls();
	}
	catch(...)
	{
		std::cout << "Cought!\n";
	}

	return NULL;
}

static void PrintNumOfCalls()
{
	static int s_count = 0;
	ilrd::ScopeLock<Guard> lock(g_guarder);
	++s_count;
	std::cout << "Count is: " << s_count << "\n";

	if (s_count == 4)
	{
		throw(1);
	}
}

int main()
{
	pthread_t thread_id[5] = {0};
	int i = 0;
	int status = 0;

	for (i = 0; i < 5; ++i)
	{
		status = pthread_create(&thread_id[i], NULL, ThreadAct, NULL);
		
		if (status)
		{
			std::cout << "pthread_create() failure.\n";

			return 1;
		}
	}

	for (i = 0; i < 5; ++i)
	{
		status = pthread_join(thread_id[i], NULL);
				
		if (status)
		{
			std::cout << "pthread_join() failure.\n";

			return 1;
		}
	}

	return 0;
}

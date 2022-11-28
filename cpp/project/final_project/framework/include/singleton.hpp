/********************************************************************************/
/* PROJECT: Singleton                                                           */
/* DATE:                                                                        */
/* NAME: Amit Regev                                                             */  
/* REVIEWER:                                                                    */
/* VERSION: 1.00                                                                */
/********************************************************************************/
#ifndef __SINGLETON_HPP__
#define __SINGLETON_HPP__

namespace ilrd
{
/******************************************************************************/

template<typename T>
class Singleton
{
public:
    Singleton(const Singleton&) = delete;
    ~Singleton() noexcept;
    static T& GetInstance();
    Singleton& operator=(const Singleton&) = delete;

private:
    Singleton();
};

/******************************************************************************/
// static
template<typename T>
T& Singleton<T>::GetInstance()
{
    static T m_data;

    return m_data;
}
/******************************************************************************/
template<typename T>
Singleton<T>::Singleton()
{}
/******************************************************************************/
template<typename T>
Singleton<T>::~Singleton() noexcept
{}
/******************************************************************************/
} // namespace ilrd
#endif //   ifndef __SINGLETON_HPP__

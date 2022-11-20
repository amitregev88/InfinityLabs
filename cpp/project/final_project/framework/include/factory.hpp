/*******************************************************************************
* PROJECT: Factory
* FILE: factory.hpp
* DATE: 10/11/2022
* NAME: Amit Regev
* REVIEWER: 
* VERSION: 1.00
*******************************************************************************/
#ifndef __FACTORY_HPP__
#define __FACTORY_HPP__

#include <unordered_map>
#include <functional>

namespace ilrd
{
/******************************************************************************/
template<typename OBJ, typename KEY, typename ...ARGS>
class Factory
{
public:
    Factory() = default;
    Factory &operator=(const Factory &o_) = delete;
    ~Factory()noexcept = default;

    void Add(KEY key_, std::function<OBJ(ARGS...)> func_);
    OBJ Create(KEY key_, ARGS... args_);

private:
    std::unordered_map<KEY, std::function<OBJ(ARGS...)> > m_map;
};


template<typename OBJ, typename KEY, typename ...ARGS>
void Factory<OBJ, KEY, ARGS...>::Add(KEY key_, std::function<OBJ(ARGS...)> func_)
{
    m_map.insert( {key_, func_} );
}
/******************************************************************************/
template<typename OBJ, typename KEY, typename ...ARGS>
OBJ Factory<OBJ, KEY, ARGS...>::Create(KEY key_, ARGS... args_)
{
    return m_map[key_] (args_ ...);
}

/******************************************************************************/
} // namespace ilrd
#endif // ifndef __FACTORY_HPP__


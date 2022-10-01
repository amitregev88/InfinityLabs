#include <string>
#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <map> //map

namespace ilrd
{

class MapAdder
{
public:
    explicit MapAdder(std::map<std::string, size_t>* m_) : m_map(m_){};

    bool operator()(const std::string& str_){return ++(*m_map)[str_] > 0;};

private:

    std::map<std::string, size_t> *m_map;
};

class PrintNdelete
{
public:

    explicit PrintNdelete(std::map<std::string, size_t>* m_) : m_map(m_){};

    bool operator()(const std::string& str_);

private:

    std::map<std::string, size_t> *m_map;
};


bool PrintNdelete::operator()(const std::string& str_)
{
    if ((*m_map)[str_] > 0)
    {
        std::cout<< (*m_map)[str_] << " x " << str_<< std::endl;
        (*m_map)[str_] = 0;
        return 1;

    }
        return 0;
}

}


int main()
{
    using namespace ilrd;
    
    std::vector<std::string> str_vector;

    std:: map<std::string, size_t> map_list;

    MapAdder map_adder(&map_list);

    PrintNdelete count_str(&map_list);
    
    std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::back_inserter(str_vector));

    for_each(str_vector.begin(), str_vector.end(),map_adder); // add the string from vector to map

    for_each(str_vector.begin(), str_vector.end(),count_str);

    return 0;

}

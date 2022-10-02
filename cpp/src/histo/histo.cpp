//#include <string> //comments missing
#include <cassert> //assert
#include <algorithm> //for_each
#include <iostream> //cin, cout
#include <iterator> //istream_iterator
#include <vector> //vector
#include <map> //map

namespace ilrd
{

    static void Histo(void);

class MapAdder
{
public: 
    explicit MapAdder(std::map<std::string, size_t>* m_) : m_map(m_){};

    void operator()(const std::string& str_){assert(m_map); ++(*m_map)[str_];};

    // CCtor and Dtor are generated
    //operator assignment is disable

private:
	MapAdder& operator=(MapAdder&);    //do not impliment!
    std::map<std::string, size_t> * const m_map;
};

class PrintNdelete
{
public:

    explicit PrintNdelete(std::map<std::string, size_t>* m_) : m_map(m_){};

    void operator()(const std::string& str_); // maybe const this too

    // disable assignment operator
private:

	PrintNdelete& operator=(PrintNdelete&);    //do not impliment!

    std::map<std::string, size_t> *m_map;
};


void PrintNdelete::operator()(const std::string& str_)
{

    if ((*m_map)[str_] > 0)
    {
        std::cout<< (*m_map)[str_] << " x " << str_<< std::endl;
        (*m_map)[str_] = 0;

    }
        
}

}
  
    
void Histo()
{ 
    
    using namespace ilrd;
    
    std::vector<std::string> str_vector;

    std:: map<std::string, size_t> map_list;

    MapAdder map_adder(&map_list);

    PrintNdelete count_str(&map_list);
    
    std::copy(std::istream_iterator<std::string>(std::cin), std::istream_iterator<std::string>(), std::back_inserter(str_vector));

    for_each(str_vector.begin(), str_vector.end(),map_adder); // add the string from vector to map

    for_each(str_vector.begin(), str_vector.end(),count_str);


}

int main()
{
    Histo();

    return 0;
}
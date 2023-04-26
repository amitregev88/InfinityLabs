// g++ -std=c++11 -pedantic-errors -Wall -Wextra -g publisher_test.cpp ../src/thread_pool.cpp -lboost_chrono -lboost_thread -lpthread -I ../include/ -o pub
#include "shape_publisher.hpp"



int main()
{
    ShapePublisher pub;
    
    pub.Init(); 
    

    pub.Publish(); 

    return 0;
}

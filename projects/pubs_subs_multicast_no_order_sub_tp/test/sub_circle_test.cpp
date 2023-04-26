//g++ -std=c++11 -pedantic-errors -Wall -Wextra -g sub_circle_test.cpp ../src/thread_pool.cpp -lboost_chrono -lboost_thread -lpthread -I ../include/ -o sub_circle

#include "shape_subscriber.hpp"

int main()
{
    ShapeSubscriber sub(CIRCLE);

    sub.Register();
   
    return 0;
}

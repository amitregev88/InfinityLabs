//g++ -std=c++11 -pedantic-errors -Wall -Wextra -g sub_square_test.cpp ../src/thread_pool.cpp -lboost_chrono -lboost_thread -lpthread -I ../include/ -o sub_square

#include "shape_subscriber.hpp"

int main()
{

    ShapeSubscriber sub(SQUARE);

    sub.Register();
    

    return 0;
}

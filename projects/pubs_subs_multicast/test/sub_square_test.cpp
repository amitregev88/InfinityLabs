//g++ -std=c++11 -pedantic-errors -Wall -Wextra -g sub_square_test.cpp -I ../include/ -o sub_square


#include "shape_subscriber.hpp"

int main()
{


    ShapeSubscriber sub(SQUARE);



    sub.Register();



    return 0;
}

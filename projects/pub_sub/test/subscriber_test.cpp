#include "shape_subscriber.hpp"

int main()
{


    ShapeSubscriber sub(SQUARE, "127.0.0.1", 5000);



    sub.Register();



    return 0;
}

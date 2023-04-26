#include "shape_subscriber.hpp"

int main()
{
    ShapeSubscriber sub(CIRCLE, "127.0.0.1", 6000);



    sub.Register();



    return 0;
}

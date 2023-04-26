#include "shape_publisher1.hpp"



int main()
{
    ShapePublisher pub;
    
    pub.Init("127.0.0.1");
    

    pub.Publish(); 


    return 0;
}

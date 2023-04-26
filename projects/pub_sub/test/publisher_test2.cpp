#include "shape_publisher2.hpp"



int main()
{
    ShapePublisher pub;
    
    pub.Init(5000, "127.0.0.1");
    

    pub.Publish(); 


    return 0;
}

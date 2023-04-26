#include"square.hpp"
#include"circle.hpp"
#include"both.hpp"





int main()
{
    Square s(20, 5, 2);

    Circle c(10, 2.5, 1);

    Both b(10, 2.5, 1);



    s.Print();

    c.Print();

    b.Print();



    return 0;
}

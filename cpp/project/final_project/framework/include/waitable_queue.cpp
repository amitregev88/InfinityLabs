
#include <waitable_queue.hpp>
#include <iostream>


using namespace ilrd;

int main()
{

    WaitQueue<std::queue<int>> que;
    int n;

    que.Push(4);

    que.Pop(n);
    
    std::cout<<"n = "<<n<<std::endl;

    

    return 0;

}

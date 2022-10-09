/******************************************
*
* Project: 
* Author: Alex milys
* Reviewer:
* Description:  
* Date:
* Notes:	
******************************************/

#include <algorithm>
#include "ostream_iter.hpp" 

//using namespace std;
using namespace  ilrd;

int main()
{
    
    int arr[]={1,2,3,4,5};
    ilrd::OstreamIter<int> iter(std::cout);

    std::copy(arr,arr+5,iter);    
    
    return 0;
}


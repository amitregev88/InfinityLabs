/*************************************************************
* Author: Amit Regev
* Date: 13/7/22 
* OL124 KNIGHT TOUR project Test
*******************************************************************/
#include "knight_tour.h"

int main(void)
{
    int i =0;
    char track[65] = {0};

    track[64] = '\0'; 
   
    for(;i<64;++i)
    {
        KnightPath(track, i/8, i % 8);
    }
    
    return 0;
}

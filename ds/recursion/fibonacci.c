/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 22/6/22 
* OL124 Fibonacci recursion
*******************************************************************/

#include <stdio.h>

int Fibonacci(int elememt_index)
{
    if (elememt_index <= 1)
    {
        return elememt_index;
    }

    return Fibonacci(elememt_index - 1) + Fibonacci(elememt_index - 2);
}

int main(void)
{
    int index = 0;
    
    printf("enter index of element in Fibonacci sequence:\n");
    scanf("%d",&index);

    printf("The number in index %d of Fibonacci sequence is: %d\n",index, Fibonacci(index));

    return 0;

}

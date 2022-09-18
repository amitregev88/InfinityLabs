#include<stdio.h>

     /*const int i = 3; *//* read only segment. with voatile --> data segment*/

int nc = 10;
const int co = 20;


int main ()
{
    const int i = 3; 
    int *ip = (int*)&i;
    *ip = 5;
    //int arr[i];
    

    printf("%d %d \n", i, *ip);
    return 0;
}


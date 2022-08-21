#include<stdio.h>

void RemoveDup(int sorted_arr[], size_t size);

int main(void)
{
    int arr[10] =  {0,0,1,1,1,2,2,3,3,4};
    int i = 0;

    RemoveDup(arr,10);

    for(;i<10;++i)
    {
        printf("%d ",arr[i]);
    }
    
    
    return 0;
}

void RemoveDup(int sorted_arr[], size_t size)
{
    size_t i = 0, j = 0;

    for(;i < size; ++i)
    {
        while(j < size-1 && sorted_arr[j] - sorted_arr[j+1] == 0)
        {
            i = j;
            j++;
        }

        while(i == j)
        {

            sorted_arr[j] = sorted_arr[j + 1];
            j--;    

        }
        
    }

}
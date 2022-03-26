#include <stdio.h>

#define R 5
#define C 6

void sum(int arr[R][C], int arrsum[R]);


int main()
{
	int arrsum[R] = {0};

    int arr[R][C] = {{1,4,7,3,0},{7,8,4,2,6},{6,4,6,4,4},{2,4,7,2,9},{1,4,1,3,0}};
    
    sum(arr, arrsum);		 

  return 0;
}


void sum(int arr[R][C], int arrsum[R])
{
    int rsum = 0;
    int i = 0, j = 0;
    

    for (; i < R; i++)
    {
    	rsum = 0;
        for (j = 0; j < C; j++)
	    {
	        rsum = rsum + arr[i][j];
	    }
	    arrsum[i] = rsum;
        
    }

    printf("\nRow Sum is:\n");
  
    for(i = 0; i < R; i++)
    {
       printf("%d ",arrsum[i]);
    }
}



#include <stdio.h> 
#include <stdlib.h> 

void TF (int num);

int main()
{
    
    int a = 100;

    TF(a);
 
    return 0;
}
    
    
void TF (int num)
{
    int i = 1;
    
  if (num < 1)
   {
    printf("number less than 1");
    exit (1);
   }

    

    for (i; i<= num ; i++)
    {
        if ((i % 3 == 0) && (i % 5 == 0))
        {
            printf("TF ");
        } 
        else if (i % 3 == 0)
        {
            printf("T ");
        }
        else if (i % 5 == 0)
        {
            printf("F ");
        }
        else
        {
            printf("%d ",i);
        }
    }
}
 

/*ex_7 swap values*/

#include <stdio.h>

void swap(int *x, int *y);

int main()
{
int num1, num2;
printf("Enter two numbers\n");
scanf("%d%d",&num1,&num2);
swap(&num1,&num2);
printf("The numbers after swap: %d  %d\n",num1 ,num2);

return 0;
}

void swap(int* x, int* y)
{
int tmp = *x;
*x = *y;
*y = tmp;


}


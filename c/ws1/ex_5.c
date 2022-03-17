/*ex 5 - tenpowx */
#include<stdio.h>

float tenpowx(int n);

int main(void)
{
	int n;
	printf("Enter a pow - n\n");
	scanf("%d",&n);
	printf("The 10^%d is -- %.2f\n", n, tenpowx(n));
	
	return 0;
}

float tenpowx(int n)
{
	float res = 1, i;
	float num = 10;
	
	if (n < 0)
	{
		num = 1 / num; 
		n *= -1;
		
	}		
	for(i = 0; i < n; i++)
	{
		res *= num;
			
	}
		
	return res;
}

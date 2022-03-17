/*ex_6 - flip number*/

#include<stdio.h> 
int flip(int num);

int main ()
{
	int number;
	printf("Enter a number:\n");
	scanf("%d", &number);
	printf("The flip number is: %d:\n", flip(number));
	return 0;
}

int flip(int num)
{
	int tmp = 0;
	while(num != 0)
	{
		tmp = tmp * 10 + (num % 10);
		num /= 10;
	}
	return tmp;
}
	

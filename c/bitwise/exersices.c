/* ***********************************************************
*Author: Amit Regev
*Reviewer: 
*Description:  bitwise operation.
*Infinity Labs: OL124	
***************************************************************/

/*calculate x*(2^y) by bit operation*/
/*
#include <stdio.h>
long Pow2(unsigned int x, unsigned int y)
{
	

	return x<<y;
	
	
}

int main()
{
	unsigned int x = 5, y = 3;
	long res;  
	
	res = Pow2(x,y);
	printf("the result is: %ld\n", res);
	
	return 0;
}
/*
/*** the  function checks if n is power of 2 (with loop)****/ 
#include <stdio.h>
int nPow2(unsigned int n)
{

	while (num <= n)
	{
		if (n == num)
			return 1;
			
		num = num<<1;
	}
		
	return 0;
	
}
/*** the  function checks if n is power of 2 (without loop)****/ 

#include <stdio.h>
int nPow2(unsigned int n)
{
	
	if ((n&(n-1)) == 0);
		return 1;
	else
		return 0;
}
	
		
		
	

int main()
{
	unsigned int x = 8;
	int res;  
	
	res = nPow2(x);
	printf("result: %ld\n", res);
	
	return 0;
}
/*********************

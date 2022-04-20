#include <stdio.h>

size_t CountCouplesOfSetBit(char* byte);
void swap1(int *num1, int *num2);
void swap2(int *num1, int *num2);
void swap3(int *num1, int *num2);

int main()
{
	char byte[] = "01110110";
	size_t count = 0;
	int num1 = 10;
	int num2 = 20;
	
	
	count =  CountCouplesOfSetBit(byte);
	
	printf("To given byte, there are %lu couples of set bits\n",count);
	
	
	printf("\nBefore execute swap1 functon: num1 = %d, num2 = %d\n", num1, num2);
	
	swap1(&num1, &num2);
	
	printf("After execute swap1 function: num1 = %d, num2 = %d\n",num1, num2);
	
	
	
	printf("\nBefore execute swap2 functon: num1 = %d, num2 = %d\n", num1, num2);
	
	swap2(&num1, &num2);
	
	printf("After execute swap2 function: num1 = %d, num2 = %d\n",num1, num2);
	
	
	
	printf("\nBefore execute swap3 functon: num1 = %d, num2 = %d\n", num1, num2);
	
	swap3(&num1, &num2);
	
	printf("After execute swap3 function: num1 = %d, num2 = %d\n",num1, num2);
	
	
	return 0;
}

size_t CountCouplesOfSetBit(char* byte)
{
	size_t counter = 0;
	size_t i = 0;
	int first_bit = 1;
	int second_bit = 2;
	
	
	for(;i<7;++i)
	{
		if (((int)byte & first_bit) && ((int)byte & second_bit))
		{
			++counter;
		}
		
		first_bit <<= 1;
		second_bit <<= 1;
	}
	return counter;
}


/*************************************/

void swap1(int *num1, int *num2)
{
	int temp = *num1;
	*num1 = *num2;
	*num2 = temp;
}

void swap2(int *num1, int *num2)
{
	*num1 = *num1 + *num2;
	*num2 = *num1 - *num2;
	*num1 = *num1 - *num2;
}

void swap3(int *num1, int *num2)
{
	*num1 = *num1 ^ *num2;
	*num2 = *num1 ^ *num2;
	*num1 = *num1 ^ *num2;
}
/******************************************/
int CountBits(unsigned long bits)
{
	int count = 0;
	while (bits & ~(bits-1))
	{
		bits &= (bits-1);
		count++;
	}	
	return count;
}
/************************************************/






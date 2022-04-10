/******************************************************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad
*Description: implemention of itoa()
*Infinity Labs OL124	
****************************************************************************/



#include <stdio.h> /* printf */

char* Itoa (int value , char *str, int base);

int main()
{

	int a = 1331;
	char b[50];
	int base = 16;
	
	printf("Itoa: A value %d in base %d is: %s\n", a, base, Itoa(a,b,base));
	
	return 0;
}	

/********************************implementation of itoa**********************************************/

char* Itoa (int value , char *str, int base)
{	
	int num = value;
	int sign_flag = 0;
	int counter_digit = 0;
	int i = 0;
	static int lut_index_value_to_ascii[36];
	
	for (i = 0; i < 9; i++)
	{
		lut_index_value_to_ascii[i] = i + 48;
		
	}
	for (i = 10; i < 37; i++)  /*traslation value to ascii  A-Z*/
	{	
		lut_index_value_to_ascii[i] = i + 55;
	
	}
	
	while (num != 0)
	{
 		num /= base;
		counter_digit++;
	}
	
 	if (value < 0)
 	
 	{
	 str[0] = '-';
	 sign_flag = 1;
	 value *= -1;
	 counter_digit++; 
	} 	
 	
  	for (i = counter_digit -1; i >= sign_flag;--i)
	{
 		str[i] = (char)(lut_index_value_to_ascii[value % base]); 
		value /= base;
	}

	
	str[counter_digit]= '\0';
	
	return str;
}






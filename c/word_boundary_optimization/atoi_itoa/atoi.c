/******************************************************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad
*Description: implemention of atoi() + tests
*Infinity Labs OL124	
****************************************************************************/


#include <stdio.h> /* printf*/
#include <string.h> /*strlen*/
#include <ctype.h> /*to lower*/

int Atoi (const char* str, int base);
int Test_Atoi (char *str);
void Test_Atoi2(void);


int main()
{

	char *str = "1331";

		
	printf("Atoi : %d\n",Atoi(str,10));
	
	
	printf("compare between my Atio to  system atio functions : %d\n", Test_Atoi(str));
	
	Test_Atoi2();
	
	return 0;
}	

int Atoi (const char* str, int base)
{
	int sign_flag = 0; 
	int i = 0;
	int digit = 0;
	int result = 0;
	int counter_digit = strlen(str);
	static int lut_index_ascii_to_value[256] = {0};
	
	for (i = 0; i < 256; i++)
	{
		lut_index_ascii_to_value[i] = 37;
	
	}
	
	for (i = 48; i < 58; i++)
	{
		lut_index_ascii_to_value[i] = digit;
		digit++; 
	}
	for (i = 97; i < 123; i++)
	{	
		lut_index_ascii_to_value[i] = digit;
		digit++; 
	}
	
	if ('-' == str[0])
 	{
		sign_flag = 1;
	} 
	
	if (lut_index_ascii_to_value[(int)(tolower(str[sign_flag]))] > 36)
	{
		return 0;
	}
	
	
 	
  	result = lut_index_ascii_to_value[(int)(tolower(str[sign_flag]))];
 	
	for (i = sign_flag + 1 ;i <= counter_digit -1;++i)
	{
		if (lut_index_ascii_to_value[(int)(tolower(str[i]))] > 36)
		{
			return result;
		}
		else
		{
 			result *= base;
 			result += lut_index_ascii_to_value[(int)(tolower(str[i]))]; 
 		}
 	}
 	
	if (sign_flag)
	{
		result *= -1;
	}
	
	return result;
}

int Test_Atoi(char *str)
{
	return Atoi(str,10) - atoi(str);
}

void Test_Atoi2(void)
{
	printf("str1 is -1. Comparison result: %d\n", Test_Atoi("-1"));
	printf("str2 is 0. Comparison result: %d\n",Test_Atoi("0"));
	printf("str3 is 15 1. Comparison result: %d\n",Test_Atoi("15 1"));
	printf("str4 is 1. Comparison result: %d\n",Test_Atoi("1"));
	printf("%d\n",Atoi("15 1", 10));
	printf("%d\n",atoi("15 1"));
}


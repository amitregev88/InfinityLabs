#include <stdio.h>
#include <string.h>
#include <ctype.h>

char* Itoa (int value , char *str, int base);
int Atoi (const char* str, int base);

int main()
{

	int a = -150;
	char *b;
	char *c;
	char *d = "-850";
	int e = 0;
	
	
	c = Itoa(a,b,10);
	
	printf("Itoa : %s\n",c);
	
	e = Atoi(d,10);
	
	printf("Atoi : %d\n",e);
	
	return 0;
}	

char* Itoa (int value , char *str, int base)
{	
	int num = value;
	int sign_flag = 0;
	int counter_digit = 0;
	int i = 0;
	

	
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
 			str[i] = (char)((value % base) + 48); 
			value /= base;
		}

	
	str[counter_digit]= '\0';
	
	
	return str;
}
/*****************************************************************************************/
int Atoi (const char* str, int base)
{
	int sign_flag = 0; 
	int i = 0;
	int digit = 0;
	int result = 0;
	int counter_digit = strlen(str);
	static int lut_ascii[256] = {0};
	
	for (i = 48; i < 58; i++)
	{
		lut_ascii[i] = digit;
		digit++; 
	}
	for (i = 97; i < 123; i++)
	{	
		lut_ascii[i] = digit;
		digit++; 
	}
	
	
		
	
	if ('-' == str[0])
 	
 	{
	 
	 sign_flag = 1;
	  
	} 	
 	
 	
 	result = lut_ascii[(int)(tolower(str[i]))];
 	
	for (i = sign_flag + 1 ;i <= counter_digit -1;++i)
	{
 		result *= base;
 		result += lut_ascii[(int)(tolower(str[i]))]; 
 			
 	}

	if (sign_flag)
	
	result *= -1;
	
	return result;

}


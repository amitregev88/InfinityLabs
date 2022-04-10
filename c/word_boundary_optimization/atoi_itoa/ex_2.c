/**************************************
*Author: Amit Regev
*Reviewer: Noan Dan Hadad
*Description:  The program print elements that appears in  str1 and str2 and not str3
*Infinity Labs OL124	
***********************************************************/
#include <stdio.h> /* printf */
#include <string.h> /* strlen, atoi */
#include <ctype.h> /* tolower */

#define BASE_10 10

#define STR_SIZE 600


void Comper2From3Arrays(const char* str1, const char* str2, const char* str3)
{
   
	int i =0;
    const char * s1 = str1;
	const char * s2 = str2;
    const char * s3 = str3;

    static char lut_apperences[256] = {0};
	
	while (*s1 )
	{
		if ( lut_apperences[(int)*s1] == 0 )
		{
			lut_apperences[(int)*s1] = 1;
		}
		s1++;
	}
	
	while (*s2)
	{
		if ( lut_apperences[(int)*s2] == 1 )
		{
			lut_apperences[(int)*s2] += 2;
		}
		s2++;
	}

	while (*s3)
	{
		lut_apperences[(int)*s3] += 4;
		s3++;
	}

	for (i = 0; i < 256; ++i)
	{	
		if (lut_apperences[i] == 3)
		{
			printf("%c ",(char)i );
		}
	}
}

int main(void)
{
	char s1[30] = "abcccdefggh";
	char s2[30] = "ceeollllhhghhhh";
	char s3[30] = "bvvvssssss";

	Comper2From3Arrays(s1, s2, s3);
	
  
    return 0;
}






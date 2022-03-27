/**************************************************
*Author: Amit Regev    
*Reviewer:	Alexander Bor
*OL124
*Description: Function to check if the given string is a palindrome
**************************************************/

#include <stdio.h> 
#include <string.h> 

int Ispalindrome(const char *str);

int main()
{
	char *s1 = "fhn5987h9348hf,mbn$#%^%@nsm";
	char *s2 = "45vn896ADy7%^@^%7yDA698nv54";
	
	if (Ispalindrome(s1) == 0)
		printf("The string %s is a palindrome.\n", s1);
	else
		printf("The string %s in not a palindrome.\n", s1);
	
	if (Ispalindrome(s2) == 0)
		printf("The string %s is a palindrome.\n", s2);
	else
		printf("The string %s in not a palindrome.\n", s2);
	return 0;
}

int Ispalindrome(const char *str)
{
	int i = 0;
	size_t j = strlen(str)-1;
	int flag = 0;
	
	while (i < (int)j)
	{
		if (*(str + i) != *(str + j))
		{
			flag = 1;
		}	
		++i;
		--j;
	}
			
	return flag;
}



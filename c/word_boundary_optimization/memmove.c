/******************************************************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad
*Description: implemention of memmove()
*Infinity Labs OL124	
****************************************************************************/

#include <stdio.h>
#include <string.h>

void *Memmove(void *dest, const void *src, size_t n);


int main()
{ 
	char str[20] = "0123456789";
	
	
	printf("Before memmove func: %s\n", str);

    Memmove(str + 5, str, 6);
    
   	printf("After memmove func: %s\n", str);
    	
	return 0;
}
   
void *Memmove(void *dest, const void *src, size_t n)   
{
	char *d = (char *)dest;
    char *s = (char *)src;
	size_t i = 0;
	
	if (s <= d && (s + n - 1) >= d)
	{	
		for (i = n - 1;i > 0;--i)
		{
			*(d + i) = *(s + i);
		}
	}
	
	else
	{
		for (i = 0; i < n;++i)
		{
			*(d + i) = *(s + i);
		}
	}
	return dest;
}

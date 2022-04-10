/******************************************************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad
*Description: implemention of memset()
*Infinity Labs OL124	
****************************************************************************/

#include <stdio.h>
void Memset(void *str, int c, size_t n)

{
	char *ptr = (char *)str;
	size_t i = 0;
	size_t len_word = sizeof(size_t); 
	char chunck_input_value[sizeof(size_t)];
	
	
	
	for (;(size_t)(ptr + i) % len_word && i < n; ++i)
	{
		ptr[i] = (char)c;
	}
	
	for (;(size_t)(ptr + i) % len_word == 0 && (n - i) >= len_word; i += len_word)  
	{
		*(size_t *)(ptr + i) = *(size_t *)chunck_input_value;
	}	
	for (;i < n;++i)
	{
		ptr[i] = (char)c;
	}
} 


int main()
{ 
	char str[20] = "Hello World";
	
	Memset (str + 11,'!',3);

	puts(str);

	return 0;
}
   
   
    

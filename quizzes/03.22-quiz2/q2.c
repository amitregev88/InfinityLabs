#include <stdio.h> 
#include <string.h>

void reversetolower(char *str);

int main()
{
    char string[] = "Hello World";
    
    printf("The string is: : %s\n", string);
    
    reversetolower(string);
    
    printf("Reverse and turn low case string:\t%s\n", string); 
    
    
    return 0;
}


  
void reversetolower(char *str)
{
	char *iter1 = str, *iter2 = str, ch;
	int len = 0, i = 0;
	len = strlen(str);
 
	for(; i < len-1; i++)
	{
		iter2++;
	}
	
		
	for (i = 0; i < len / 2; i++)
	{
		ch = tolower(*iter2);
		*iter2 = tolower(*iter1);
		*iter1 = ch;
		iter1++;
		iter2--;
	}
}	

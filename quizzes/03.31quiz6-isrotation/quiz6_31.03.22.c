#include <stdio.h>
#include <string.h>

int IsRotation(const char *s1, const char *s2);
int main()
{

	char* s1 = "12345";
	char* s2 = "45123"; 
	
	
	if(IsRotation(s1,s2))
	{
		printf("s2 is totation of s1\n");
	} 
	else
	{
		printf("s2 is not totation of s1\n");
	}
	return 0;
}


int IsRotation(const char *s1, const char *s2)
{ 
	int partition = 0;
    int size = strlen(s1);
	int condition1 = 0;
	int condition2 = 0;
	const char *s1_ptr = s1;
	const char *s2_ptr = s2;
	
	if (strlen(s1) != strlen(s2))
    {
    	return 0;
   	}    
	
	while (partition < size)
	{		
		condition1 = !(strncmp(s1_ptr, s2_ptr + partition, size - partition));
		condition2 = !(strncmp(s1_ptr + (size - partition), s2_ptr, partition));
		if (condition1 && condition2)
		{
			return 1;
		}
		partition++;
	}
		return 0;	      
}



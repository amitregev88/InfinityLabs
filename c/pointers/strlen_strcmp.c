#include <stdio.h>

size_t Strlen(const char *str);

int Strcmp(const char *string1, const char *string2);


int main()
{
	char str1[] = "amit";
	char str2[] = "Amit";
	
	printf("Str1 lenght = %lu\n",Strlen(str1));
	printf("Str2 lenght = %lu\n",Strlen(str2));		
	
	if(Strcmp(str1,str2) > 0)
	{
		printf("str1 is bigger then str2\n");
	}
	else if (Strcmp(str1,str2) < 0)
	{
		printf("str2 is bigger then str1\n");
	}
	else {printf("str1 and str2 are the same\n");}
	return 0;
}

size_t Strlen(const char *str)
{
	size_t result = 0;
	
	while (str[result]!= '\0')
	{
		result++;
	}
	return result;
}

int Strcmp(const char *string1, const char *string2)
{
	int i = 0, s1 = 0, s2 = 0;
	while (string1[i] != '\0') && string2[i] != '\0')
	{
		if(string1[i] > string2[i])
		{
			s1++;
		}
		 
		if else(string1[i] < string2[i])
		{
			s2++;
		}
	}
	if(s1 > s2)
	{
	return 1;
	}
	else if(s2 > s1)
	{
	return -1;
	}
return 0;
}
	


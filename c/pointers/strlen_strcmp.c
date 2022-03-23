#include <stdio.h>

size_t Strlen(const char *str);

int Strcmp (const char *str1, const char *str2);


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

int Strcmp (const char *str1, const char *str2)
{
	size_t n = 0;
	
	while ( (str1[n] != '\0') && (str2[n] != '\0') )
	{
		if (str1[n] != str2[n])
		{
			return (str1[n] - str2[n]);
		}
		else n++;
		
	}
	
	return (str1[n] - str2[n]); 
}


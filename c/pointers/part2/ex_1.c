 /*Strlen*/
size_t Strlen(const char *s)
{
    size_t count = 0;
    while(*s!='\0')
    {
        count++;
        s++;
    }
    return count;
}
 
 
/*copy char arr sorce  to char arr2 destination */
char* Strcpy(char *dest, const char *src)
{
	size_t i;

    for (i = 0; src[i] != '\0'; i++)
    	{
		dest[i] = src[i];
		}
	dest[i] = '\0';

	return dest;
}



/*copy string to char arr */

char* Strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';

	return dest;
	
/*compare between str1 and str2 for first n characters */
	
int Strncmp(const char *str1, const char *str2, size_t num)
{
	int i = 0;
	while (num > 0)
	{
		if (str1[i] != str2[i])
		{
			return str1[i] - str2[i];
		}
		else 
		{
			i++;
			num--;
		}
	}
		
	return str1[i] - str2[i];
}

/*compare between str1 and str2 -  case-insensitively */

int Strcasecmp(const char *s1, const char *s2)
{
	int res = 0;
	while (*s1 != '\0' && *s2 !='\0')
    {
	res = *s1 - *s2;
	if ((*s1 >= 65 && *s1 <= 90) || (*s1 >= 97 && *s1 <= 122))//checking if s1 between a-z or A-Z
    {
		if (res != 0 && res != 32 && res != -32) // this line checks if is not it the smame letter (ex- a-A)
		{ 
                return res;
        }
    }
	else if (res != 0) // s1 isn't alphabet. this condition checks if s1 and s2 are diffrent? 
	{
		return res;
	}
		s1++;
		s2++;    
    }
            
    return *s1 - *s2; 
   
}


/*The function  searches the occurrence of a specified character in the given string and returns the pointer to it.*/


char *StrChr(const char *str, int c)
{
    while (*str!='\0')
        {
            if (*str == (char)c)
                return (char*)str;
            str++;
        }    
    return NULL;
}

/*The function strdup() is used to duplicate a string. */
char *Strdup(const char *src)
{
    char *str = NULL;
    size_t len = Strlen(src);
    
    str = (char *)malloc(len * sizeof(char));
    return Strcpy (str, src); 
    
}

/*the Strcat() function contcatenates (joins) two strings.*/


char *Strcat(char *dest, const char *src)
{
	size_t dest_len = Strlen (dest);
	char* ptr = dest + dest_len; // make `ptr` point to the end of the dest string
	
	while (*src != '\0') // add characters of the src to the dest string
	{
		* ptr++ = * src++;
	}
	
	*ptr = '\0' ;
	return dest;
}



/* This function appends n characters from src string to dest string */
char* Strncat(char* dest, const char* src, size_t num)
{
    size_t dest_len = Strlen (dest);
    char* ptr = dest + dest_len;  // Make `ptr` point to the end of the destination string
 
    
    while (*src != '\0' && num != 0) // Adding characters of the source to the destination string
	{	
        *ptr++ = *src++;
        num--;
    }
 
    *ptr = '\0';
 
	return dest;
}
 
	
/*Ststr() - This function takes two strings s1 and s2 as an argument and finds the first occurrence of the sub-string s2 in the string s1.*/




	
	



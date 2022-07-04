/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 22/6/22 
* OL124 Implementation of functions from string.h recursively 
* Strlen, Strcmp, StrCpy, Strcat StrStr
*******************************************************************/
#include <stdio.h>
#include <string.h>

size_t Strlen(const char *str)
{
    size_t counter = 0;
    
    if(*str == '\0')
    {
        return counter;
    }

    ++str;
    counter = 1 + Strlen(str);
        
    return counter;
}

int Strcmp(const char *src1, const char *src2)
{
    int result = 0;
    
    if(*src1 == '\0' || *src2 == '\0' || *src1 != *src2)
    {
        return *src1 - *src2;  
    }

    ++src1;
    ++src2;

    result = Strcmp(src1, src2);

    return result;
}

char *Strcpy(char *dest, const char *src)
{
    if(*src == '\0')
    {
        *dest = *src;
        return dest;
    }

    *dest = *src;

    ++dest;
    ++src;

    Strcpy(dest, src);

    return dest;
}

char *Strcat(char *dest, const char *src)
{
    if(*dest == '\0')
    {
        Strcpy(dest,src);
        return dest;
    }

    dest++;

    Strcat(dest,src);

    return dest;
} 


char *Strstr(const char *haystack, const char *needle)
{
    size_t i = 0;
    
    if (*needle == '\0')
    {
        return (char *)haystack;
    }
 
    for (i = 0; i < Strlen(haystack); i++)
    {
        if (*(haystack + i) == *needle)
        {
            char* ptr = Strstr(haystack + i + 1, needle + 1);
            return (ptr) ? ptr - 1 : NULL;
        }
    }
 
    return NULL;
}
 
int main(void)
{
    char *text1 = "jjj lll sss";
	char *text2 = "jjj lll sss ??";
	char dest1[35] = "dddddd";
	char dest2[35] = "dddddd";
	char dest3[35] = "dddddd";
	char *needle = "l s";
    
/* ---------test for Strlen-------------- */
	printf("------------StrLen Test------------\n\n");
	printf("the length of text by Strlen is %lu\n", Strlen(text1));
	printf("the length of text by strlen original  is %lu\n\n", strlen(text1));

/* -----------test for Strcmp------------ */ 
	printf("------------Strcmp Test------------\n\n");
 	printf("the cmperison of text by of Strcmp is %d\n", Strcmp(text1, text2));
	printf("the cmperison of text by strcmp original returns %d\n\n", strcmp(text1, text2));

/*	-----------test for Strcpy------------ */
	printf("------------Strcpy Test------------\n\n");
	printf("the destination text is %s\n", dest1);
	printf("the destination text with Strcpy is %s\n", Strcpy(dest1, text1));
	printf("the destination text is %s\n", dest2);
	printf("the destination text with original strcpy is: %s\n\n", strcpy(dest2, text1));

    /* -------------test for Strcat------------- */
	printf("------------Strcat Test------------\n\n");
	printf("the source text is %s\n", text1);
	printf("the destination text is %s\n", dest3);	
	printf("the result text is %s\n", Strcat(dest3, text1));

    /* -------------test for Strstr------------- */
	printf("-----------Strstr Test------------\n\n");
	printf("the substring was found? with Strstr: %s\n", Strstr(text2, needle));
	printf("the substring was found? with original strstr: %s\n", strstr(text2, needle));

    return 0;
}
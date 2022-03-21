 
/*copy char arr sorce  to char arr2 destination */
Strcpy(char *dest, const char *src, size_t)
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

Strncpy(char *dest, const char *src, size_t n)
{
	size_t i;

    for (i = 0; i < n && src[i] != '\0'; i++)
		dest[i] = src[i];
	for ( ; i < n; i++)
		dest[i] = '\0';

	return dest;
----------------------------------------------------------------	
	*/
	int StrCmp (const char *str1, const char *str2)
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
	


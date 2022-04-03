#include <stdio.h>	/*printf*/
#include <stdlib.h>	/*malloc*/
#include <string.h>	/*strcpy, strlen*/
#include <assert.h> /*assert*/
#include <ctype.h>  /*tolower*/


char *Strdup(const char *src);

int main(int argc, char **argv , char **envp)
{

	char **copy_env = NULL;  /* dynamic allocation for array of pointers length (envp) */
	int i = 0, j = 0, k = 0;
	char *dup = NULL;
	
	
	
	for(i = 0;*(envp + i) != NULL;i++) /* for couting of env variable*/
	{}
	
	copy_env = (char **)malloc(sizeof(char *)*(i + 1)); /* index i started from 0 therefore i+1 */
 	assert(copy_env != NULL);  /*  check success of malloc*/
 	
 	*(copy_env + i) = NULL;
 	
 	for (j = 0; j < i; j++)
 	{
 	
 		dup = Strdup(envp[j]);
 		/*strtmp = strcpy(dup, envp[j]);*/
 	
 		for (k = 0; dup[k] != '\0';k++)
 		{
 			*(dup + k) = tolower(*(dup + k));
 		}
 		*(copy_env + j) = dup;
 		dup = NULL;
 	}
			
	copy_env[j] = NULL;
	
		
	for (i = 0;copy_env[i] != NULL; i++)
	{
		printf("%s\n", copy_env[i]);
		
	}
	
	for(i = 0; i < j; i++)
		free(copy_env[i]); 
		
	free(copy_env);	
	copy_env = NULL;
	
	return 0;

}

char *Strdup(const char *src)
{
	size_t len = 0;
	char *str = NULL;
	len = strlen(src);
	
	str = (char*)malloc(len * sizeof(char) + 1);
	assert(str != NULL);  /*  check success of malloc*/
	str[len]='\0';
	return strcpy(str, src);
} 


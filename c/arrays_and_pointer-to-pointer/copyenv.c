#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>



int main(int argc, char **argv , char **envp)
{

	char **copy_env = NULL;  /* dynamic allocation for array of pointers length (envp) */
	int i = 0;
	int j = 0;
	char *dup = NULL;
	
	
	for(i = 0;*(envp + i) != NULL;i++) /* for couting of env variable*/
	{}
	
	copy_env = (char **)malloc(sizeof(char *)*i);
 	assert(copy_env != NULL);  /*  check success of malloc*/
 	
	while( envp[j] != NULL)  
	{
		dup = (char*)malloc(strlen(envp[j]) * sizeof(char));
		assert(dup != NULL);  /*  checks success of malloc */ 
		copy_env[j] = strcpy(dup, envp[j]);
		j++;
	}
	
	copy_env[j] = NULL;
	
	i = 0;
	
	while (copy_env[i] != NULL)
	{
		printf("%s\n", copy_env[i]);
		i++;
	}
	
	
	for(i = 0; i < j; i++)
		free(copy_env[i]); 
		
	free(copy_env);	
	copy_env = NULL;
	
	return 0;

}


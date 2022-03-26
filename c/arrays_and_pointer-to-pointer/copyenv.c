#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>



int main(int argc, char **argv , char **envp)
{
	/*unsigned long int len = sizeof(envp)/sizeof(envp[0]);*/
	
	
	char **copy_env = NULL;  /* dynamic allocation for array of pointers length (envp) */
	static int i = 0;
	static int j = 0;
	char *dup = NULL;
	
	
	for(i=0;*(envp+i) != NULL;i++)
	{}
	copy_env=malloc(i*8);
	assert(copy_env != NULL);  /*  check success of malloc */
	
	
	while( envp[j] != NULL)
	{
		dup = (char*)malloc(strlen(envp[i])+1);
		assert(dup != NULL);  /*  check success of malloc */
		copy_env[j] = strcpy(dup, envp[j]);
		j++;
		free(dup);
		dup = NULL;
		
	}
	
	copy_env[j] = (char*)NULL;
	
	i = 0;
	
	while(copy_env[i] != NULL)
	{
		printf("%s\n", copy_env[i]);
		i++;
	}
	
	free(copy_env);	
	copy_env = NULL;
	
	return 0;

}





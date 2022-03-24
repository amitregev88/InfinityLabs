#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>



int main(int argc, char **argv , char **envp)
{
	char *copy = (char*)malloc(strlen(*envp));
	int i = 0;
	
	assert(copy != NULL);
	
	while(*(envp+i) != NULL)
	{
		
		strcpy(copy+i , *(envp+i));
		i++;
		
	
	}
	
	*(copy + i) = (char)NULL;
	i = 0;
	
	while((copy+i) != NULL)
	{
		
		printf("%s\n", (copy+i));
		i++;
		
	
	}
	
	

	free(copy);	
	
	return 0;
	


}

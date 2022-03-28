#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE* file = NULL;
	char str_path[] = {"/home/amit/git/c/files/readme"};
	char string[100];
	 
	
	file = fopen(str_path,"a");
	if (file == NULL)
	{
	printf("Error open file\n");
	exit(1);
	}
	
	printf("Enter a string:\n");
	fgets(string,100,stdin); /* fgets insert input to string*/
	fputs(string, file); /* fputs insert the char string to file (stream*)*/
	
	fclose(file);

	return 0;
}

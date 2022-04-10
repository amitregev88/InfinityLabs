/************************************************************************************
*Author: Amit Regev
*Reviewer: Sveta Blum
*Description:  recieve a string from user and append to file.
**Infinity Labs OL124	

************************************************************************************/
#include <stdio.h>


int main()
{
	FILE* file = NULL;
	char file_name[20];
	char string[100];
	 
	printf("Enter the file name to create:\n");
	fgets(file_name,20, stdin);
	
	
	file = fopen(file_name,"a");
	if (file == NULL)
	{
		printf("Error open a file\n");
		return(1);
	}
	
	printf("Enter a string:\n");
	fgets(string,100,stdin); /* fgets insert input to string*/
	fputs(string, file); /* fputs insert the char string to file (stream*)*/
	
	fclose(file);

	return 0;
}

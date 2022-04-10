/************************************************************************************
*Author: Amit Regev
*Reviewer: Sveta Blum
*Description:recieve a string from user and append to file with "special input".
			 using enum in  operation function
*Infinity Labs OL124	
************************************************************************************/
#include <stdio.h>	/*printf*/
#include <string.h> /*str*/
#include <stdlib.h>/* exit, system*/

#define MAX_STRING 200


typedef int (*ptr_cmpfunc)(char *s_in);  /*creating a pointer to function type*/ 
typedef void (*ptr_operfunc)(int flag, char *s_in, char *fname); /*creating a pointer to function type*/ 

typedef struct
{

	char *str;
	ptr_cmpfunc ptr_cmp;
	ptr_operfunc ptr_oper;

}logger;

enum Isbool {ture, false};


/*************************declarations of comparison function************************************************/
int CompRm(char *s_in);
int CompCount(char *s_in);
int CompExit(char *s_in);
int CompBegin(char *s_in);
int CompDefault(char *s_in);
/*************************declarations of operation function************************************************/
enum Isbool OperRm(int flag, char *s_in, char *fname);
enum Isbool OperCount(int flag, char *s_in, char *fname);
enum Isbool OperExit(int flag, char *s_in, char *fname);
enum Isbool OperBegin(int flag, char *s_in, char *fname);
enum Isbool OperDefault(int flag, char *s_in, char *fname);
int main (int argc, char **argv);


int main (int argc, char **argv)
{
	char string[MAX_STRING] = {0};
    int i = 0, flag = 0;
    logger log_arry[5];
    char fname[20];
    
    
    ptr_cmpfunc ptr_comprm = &CompRm;
    ptr_cmpfunc ptr_compcount = &CompCount;
    ptr_cmpfunc ptr_compexit = &CompExit;
    ptr_cmpfunc ptr_compbegin = &CompBegin;
    ptr_cmpfunc ptr_compdefault = &CompDefault;
    
    ptr_operfunc ptr_operrm = &OperRm;
    ptr_operfunc ptr_opercount = &OperCount;
    ptr_operfunc ptr_operexit = &OperExit;
    ptr_operfunc ptr_operbegin = &OperBegin;
    ptr_operfunc ptr_operdefault = &OperDefault;
    
          
  
        /* initialization of log arry*/
    log_arry[0].str = string; 
    log_arry[0].ptr_cmp = ptr_comprm;
    log_arry[0].ptr_oper = ptr_operrm;
    log_arry[1].str = string; 
    log_arry[1].ptr_cmp = ptr_compcount; 
    log_arry[1].ptr_oper = ptr_opercount;
    log_arry[2].str = string; 
    log_arry[2].ptr_cmp = ptr_compexit; 
    log_arry[2].ptr_oper = ptr_operexit;
    log_arry[3].str = string;
    log_arry[3].ptr_cmp = ptr_compbegin;
    log_arry[3].ptr_oper = ptr_operbegin;
    log_arry[4].str = string; 
    log_arry[4].ptr_cmp = ptr_compdefault;
    log_arry[4].ptr_oper = ptr_operdefault;

	printf("Enter a file name to create\n");
	fgets(fname,20,stdin);
	
	
    while (1)
    {
        printf("Please enter a string and in the end press Enter\n");
        fgets(string, MAX_STRING, stdin);
 
    	
    	 for (i = 0; i < 5; ++i)
    	 {
    	      log_arry[i].str = string;
    	      flag = log_arry[i].ptr_cmp(log_arry[i].str);
    	      log_arry[i].ptr_oper(flag, log_arry[i].str,fname);
    	 }     
    }
    
	**argv = **argv;
	argc = argc;
	return 0;
}

/*************************definitions of comparison function *******************************/
int CompRm(char *s_in)
{
	 
	if(strcmp(s_in,"-remove\n") == 0)
		return 1;
	else
		return 0;
}

int CompCount(char *s_in)
{
	
	if (strcmp(s_in,"-count\n") == 0)
		return 1;
	else
		return 0;
}	

int CompExit(char *s_in)
{
	
	if (strcmp(s_in,"-exit\n") == 0)
		return 1;
	else
		return 0;
}	

int CompBegin(char *s_in)
{
	if (s_in[0] == '<')
		return 1;
	else
		return 0;
}

int CompDefault(char *s_in)
{
	if ((CompBegin(s_in)) || (CompExit(s_in)) || (CompCount(s_in)) || (CompRm(s_in)))
	
		return 0;
	else 
		return 1;
}

/*************************definitions of operation function ************************************************/
void OperRm(int flag, char *s_in, char *fname)
{
	s_in = s_in;
	
	if (flag)
	{
		remove (fname);
		printf ("File %s removed succesfully\n", fname);
	}
	
}

void OperCount(int flag, char *s_in, char *fname)
{
	s_in = s_in;
	
	if (flag)
	{
		FILE *fp = fopen(fname, "r");
		char c;
		int counter = 0;
		
		if (fp == NULL)
			{
				fprintf (stderr,"Failed to open the file %s\n", fname);
				exit(1);
			}
	
    	for (c = getc(fp); c != EOF; c = getc(fp))
        	{
            	if (c == '\n') 
            	++counter;
        	}
		printf("number of lines is: %d\n", counter);
	
		fclose(fp);
	}
	
}

	
void OperExit(int flag, char *s_in, char *fname)
{
	s_in = s_in;
	fname = fname;
	
    if(flag)
    {
        exit(0);
    }
    
}

void OperBegin(int flag, char *s_in, char *fname)
{
	if (flag)
	{
		FILE *fp = fopen(fname, "r");
		FILE *fp2 = fopen ("temp.txt", "w");
		char temp_char;
		
		if (NULL == fp || NULL == fp2)
		{
			fprintf (stderr, "Files openning failed\n");
			exit (1);
		}
		
		/*	this loop duplicates the original file to temporary one	*/
		for (temp_char = fgetc(fp);temp_char != EOF;temp_char = fgetc(fp))
		{
			fputc (temp_char, fp2);
		}
		
		fclose (fp);
		fclose (fp2);
		
		/*	removing the original file  */
		remove(fname);
		
		/*	open again the FILE_NAME add a *str in the beginning and then copy the temp.txt to it*/
		fp = fopen (fname, "a+");
		fp2 = fopen ("temp.txt", "r");
		
		if (fp == NULL || fp2 == NULL)
		{
			fprintf (stderr, "Files openning failed\n");
			exit (1);
		}
		
		/*	adding the str without a '<' character	*/
		fputs ((s_in + 1), fp);
		
		/*	copies the temp.txt to file_name	*/
		for (temp_char = fgetc(fp2); temp_char != EOF; temp_char = fgetc(fp2))
		{
			fputc (temp_char, fp);
		}
		
		fclose (fp);
		fclose (fp2);
		remove ("temp.txt");
	}
}

void OperDefault(int flag, char *s_in, char *fname)
{
    if(flag)
    {
		FILE *fp = fopen(fname, "a");
         
		if (fp == NULL)
			{
				fprintf (stderr,"Failed to open the file %s\n", fname);
				exit(1);
			}
        
		fputs(s_in, fp);      
        fclose(fp);        
    }
}

	



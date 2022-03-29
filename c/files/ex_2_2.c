/************************************************************************************
*Author: Amit Regev
*Reviewer: 
*Description:  recieve a string from user and append to file with "special input"
**Infinity Labs OL124	

************************************************************************************/
#include <stdio.h>	
#include <string.h> /*str*/
#include <stdlib.h>/*system*/

typedef int(ptr_cmpfunc)(char *s_in)); /*create a pointer to function type*/ 
typedef void(ptr_operfunc(int res, const char *fname);

/*************************declarations of comparison function************************************************/
int ptr_cmpfunc CompRm(char *s_in);
int ptr_cmpfunc CompCount(char *s_in);
int ptr_cmpfunc CompExit(char *s_in);
int ptr_cmpfunc CompBegin(char *s_in);
int ptr_cmpfunc Defult(char *s_in);
/*************************declarations of operation function************************************************/
void ptr_operfunc OperRm(int res const char *fname);
void ptr_operfunc OperCount(int res const char *fname);




typedef struct{

char str[];

ptr_cmpfunc ptr_Cmp;

ptr_operfunc ptr_Oper;

} name;


int main()
{



	return 0;
{

/*************************definitions of comparison function ************************************************/
int ptr_cmpfunc CompRm(char *s_in)
{
	if(strcmp(s_in,"-remove") == 0)
		return 1;
	else
		return 0;
}

int ptr_cmpfunc CompCount(char *s_in)
{
	
	if (strcmp(s_in,"-count") == 0)
		return 1;
	else
		return 0;
}	

int ptr_cmpfunc CompExit(char *s_in)
{
	
	if (strcmp(s_in,"-exit") == 0)
		return 1;
	else
		return 0;
}	

int ptr_cmpfunc CompExit(char *s_in)
{
	
	if (strcmp(s_in,"-exit") == 0)
		return 1;
	else
		return 0;
	}

int ptr_cmpfunc CompBegin(char *s_in)
{
	if (strncmp(s_in,"<",1) == 0)
		return 1;
	else
		return 0;
}

int ptr_cmpfunc Defult(char *s_in)
{
	if ((CompBegin(s_in)) || (CompExit(s_in)) || (CompCount(s_in)) || (CompRm(s_in)))
	
		return 0;
	else 
		return 1;
}

/*************************definitions of operation function ************************************************/
void ptr_operfunc OperRm(int res const char *fname)
{
	if (res)
		system("rm ", fname);
}

	
void ptr_operfunc OperCount(int res const char *fname)
{
	if (res)
		fopen(fname, r 
}			
			

	



/**************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad
*Description:  checks whether is little-endian by macros. 
*Infinity Labs OL124	
***********************************************************/
#include <stdio.h> /*printf*/

#define IS_LITTLE_ENDIAN *(char *)&argc? 1:0


int main(int argc, char **argv)
{
	if(IS_LITTLE_ENDIAN) 
	{
		printf("it is little-endian\n");	
	}
	else
  	{
  		printf("it is big-endian\n");
  	}
  	

	return 0;
}

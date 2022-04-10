/**************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad
*Description:  The program checks whether is little-endian. 
*Infinity Labs OL124	
***********************************************************/
#include <stdio.h>



void IsLittlendian (void);

int main(void)
{
	
	IsLittlendian();
	
	return 0;
}	


void IsLittlendian (void)
{
	int n = 1;
	
	if(*(char *)&n == 1) 
	{
		printf("it is little-endian\n");	
	}
	else
  	{
  		printf("it is big-endian\n");
  	}
  	
  	  	
    return;
}


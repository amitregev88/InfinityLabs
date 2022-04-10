/**************************************
*Author: Amit Regev
*Reviewer: Noam Dan Hadad 
*Description:  implementation memset
*Infinity Labs OL124	
***********************************************************/


#include <stdio.h>

#define SIZEOF_TYPE(t) ((char *)(((t *)0) + 1) - (char *)0)

int main()
{

	printf("%lu\n", SIZEOF_TYPE(double)); 
	
 
	return 0; 
}




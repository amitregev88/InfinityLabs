#include <stdio.h>

#define SIZEOF_TYPE(t) ((char *)(((t *)0) + 1) - (char *)0)



int main()
{

	
	printf("%lu\n", SIZEOF_TYPE(int)); 
	
 
	return 0; 
}

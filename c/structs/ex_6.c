#include <stdio.h>

#define SIZEOF_VAR(x) ((char *)(&x + 1) - (char *) &x)
typedef struct
{
	int a;
	int b;
	float c;
	char d;
}test;


int main()
{

	double a = 0;
	test b; 
	printf("size of type a variable is:%ld bytes\n", SIZEOF_VAR(a)); 
	printf("size of type b variable is:%ld bytes\n", SIZEOF_VAR(b)); 
 
	return 0; 
}

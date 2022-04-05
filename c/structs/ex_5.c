#include<stdio.h>

#define MAX2(a,b) (a > b) ? a : b 
#define MAX3(a,b,c) (a > b) ? ((a > c) ? a : c) : ((b>c) ? b :c)

int main()
{
	printf("A greater value from (15,2) is %d\n", MAX2(15,2)); 
	printf("A greater value ftom (3,20) is %d\n", MAX2(3,20));
	printf("A greater value from (10,9,2) is %d\n", MAX3(10,9,2));
	printf("A greater value from (10,11,3) is %d\n", MAX3(10,11,3));
	printf("A greater value from (10,11,20) is %d\n", MAX3(10,11,20));
  return 0;
}

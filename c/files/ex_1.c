#include <stdio.h>

typedef void (*ptrfunc)(int); 


typedef struct /* my strucut*/
{

int num;  
ptrfunc print;

}print_me;


void Print(int n) /* define a function */
{
	printf("%d",n);
}

int main()
{
	int i = 0;
	print_me arr[10];
	
	/*  print_me arr[10]= {{1, &dk,},{2, }}  initallizing */

	for (i=0; i < 10; i++)
	{
	arr[i].num = i;
	arr[i].print = &Print;
	
	(*(arr[i].print))(arr[i].num);
	}
	return 0;
}


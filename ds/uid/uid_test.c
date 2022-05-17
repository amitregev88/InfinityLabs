/*************************************************************
* OL124  uid number
* 
* uid.h
* uid.c
* uid_test.c
******************************************************************/
#include <stdio.h> 
#include "uid.h"
#include <sys/types.h>


#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  (x)==(y)? IF_SUCCESS(1) : IF_SUCCESS(0)


void UIDTest(void);

int main()
{
	
	UIDTest();

	return 0;
}


void UIDTest(void)
{
	uid_ty uid = {0,0,0}; 
	
	uid = GetUID();

	printf("\ntesting of UIDIsSame() function:\n\n");
	
	TEST(UIDIsSame(UID_INVALID, UID_INVALID), 1);
	
	printf("\ntesting of  GetUID():\n\n");
	
	TEST(UIDIsSame(uid,UID_INVALID), 0);
	
}
	
	
	










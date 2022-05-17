/*************************************************************************************
* OL124 Circular Buffer Project
* 
* Name: Alexander Bor 
* Reviewer: 
* Date: 24.04.2022
*   
*************************************************************************************/


#include <stddef.h> /* NULL */
#include <stdio.h>	/* printf()*/
#include "circ_buffer.h" /* API */
#include <string.h>

#define __MSG_SUCCEED__ printf ("This test SUCCEEDED\n")
#define __MSG_FAILURE__ printf ("This test FAILED\n")
#define __TEST_MSG__(a,b) if (a == b) {__MSG_SUCCEED__;} else {__MSG_FAILURE__;}

/*
struct circ_buffer 
{
    void *data;
    void *head;
    void *tail;
    size_t size;
   
};
*/

void TEST_1()
{
	circ_buffer_ty *buffer = NULL;
	
	printf ("\n--------------------------- TEST #1 -----------------------------\n\n\n");
	printf ("\nNow testing -------- BufferCreate(20) --------\n\n");
	buffer = BufferCreate(20);
	__TEST_MSG__(BufferSize(buffer), 20);
	printf ("\nNow testing -------- BufferIsEmpty(buffer) --------\n\n");
	__TEST_MSG__(BufferIsEmpty(buffer), 1);
	
	BufferDestroy(buffer);
	
}

void TEST_2()
{
	char str1[21] = "alexander.bor.3100694";
	char str2[21] = "i am";
	circ_buffer_ty *buffer = NULL;
	printf ("\n--------------------------- TEST #2 -----------------------------\n\n\n");
	printf ("\nNow testing -------- BufferCreate(20) --------\n\n");
	buffer = BufferCreate(20);
	__TEST_MSG__(BufferSize(buffer), 20);
	printf ("\nNow testing -------- BufferIsEmpty(buffer) --------\n\n");
	__TEST_MSG__(BufferIsEmpty(buffer), 1);
	
	printf ("\nNow testing -------- BufferWrite(buffer, str1, 13) == 'alexander.bor'--------\n\n");
	__TEST_MSG__(BufferWrite(buffer, str1, 13), 13);

	printf ("\nNow testing -------- BufferFreeSpace() == 7 ? --------\n\n");;
	__TEST_MSG__(BufferFreeSpace(buffer), 7);
	
	printf ("\nNow testing -------- BufferRead(buffer, str2, 9) == alexander --> .bor--------\n\n");
	__TEST_MSG__(BufferRead(buffer, str2, 9), 9);
	printf("%s\n", str2);
	
	__TEST_MSG__(BufferFreeSpace(buffer), 16);
	
	printf ("\nNow testing -------- BufferWrite(buffer, str1, 13) == .boralexander.bor--------\n\n");
	__TEST_MSG__(BufferWrite(buffer, str1, 13), 13);
	
	printf ("%ld\n",BufferFreeSpace(buffer));
	
	
	printf ("\nNow testing -------- BufferRead(buffer, str2, 20) .boralexander.bor--------\n\n");
	__TEST_MSG__(BufferRead(buffer, str2, 20), 17);
	printf("%s\n", str2);
	
	BufferDestroy(buffer);
}

void TEST_3()
{
	char str1[21] = "alex.bor.3100694";
	char str2[21] = "i";
	char str3[21] = "i";
	circ_buffer_ty *buffer = NULL;
	printf ("\n--------------------------- TEST #3 -----------------------------\n\n\n");
	printf ("\nNow testing -------- BufferCreate(8) --------\n\n");
	buffer = BufferCreate(8);
	__TEST_MSG__(BufferSize(buffer), 8);
	printf ("\nNow testing -------- BufferIsEmpty(buffer) --------\n\n");
	__TEST_MSG__(BufferIsEmpty(buffer), 1);
	printf ("\nNow testing -------- BufferWrite(buffer, str1, 13) --------\n\n");
	__TEST_MSG__(BufferWrite(buffer, str1, 13), 8);
	
	printf ("\nNow testing -------- BufferRead(buffer, str2, 4) --------\n\n");
	__TEST_MSG__(BufferRead(buffer, str2, 4), 4);
	puts(str2);
	
	printf ("\nNow testing -------- BufferRead(buffer, str3, 1) --------\n\n");
	__TEST_MSG__(BufferRead(buffer, str3, 1), 1);
	puts(str3);
	
	printf ("\nNow testing -------- BufferWrite(buffer, str1, 4) --------\n\n");
	__TEST_MSG__(BufferWrite(buffer, str1, 4), 4);
	
	printf ("\nNow testing -------- BufferWrite(buffer, str1, 4) --------\n\n");
	__TEST_MSG__(BufferWrite(buffer, str1 + 9, 4), 1);
	
	printf ("\nNow testing -------- BufferRead(buffer, str3, 20) --------\n\n");
	__TEST_MSG__(BufferRead(buffer, str3, 20), 8);
	puts(str3);
	
	BufferDestroy(buffer);
}

int main()
{
	
	TEST_1();
	TEST_2();
	TEST_3();
	return 0;
}




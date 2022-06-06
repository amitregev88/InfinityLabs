/*************************************************************************************
* Name: Amit Regev 
* 
* Date: 26.05.22
* Variable Size Allocator Test
**************************************************************************************/

#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free */
#include "vsa.h"

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


int main()
{

	vsa_ty *new_vsa;
	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;

	size_t neto = 204 - 4 - 16 - 8;

	void *new_pool = malloc(208);
    if (new_pool == NULL)
	{
		printf("Memory allocation failed\n");
        return 1;
	}
    
    printf("\nTesting of VSAInit and VSALargestChunkAvailable functions:\n");
    new_vsa = VSAInit((char *)new_pool + 4, 204);
	TEST(neto,VSALargestChunkAvailable(new_vsa));

    printf("\nTesting of VSAAlloc and VSALargestChunkAvailable functions:\n");
    block1 = VSAAlloc(new_vsa, 168);
	TEST(0, VSALargestChunkAvailable(new_vsa));

	block2 = VSAAlloc(new_vsa, 16);
	TEST(NULL,block2);

    
    printf("\nTesting of VSAFree,  VSAAlloc and VSALargestChunkAvailable functions:\n");
    VSAFree(block1);	
	block2 = VSAAlloc(new_vsa, 104);
	TEST(64,VSALargestChunkAvailable(new_vsa));

	block3 = VSAAlloc(new_vsa, 24);
	TEST(32,VSALargestChunkAvailable(new_vsa));


	free(new_pool);
	new_pool = NULL;
	
    return 0;
}

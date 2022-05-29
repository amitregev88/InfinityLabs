/******************************************
* OL124 VSA
* vsa.h
* vsa.c
* vsa_test.c 
*
* Revision 2.0
******************************************/
/* --DEMO--

int main()
{

    vsa_ty *vsa;
    
    void *pool = NULL;
    struct kolshehu *block = NULL;
    
    pool = malloc(pool_size);
    
    vsa = VSAInit(pool, pool_size);
    
    block = VSAAlloc(vsa, sizeof(*block));
    
    FSAFree(block);
    
    return 0;
}
*/


#include "vsa.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

#define __MSG_SUCCEED__ printf ("This test SUCCEEDED\n")
#define __MSG_FAILURE__ printf ("This test FAILED\n")
#define __MSG_FUNC_NAME__(a) printf ("-------------- Now Testin ---- a() ----\n")
#define __TEST__(a, b, c) if ((a) b (c)) {__MSG_SUCCEED__;} else {__MSG_FAILURE__;}
#define __TEST_ITER__(a, b) if(SListIsSameIter(a, b)){__MSG_SUCCEED__;}else{__MSG_FAILURE__;}

typedef struct test
{
    size_t first;
    size_t second;
}test_ty;

static size_t GetBlockSize(vsa_ty *vsa);

int TEST_1()
{
    vsa_ty *head = NULL, *block1 = NULL, *block2 = NULL, *block3 = NULL;
    void *pool = malloc (85);
    size_t size = 0;

    if(NULL == pool)
    {
        return 0;
    }

    size = 85;
    

    printf ("\n--------------------------- TEST #1 -----------------------------\n\n\n");

	printf ("\nNow testing -------- VSAInit(pool, 85) --------\n\n");
    head = (vsa_ty *)VSAInit(pool, size);
	__TEST__(head, !=, NULL);
     printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 72 ?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 72);

    printf ("\nNow testing -------- VSAAlloc(head) ?--------\n\n");	
    block1 = (vsa_ty *)VSAAlloc(head, 20);
	__TEST__(GetBlockSize((vsa_ty*)((char*)block1 - WORD_SIZE)), ==, 24);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 40?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 40);
	

    printf ("\nNow testing -------- VSAAlloc(head, 16) ?--------\n\n");	
    block2 = (vsa_ty *)VSAAlloc(head, 15);
	__TEST__(GetBlockSize((vsa_ty*)((char*)block2 - WORD_SIZE)), ==, 16);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 16?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 16);

    printf ("\nNow testing -------- VSAAlloc(head, 6) ?--------\n\n");	
    block3 = (vsa_ty *)VSAAlloc(head, 6);
	__TEST__(GetBlockSize((vsa_ty*)((char*)block3 - WORD_SIZE)), ==, 16);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 0?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 0);

    VSAFree(block1);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 24?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 24);
    VSAFree(block2);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 48?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 48);
   
    free(pool);
    return 0;
}

int TEST_2()
{
    vsa_ty *head = NULL, *block1 = NULL, *block2 = NULL, *block3 = NULL;
    void *pool = malloc (85);
    size_t size = 0;

    if(NULL == pool)
    {
        return 0;
    }

    size = 85;
    

    printf ("\n--------------------------- TEST #1 -----------------------------\n\n\n");

	printf ("\nNow testing -------- VSAInit(pool, 85) --------\n\n");
    head = (vsa_ty *)VSAInit(pool, size);
	__TEST__(head, !=, NULL);
     printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 72 ?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 72);

    printf ("\nNow testing -------- VSAAlloc(head) ?--------\n\n");	
    block1 = (vsa_ty *)VSAAlloc(head, 20);
	__TEST__(GetBlockSize((vsa_ty*)((char*)block1 - WORD_SIZE)), ==, 24);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 40?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 40);
	

    printf ("\nNow testing -------- VSAAlloc(head, 16) ?--------\n\n");	
    block2 = (vsa_ty *)VSAAlloc(head, 15);
	__TEST__(GetBlockSize((vsa_ty*)((char*)block2 - WORD_SIZE)), ==, 16);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 16?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 16);

    printf ("\nNow testing -------- VSAAlloc(head, 6) ?--------\n\n");	
    block3 = (vsa_ty *)VSAAlloc(head, 6);
	__TEST__(GetBlockSize((vsa_ty*)((char*)block3 - WORD_SIZE)), ==, 16);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 0?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 0);

    VSAFree(block1);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 24?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 24);
    VSAFree(block2);
    printf ("\nNow testing -------- VSALargestChunkAvailable(head) == 48?--------\n\n");	
	__TEST__(VSALargestChunkAvailable(head), ==, 48);
   
    free(pool);
    
    return 0;
}
int main()
{
    TEST_1();

/*
    TEST_2();
*/
    return 0;
}

static size_t GetBlockSize(vsa_ty *vsa)
{
    size_t size = 0;

    assert(vsa);

    size = *(size_t *)vsa;

    return size - (size & 0x01) - (size & 0x02);
}
#include "fsa.h"
#include <stdio.h>
#include <stdlib.h>

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)


int main()
{

    void *pool = NULL;

    void *data1 = NULL;

    void *data2 = NULL;

    void *data3 = NULL;

    void *data4 = NULL;

    fsa_ty *new_fsa = NULL;

    size_t sblock = 8, number_of_blocks = 3, suggest = 0;
    
    printf("number of blocks is %lu, size of each block is %lu bytes\n", number_of_blocks, sblock);

    suggest = FSASuggestSize(number_of_blocks, sblock);

    printf("\nTesting of FSASuggestSize:\n");
    
    TEST(suggest,47);

    printf("\n\nshould to allocate %ld bytes.\n",suggest);

    printf("\nattempt to alocate %ld bytes...\n",suggest);

    pool = malloc(suggest+1UL);
    if (NULL == pool)
    {
        printf("\n memory allocation failed\n");
        return 1; 
    }

    else
    {
       printf("\n memory allocation succeed\n");     

    }


    printf("\n\nTesting of FSAInit function in case the address is not alignment\n");

    new_fsa = FSAInit ((char *)pool + 1UL ,suggest, sblock);

    if (new_fsa)
    { 
        IF_SUCCESS(1); 
    }

    else
    {
        IF_SUCCESS(0);
    }

    if ((size_t)new_fsa % sizeof(size_t) == 0)
    {
        printf("Function passed test successfully\n");
    }

    else 
    {
        printf("Function failed test\n ");
    }

    printf("\n\nTesting of FSACountFree function in before FSAAlloc\n");

    TEST(FSACountFree(new_fsa),number_of_blocks);

    printf("\n\nTesting of FSAAlloc function \n");
   
    data1 = FSAAlloc(new_fsa);
    

    if (data1)
    { 
        IF_SUCCESS(1); 
    }

    else
    {
        IF_SUCCESS(0);
    }

    printf("\n\nTesting of FSACountFree function in FSAAlloc\n");

    TEST(FSACountFree(new_fsa),number_of_blocks-1);

    printf("\n\nTesting of FSAAlloc function again: \n");
   
    data2 = FSAAlloc(new_fsa);

    if (data2)
    { 
        IF_SUCCESS(1); 
    }

    else
    {
        IF_SUCCESS(0);
    }

    printf("\n\nTesting of FSACountFree function in after second time of FSAAlloc\n");

    TEST(FSACountFree(new_fsa),number_of_blocks-2);

    printf("\n\nTesting of FSAAlloc function again: \n");
   
    data3 = FSAAlloc(new_fsa);

    if (data3)
    { 
        IF_SUCCESS(1); 
    }

    else
    {
        IF_SUCCESS(0);
    }

    printf("\n\nTesting of FSACountFree function in after thrid time of FSAAlloc\n");
    TEST(FSACountFree(new_fsa),0);

    printf("\n\nTesting of FSAAlloc function again: \n");
   
    data4 = FSAAlloc(new_fsa);

    if (!data4)
    { 
        IF_SUCCESS(1); 
    }

    else
    {
        IF_SUCCESS(0);
    }

    

    (void)data1;
    (void)data2;
    (void)data3;
    (void)data4;
    free(pool);

    return 0;


}


#include "fsa.h"
#include <stdio.h>
#include <stdlib.h>

#define IF_SUCCESS(A) A == 1? printf("Function passed test successfully\n") : printf("Function failed test\n ")
#define TEST(x,y)  x == y? IF_SUCCESS(1) : IF_SUCCESS(0)

int main()
{
    size_t suggest = 0;
    void *pool = NULL;
    fsa_ty *new_fsa = NULL;
    size_t sblock = 8, number_of_blocks = 3;

    void *data = NULL;
    
    printf("number of blocks is %lu, size of each block is %lu\n", number_of_blocks, sblock);

    suggest = FSASuggestSize(number_of_blocks, sblock);

    printf("\n\nTesting of FSASuggestSize\n");
    
    TEST(suggest,40);

    printf("\n\nshould to allocate %ld bytes\n",suggest);

    printf("\nattempt to alocate %ld bytes\n",suggest);

    pool = malloc(suggest );
    if (NULL == pool)
    {
        printf("\n memory allocation failed\n");
        return 1; 
    }

    else
    {
       printf("\n memory allocation succeed\n");     

    }


    printf("\n\ntesting of FSAAlloc function\n");

    new_fsa = FSAInit (pool ,suggest, sblock);

    if (new_fsa)
    {
      
      IF_SUCCESS(1); 
    }

    else
    {

        IF_SUCCESS(0);
    } 

    printf("Testing of FSACountFree function in before FSAAlloc\n");

    TEST(FSACountFree(new_fsa),number_of_blocks);

    printf("Testing of FSAAlloc function in before\n");
   
    data = FSAAlloc(new_fsa);
    (void)data;


    /*free(pool);*/

    return 0;


}


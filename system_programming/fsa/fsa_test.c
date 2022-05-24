#include "fsa.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    size_t suggest = 0;
    void *pool = NULL;
    fsa_ty *new_fsa = NULL;

    suggest = FSASuggestSize(3, 8);

    printf("%ld",suggest);

    pool = malloc(suggest);
    if (NULL == pool)
    {

        return 1; 
    }

    new_fsa = FSAInit (pool,suggest,8);

    return 0;


}


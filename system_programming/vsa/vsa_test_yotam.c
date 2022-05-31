/******************************************
* OL124 Project VSA
*
* Author: Yotam Aharon 
* Description:  Test For VSA
* 
******************************************/

#include "vsa.h"
#include <stdio.h> /*printf*/
#include <stdlib.h> /*malloc, free*/

#define VSA_SIZE 16
#define META_SIZE 8

#define RESET   "\033[0m"        /* Reset colour */
#define RED     "\033[31m"       /* Red */
#define GREEN   "\033[32m"      /* Green */
#define White   "\033[37m"	    /* White */

#define CHECKEQ(function, val, variable, input) val == variable ? \
printf(GREEN "%s worked succesfully for %s\n",function, input) : \
printf(RED "%s failed  for %s\n",function, input)



int main()
{

	vsa_ty *vsa;
    void *pool = NULL;

	void *block1 = NULL;
	void *block2 = NULL;
	void *block3 = NULL;

	short  info_1 = 1;

	size_t full_check = 152 - VSA_SIZE - META_SIZE;

	pool = malloc(156+4);
	pool = (char *)pool + 4;
    if (pool == NULL)
	{
		exit(1);
	}
    
    vsa = VSAInit(pool, 156);
	CHECKEQ("VSAInit",full_check,VSALargestChunkAvailable(vsa)," after init with 156 (align of 4)");

    block1 = VSAAlloc(vsa, (full_check - META_SIZE));
	*(short *)block1 = info_1;
	CHECKEQ("VSAAlloc", 0, VSALargestChunkAvailable(vsa),"  alloc with 120");

	block2 = VSAAlloc(vsa, 60);
	CHECKEQ("VSAAlloc",NULL,block2," too large alloc return with NULL");

    VSAFree(block1);	
	block2 = VSAAlloc(vsa, 60);
	printf("free space: %lu\n",VSALargestChunkAvailable(vsa));
	CHECKEQ("VSAFree",(full_check-64-META_SIZE),VSALargestChunkAvailable(vsa)," space now after free there is place for another alloc");

	block3 = VSAAlloc(vsa, 24);
	printf("free space: %lu\n",VSALargestChunkAvailable(vsa));
	CHECKEQ("VSAAlloc",(full_check-64-(2 * META_SIZE)-24) ,VSALargestChunkAvailable(vsa),"free place left after 2 alloc");
	*(short *)block3 = info_1;

	pool = (char *)pool - 4;
	free(pool);
	pool = NULL;
    printf(RESET);
	
    return 0;
}


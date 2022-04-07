/******************************************************************************
*Author: Amit Regev
*Reviewer: 
*Description: implemention of memset()
*Infinity Labs OL124	
****************************************************************************/



#include<stdio.h>


void Memset(void *dest, void *src, size_t n)
{
	char *d = dest;
    char *s = src;
	size_t i = 0;
	size_t len_word = sizeof(size_t); 
	
		
	for (;(size_t)(s+i)%len_word && i < n; ++i)

		*(d + i) = *(s + i);
	
	for (;(size_t)(s + i) % len_word == 0 && (n - i) >= len_word; i += len_word)  

		*(size_t *)(d + i) = *(size_t *)(s + i);
		
	for (;(((size_t)(s + i) % len_word == 0) && (n - i) < len_word);++i)
	
		*(d + i) = *(s + i);

} 
/*	
1. first loop --> enter only when unalign
	
	


*/	

/*
2 second loop - enter only when align and copy the all word. 		
*/

/*
3 third loop - enter only when align and a tail left. 		
*/


int main()
{ 
	int arr1[5] = {1,2,3,4,5};
	int arr2[5];
	int n = 20;
	int i = 0;
	
	printf("size of int is %ld\n", sizeof(int));

    Memcpy(arr2,arr1,n);
    
    for (i = 0; i < 5; i++)
		printf("%d ", *(arr2+i));
    	
	return 0;
}
   
   
    

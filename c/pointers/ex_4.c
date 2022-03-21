#include <stdio.h>

void swap1(size_t *x,size_t *b);
void swap2(size_t **x,size_t **b);

int main()
{
    size_t a=3;
    size_t b=5;
    size_t *c = &a;
    size_t *d = &b; 
    
    printf("before: a = %lu, b = %lu\n",a,b);
    swap1(&a,&b);
    printf("after swap1: a = %lu, b = %lu\n",a,b);
    swap2(&c,&d);
    printf("after swap2: a = %lu, b = %lu\n", a,b);
    
    return 0;
}

void swap1(size_t *x,size_t *b)
{ 
    size_t temp = *x;
    *x = *b;
    *b = temp;
}

void swap2(size_t **x,size_t **b)
{
  	swap1((size_t *)&x,(size_t *)&b);
}


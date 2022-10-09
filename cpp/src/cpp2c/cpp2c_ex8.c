#include <stdlib.h> /*malloc , free*/

typedef struct
{
    int x;
    int y; 
}B;

void Ctor(B * b)
{
    b->x=0;
    b->y=0;
}

void Setx(int inX, B* b)
{
    b->x = inX;
}

void Sety(int inY, B* b)
{
    b->y = inY;
}


B* AllocB(size_t num_of_elem)
{
    size_t i = 0;

    size_t *ptr = malloc(sizeof(B) * num_of_elem + sizeof(size_t));

    *ptr = num_of_elem;

    ptr =  ptr + 1;

    for(i = 0;i < num_of_elem;++i)
    {
        Ctor((B*)ptr + i);
    }

    return (B *)ptr;
}

void Dtor(B *b)
{
    
}


void FreeB(B* ptr)
{
    size_t size = *((size_t *)ptr - 1);
    int i = 0;

    for(i = size - 1; i >= 0; --i)
    {
        Dtor(ptr + i);
    }

    free((size_t *)ptr - 1);
}

void Foo()
{
    B array1[100];
    B *ptr=NULL;
    size_t i = 0;
    
    for(i = 0; i < 100; ++i)
    {
        Setx(0,&array1[i]);
        Sety(0,&array1[i]);
    }

    ptr = AllocB(100);

    printf("ptr.x = %d\n" ptr->x)
    FreeB(ptr);
}

int main()
{

    Foo();
    return 0;
}
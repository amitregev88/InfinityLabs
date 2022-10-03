#include <stdlib.h> /*malloc , free*/

typedef struct
{
    int x;
    int y; 
}B;


void Setx(int inX, B* const b)
{
    b->x = inX;
}

void Sety(int inY, B* const b)
{
    b->y = inY;
}

void Foo()
{
    B array1[100];

    B* array2 = malloc(sizeof(B) * 100);

    int i = 0;
    
    for(i = 0; i < 100; ++i)
    {
        Setx(0,&array1[i]);
        Sety(0,&array1[i]);
    }


    free(array2);  
}

int main ()
{

    Foo();
    return 0;
}
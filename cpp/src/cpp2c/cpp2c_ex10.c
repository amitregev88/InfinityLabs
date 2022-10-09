#include <stdlib.h> /*malloc , free*/

#include<stdio.h>
#include <stdlib.h>

static void Bla()
{
    printf("Bla()\n");
}

typedef struct B
{
    void (*bla)();
    int x;
    int y;
    
}B;

void SetX( B * const ref, int inX)
{
    ref->x = inX;
}

void SetY( B * const ref , int inY)
{
    ref->y = inY;
}

void CtorB(B * b_)
{
    b_->x = 0;
}

void Foo()
{
    B array1[10];
    size_t i = 0;
    B * array2 = NULL;


    for (i = 0; i < 10 ; i++)
    {
        CtorB(&array1[i]);
        printf("B arr1.x = %d, arr1.y = %d,\n", array1[i].x, array1[i].y);
    }

}



B Ctor_B()
{
    B b;
    b.bla = Bla;
    b.x = 0;
    b.y = 0;

    return b;
}



int main()
{
    B b = Ctor_B();

/*     printf("B b.x = %d, b.y = %d,\n", b.x, b.y);
    
    SetX(&b, 5);

    SetY(&b, 6);

    printf("B b.x = %d, b.y = %d,\n", b.x, b.y);
 */
    Bla();

    b.bla();

    return 0;
}

#include <stdio.h>/*printf*/


struct B
{
    int x;
    int y;
    
    void (*SetX)(int inX, struct B* const);
    void (*SetY)(int inY, struct B* const);

};


void Setx(int inX, struct B* const b)
{
    b->x = inX;
}

void Sety(int inY, struct B* const b)
{
    b->y = inY;
}


struct B Ctor()
{

    struct B b;

    b.SetX = Setx;
    b.SetY = Sety;

    return b;
}



int main()
{
    /*...*/

    struct B bb = Ctor();
    
    bb.SetX(5,&bb);
    bb.SetY(6,&bb);

    printf("size of struct b: %ld\n",sizeof(bb));

    printf("bb.x = %d\n", bb.x);
    printf("bb.y = %d\n", bb.y);

    return 0;
}
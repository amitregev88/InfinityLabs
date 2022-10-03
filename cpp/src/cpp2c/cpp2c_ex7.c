#include <stdlib.h> /*malloc , free*/


struct B
{
    int x;
    int y; 

};

void Setx(int inX, struct B* const b)
{
    b->x = inX;
}

void Sety(int inY, struct B* const b)
{
    b->y = inY;
}

int main ()
{
    struct B b = {0,0};

    struct B* p  = malloc(sizeof(b));
    Setx(5,&b);
    Sety(6,&b);

    Setx(5,p);
    Sety(6,p);
    free (p);

    return 0;
}
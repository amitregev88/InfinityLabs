/******************************************************************************/
/*    PROJECT:    Cpp 2 C                                                    */
/*    FILE:        cpp2c_ex12.cpp                                                */
/*    DATE:         22/09/22                                                      */
/*    NAME:         Tamar .N.                                                      */
/*    REVIEWER:                                                                  */
/*    VERSION:     1.0                                                              */
/******************************************************************************/

#include<stdio.h>
#include <stdlib.h>

typedef struct base
{
    int m_x;
    int m_y;
    
}Base;



typedef struct derive
{
    Base B;
    int z;
    
}Derive;

void CBase(Base * b, int inX, int inY)
{
    printf("Ctor Base\n");
    b->m_x = inX;
    b->m_y = inY;
}

void DBase(Base * b)
{
    (void)b;
    printf("Dtor Base\n");
}

void CDerive(Derive * d, int inX, int inY,  int inZ)
{
    printf("Ctor Derive\n");
    CBase(&(d->B),inX,inY);
    d->z = inZ;
}

void DDerive(Derive *d)
{
   DBase(&(d->B));
}

void PrintBase(Base b)
{
    printf("Base x = %d, y = %d,\n", b.m_x, b.m_y);
}

void PrintDerive(Derive d)
{
    printf("Derive z = %d \n", d.z);
}

int main()
{
    Derive d;

    CDerive(&d, 2, 4, 6);

    PrintDerive(d);

    DDerive(&d);
 
    return 0;
}
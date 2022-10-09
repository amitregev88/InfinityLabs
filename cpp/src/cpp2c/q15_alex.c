/******************************************
 *
 * Project:
 * Author: Alex milys
 * Reviewer:
 * Description:
 * Date:
 * Notes:
 ******************************************/

#include <stdlib.h>
#include <stdio.h>

typedef struct Base
{
    /*struct BaseVTable* vptr;*/
    void *vptr;
    int x, y;
} Base;

typedef struct Derived
{
    /*struct DerivedVTable* vptr;*/
    Base m_b;
    int z;
} Derived;

typedef struct BaseVTable
{
    void (*Dtor)(Base *this);
    void (*Foo)(Base *this);

} BaseVTable;

typedef struct DerivedVTable
{
    void (*Dtor)(Derived *this);
    void (*Foo)(Derived *this);
    
} DerivedVTable;

void Base_Ctor(Base *this, int inx, int iny);
void Base_Dtor(Base *this);
void Base_Foo(Base *this);

void Derived_Ctor(Derived *this,void* dvtbl, int inx, int iny, int inz);
void Derived_Dtor(Derived *this);
void Derived_Foo(Derived *this);

void* InitBaseVTable();
void* InitDerivedVTable();


int main()
{
    Base *pBase = malloc(sizeof(Derived));
    void* dvtbl=InitDerivedVTable();
    pBase->vptr=InitBaseVTable();
    
    Derived_Ctor((Derived*)pBase,dvtbl, 5, 6, 7);
    
    ((DerivedVTable*)((Derived*)pBase)->m_b.vptr)->Foo((Derived*)pBase);
    
    ((DerivedVTable*)((Derived*)pBase)->m_b.vptr)->Dtor((Derived*)pBase);
    
    
    /*Derived_Dtor((Derived*)pBase);*/
    
    return 0;
}

void Base_Ctor(Base *this, int inx, int iny)
{
    this->x = inx;
    this->y = iny;
    /*this->vptr = new;*/
}
void Base_Dtor(Base *this)
{
    printf("Base Dtor\n");
}
void Base_Foo(Base *this)
{
    printf("Base Foo \n");
}
void Derived_Ctor(Derived *this,void* dvtbl, int inx, int iny, int inz)
{
    Base_Ctor(&this->m_b,inx,iny);
    this->z=inz;
    this->m_b.vptr=dvtbl;
}

void Derived_Dtor(Derived *this)
{
      
    printf("Derive Dtor\n");
    Base_Dtor(&this->m_b);

}
void Derived_Foo(Derived *this)
{
    printf("Derive Foo\n");
}

void* InitBaseVTable()
{
    static BaseVTable baseVTable; 
    baseVTable.Foo=Base_Foo;
    baseVTable.Dtor=Base_Dtor;
    return (void*)&baseVTable;
}
void* InitDerivedVTable()
{
    static DerivedVTable derivedVTable; 
    derivedVTable.Foo=Derived_Foo;
    derivedVTable.Dtor=Derived_Dtor;
    return (void*)&derivedVTable;

}

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
    /*void *vptr;*/
    Base m_b;
    int z;
} Derived;

typedef struct BaseVTable
{
    void (*ptrBase_Dtor)(Base *this);
    void (*Foo)(Base *this);

} BaseVTable;

typedef struct DerivedVTable
{
    void (*ptrDerived_Dtor)(Derived *this);
    void (*Foo)(Derived *this);
    
} DerivedVTable;

void Base_Ctor(Base *this, int inx, int iny);
void Base_Dtor(Base *this);
void Base_Foo(Base *this);

void Derived_Ctor(Derived *this, int inx, int iny, int inz);
void Derived_Dtor(Derived *this);
void Derived_Foo(Derived *this);

int main()
{
    Base *pBase = malloc(sizeof(Derived));
    Derived_Ctor((Derived*)pBase, 5, 6, 7);
    
    ((DerivedVTable*)((Derived*)pBase)->m_b.vptr)->Foo((Derived*)pBase);
    
    ((DerivedVTable*)((Derived*)pBase)->m_b.vptr)->ptrDerived_Dtor((Derived*)pBase);
    
    /*((DerivedVTable*)pBase)->Foo;  */
    /*((DerivedVTable*)pBase)->ptrDerived_Dtor;*/
    /*pBase->Foo() ->*/
    
     /*pBase->vptr;*/
    
    /*Derived_Dtor((Derived*)pBase);*/
    
    return 0;
}

void Base_Ctor(Base *this, int inx, int iny)
{
    BaseVTable *new = (BaseVTable *)malloc(sizeof(BaseVTable));
    new->ptrBase_Dtor = Base_Dtor;
    new->Foo = Base_Foo;
    this->x = inx;
    this->y = iny;
    this->vptr = new;
}
void Base_Dtor(Base *this)
{
    printf("Base Dtor\n");
    free(this->vptr);
    this->vptr = 0;
}
void Base_Foo(Base *this)
{
    printf("Base Foo \n");
}
void Derived_Ctor(Derived *this, int inx, int iny, int inz)
{
    DerivedVTable* new=NULL;
    Base_Ctor(&this->m_b,inx,iny);
    new=(DerivedVTable*)malloc(sizeof(DerivedVTable));
    new->ptrDerived_Dtor=Derived_Dtor;
    new->Foo=Derived_Foo;
    this->z=inz;
    this->m_b.vptr=new;
}

void Derived_Dtor(Derived *this)
{
      
    /*free(this->m_b.vptr);*/
    /*this->m_b.vptr=0;*/
    printf("Derive Dtor\n");
    
    Base_Dtor(&this->m_b);

}
void Derived_Foo(Derived *this)
{
    printf("Derive Foo\n");
}

/*******************************************************************************/
/* Project: cpp2c                                                              */
/* Date: 08/10/2022                                                            */
/* Name: Amit Regev                                                            */ 
/* Reviewer:                                                                   */
/*******************************************************************************/

/************************includes**********************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */

/*************************PublicTransport************************************/
typedef struct PublicTransportvTable
{
    void (*Dtor) (void *);
    void (*Display) (void *);
}PublicTransportvTable;

typedef struct PublicTransport
{
    PublicTransportvTable *vtable;
    int m_license_plate;
}PublicTransport;

void vPublicTransportDtor(PublicTransport *);
void vPublicTransportDisplay_ty(PublicTransport *);
PublicTransportvTable pt_ptr_func_table = {vPublicTransportDtor, vPublicTransportDisplay_ty};

int PT_s_count = 0;

void PublicTransportCtor(PublicTransport *t_)
{
    t_->vtable = &pt_ptr_func_table;
    t_->m_license_plate = ++PT_s_count;
    printf("PublicTransport::Ctor()%d\n", t_->m_license_plate);
}

void vPublicTransportDtor(PublicTransport *t_)
{
    --PT_s_count;
    printf("PublicTransport::Dtor()%d\n", t_->m_license_plate);
}

void PublicTransportCCtor(PublicTransport *t_, const PublicTransport *other)
{
    t_->vtable = &pt_ptr_func_table;
    t_->m_license_plate = ++PT_s_count;
    printf("PublicTransport::CCtor() %d\n", t_->m_license_plate);
}

void vPublicTransportDisplay_ty(PublicTransport *t_)
{
    printf("PublicTransport::display(): %d\n", t_->m_license_plate);
}

static void PublicTransportprint_count(void)
{
    printf("s_count: %d\n", PT_s_count);
}

int PublicTransportget_ID_ty(PublicTransport *t_)
{
    return t_->m_license_plate;
}

/*********************************Minibus*************************************/
typedef struct Minibus
{
    PublicTransport pt_base;
    int m_numSeats;
} Minibus;

typedef struct
{
    PublicTransportvTable pt_table;
    void (*wash) (Minibus *, int);
} MinibusvTable;

void MinibusDtor(Minibus *);
void Minibusdisplay_ty(Minibus *);
void vWash_ty(Minibus *, int);
MinibusvTable minibus_ptr_func_table = {{MinibusDtor, Minibusdisplay_ty}, vWash_ty};

void MinibusCtor(Minibus *t_)
{
    PublicTransportCtor((PublicTransport *)t_);
    t_->pt_base.vtable = &minibus_ptr_func_table; // it's same --> *(void**)t_ = &minibus_ptr_func_table
    t_->m_numSeats = 20;
    printf("Minibus::PublicTransportCtor()\n");
}

void MinibusCCtor(Minibus *t_, const Minibus *other_)
{
    PublicTransportCCtor((PublicTransport*)t_, (PublicTransport*)other_);
    t_->pt_base.vtable = &minibus_ptr_func_table;
    t_->m_numSeats = other_->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void MinibusDtor(Minibus *t_)
{
    printf("Minibus::Dtor()\n");
    *(void **)t_ = &pt_ptr_func_table; //no longer derived class
    vPublicTransportDtor((PublicTransport *)t_);
}

void Minibusdisplay_ty(Minibus *t_)
{
    printf("Minibus::display() ID:%d num seats:%d\n", PublicTransportget_ID_ty((PublicTransport *)t_), t_->m_numSeats);
}

void vWash_ty(Minibus *t_, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, PublicTransportget_ID_ty((PublicTransport *)t_));
}

/*******************************Taxi*****************************************/
typedef PublicTransport Taxi;


void TaxiDtor(Taxi *);
void Taxidisplay_ty(Taxi *);
PublicTransportvTable taxi_ptr_func_table = {TaxiDtor, Taxidisplay_ty};

void TaxiCtor(Taxi *t_)
{
    PublicTransportCtor((PublicTransport *)t_);
    t_->vtable = &taxi_ptr_func_table;
    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(Taxi *t_, const Taxi *other_)
{
    PublicTransportCCtor((PublicTransport *)t_, (PublicTransport *)other_);
    t_->vtable = &taxi_ptr_func_table;
    printf("Taxi::CCtor()\n");
}

void TaxiDtor(Taxi *t_)
{
    printf("Taxi::Dtor()\n");
    *(void **)t_ = &pt_ptr_func_table; //no longer derived class
    vPublicTransportDtor((PublicTransport *)t_);
}

void Taxidisplay_ty(Taxi *t_)
{
    printf("Taxi::display() ID:%d\n", PublicTransportget_ID_ty((PublicTransport *)t_));
}


/****************************Special Taxi****************************************/
typedef Taxi SpecialTaxi;

void SpecialTaxiDtor(SpecialTaxi *);
void SpecialTaxidisplay_ty(SpecialTaxi *);
PublicTransportvTable special_taxi_ptr_func_table = {SpecialTaxiDtor, SpecialTaxidisplay_ty};

void SpecialTaxiCtor(SpecialTaxi *t_)
{
    TaxiCtor((Taxi *)t_);
    t_->vtable = &special_taxi_ptr_func_table;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi *t_, const SpecialTaxi *other_)
{
    TaxiCCtor((Taxi *)t_, (Taxi *)other_);
    t_->vtable = &special_taxi_ptr_func_table;
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDtor(SpecialTaxi *t_)
{
    printf("SpecialTaxi::Dtor()\n");
    *(void **)t_ = &taxi_ptr_func_table; //no longer derived class
    TaxiDtor((Taxi *)t_);
}

void SpecialTaxidisplay_ty(SpecialTaxi *t_)
{
    printf("SpecialTaxi::display() ID:%d\n", PublicTransportget_ID_ty((PublicTransport *)t_));
}
/******************************************************************************/


void print_infoPublicTransport(PublicTransport *a)
{
    a->vtable->Display(a);
}

void vPrintInfo(void)
{
    PublicTransportprint_count();
}

void vprint_infoMinibus(Minibus *m)
{
    (*((MinibusvTable **)m))->wash(m, 3);
}

PublicTransport print_infoInt(int i)
{
    Minibus ret;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    Minibusdisplay_ty(&ret);

    PublicTransport tmp;
    PublicTransportCCtor(&tmp, (PublicTransport *)&ret);
    MinibusDtor(&ret);

    return tmp;
}

void taxi_display(Taxi s)
{
    Taxidisplay_ty(&s);
}


/********************************main()***************************************/
int main(void)
{
    Minibus m;
    int i = 0;
    MinibusCtor(&m);

    vprint_infoMinibus(&m);

    PublicTransport tmp = print_infoInt(3);
    vPublicTransportDisplay_ty(&tmp);
    vPublicTransportDtor(&tmp);

    PublicTransport *array[] = {malloc(sizeof(Minibus)), malloc(sizeof(Taxi)), malloc(sizeof(Minibus))};
    MinibusCtor((Minibus *)array[0]);
    TaxiCtor((Taxi *)array[1]);
    MinibusCtor((Minibus *)array[2]);

    for (i = 0; i < 3; ++i)
    {
        array[i]->vtable->Display(array[i]);
    }

    for (i = 0; i < 3; ++i)
    {
        array[i]->vtable->Dtor(array[i]);
        free(array[i]);
    }

    Minibus minibus;
    MinibusCtor(&minibus);
    PublicTransport pt_minibus;
    PublicTransportCCtor(&pt_minibus, (const PublicTransport *)&minibus);
    MinibusDtor(&minibus);

    Taxi taxi;
    TaxiCtor(&taxi);
    PublicTransport pt_taxi;
    PublicTransportCCtor(&pt_taxi, (const PublicTransport *)&taxi);
    TaxiDtor(&taxi);

    PublicTransport public_transport;
    PublicTransportCtor(&public_transport);

    PublicTransport arr2[] = {pt_minibus, pt_taxi, public_transport};

    for (i = 0; i < 3; ++i)
    {
        vPublicTransportDisplay_ty(&arr2[i]);
    }
    print_infoPublicTransport(&arr2[0]);

    PublicTransportprint_count();
    Minibus m2;
    MinibusCtor(&m2);
    PublicTransportprint_count();

    Minibus arr3[4];
    for (i = 0; i < 4; ++i)
    {
        MinibusCtor(&arr3[i]);
    }

    Taxi *arr4 = malloc(sizeof(Taxi) * 4);
    for (i = 0; i < 4; ++i)
    {
        TaxiCtor(&arr4[i]);
    }

    for (i = 3; i >= 0; --i)
    {
        TaxiDtor(&arr4[i]);
    }
    free(arr4);

    printf("%d\n", 1 > 2 ? 1 : 2);
    printf("%d\n", 1 > 2.0 ? 1 : 2);

    SpecialTaxi special_taxi;
    SpecialTaxiCtor(&special_taxi);

    Taxi t_special_taxi;
    TaxiCCtor(&t_special_taxi, (const Taxi *)&special_taxi);
    taxi_display(t_special_taxi);
    TaxiDtor(&t_special_taxi);

    /*Dtors*/

    SpecialTaxiDtor(&special_taxi);

    for (i = 3; i >= 0; --i)
    {
        MinibusDtor(&arr3[i]);
    }

    MinibusDtor(&m2);
    for (i = 2; i >= 0; --i)
    {
        vPublicTransportDtor(&arr2[i]);
    }
    MinibusDtor(&m);

    return 0;
}

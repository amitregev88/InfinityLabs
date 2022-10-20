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
typedef struct 
{
    void (*Dtor) (void *);
    void (*Display) (void *);
}PublicTransportvTable;

typedef struct 
{
    PublicTransportvTable *vtable;
    int m_license_plate;
}PublicTransport;

void vPublicTransportDtor(PublicTransport *);
void vPublicTransportDisplay_th(PublicTransport *);
const PublicTransportvTable pt_ptr_func_table = {vPublicTransportDtor, vPublicTransportDisplay_th};

int PT_s_count = 0;

void PublicTransportCtor(PublicTransport *t_)
{
    t_->vtable = (PublicTransportvTable *)&pt_ptr_func_table;
    t_->m_license_plate = ++PT_s_count;
    printf("PublicTransport::Ctor()%d\n", t_->m_license_plate);
}

void vPublicTransportDtor(PublicTransport *t_)
{
    --PT_s_count;
    printf("PublicTransport::Dtor()%d\n", t_->m_license_plate);
}

void PublicTransportCCtor(PublicTransport *t_, const PublicTransport *other_)
{
    (void)other_;
    t_->vtable = (PublicTransportvTable *)&pt_ptr_func_table;
    t_->m_license_plate = ++PT_s_count;
    printf("PublicTransport::CCtor() %d\n", t_->m_license_plate);
}

void vPublicTransportDisplay_th(PublicTransport *t_)
{
    printf("PublicTransport::display(): %d\n", t_->m_license_plate);
}

static void PublicTransportprint_count(void)
{
    printf("s_count: %d\n", PT_s_count);
}

int PublicTransportget_ID_th(PublicTransport *t_)
{
    return t_->m_license_plate;
}

/*********************************Minibus*************************************/
typedef struct
{
    PublicTransport pt_base;
    int m_numSeats;
} Minibus;

typedef struct
{
    PublicTransportvTable pt_table;
    void (*wash) ();
} MinibusvTable;

void MinibusDtor(Minibus *);
void Minibusdisplay_th(Minibus *);
void vMinibusWash_th(Minibus *, int);
const MinibusvTable minibus_ptr_func_table = {{MinibusDtor, Minibusdisplay_th}, vMinibusWash_th};

void MinibusCtor(Minibus *t_)
{
    PublicTransportCtor((PublicTransport *)t_);
    t_->pt_base.vtable = (MinibusvTable *)&minibus_ptr_func_table; // it's same --> *(void**)t_ = &minibus_ptr_func_table
    t_->m_numSeats = 20;
    printf("Minibus::PublicTransportCtor()\n");
}

void MinibusCCtor(Minibus *t_, const Minibus *other_)
{
    PublicTransportCCtor((PublicTransport *)t_, (PublicTransport *)other_);
    t_->pt_base.vtable = (MinibusvTable *)&minibus_ptr_func_table;
    t_->m_numSeats = other_->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void MinibusDtor(Minibus *t_)
{
    printf("Minibus::Dtor()\n");
    *(void **)t_ = (PublicTransport *)&pt_ptr_func_table; //no longer derived class
    vPublicTransportDtor((PublicTransport *)t_);
}

void Minibusdisplay_th(Minibus *t_)
{
    printf("Minibus::display() ID:%d num seats:%d\n", PublicTransportget_ID_th((PublicTransport *)t_), t_->m_numSeats);
}

void vMinibusWash_th(Minibus *t_, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, PublicTransportget_ID_th((PublicTransport *)t_));
}

/*******************************Taxi*****************************************/
typedef PublicTransport Taxi;


void TaxiDtor(Taxi *);
void Taxidisplay_th(Taxi *);
const PublicTransportvTable taxi_ptr_func_table = {TaxiDtor, Taxidisplay_th};

void TaxiCtor(Taxi *t_)
{
    PublicTransportCtor((PublicTransport *)t_);
    *(void **)t_ = (PublicTransportvTable  *)&taxi_ptr_func_table;
    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(Taxi *t_, const Taxi *other_)
{
    PublicTransportCCtor((PublicTransport *)t_, (PublicTransport *)other_);
    *(void **)t_ = (PublicTransportvTable *)&taxi_ptr_func_table;
    printf("Taxi::CCtor()\n");
}

void TaxiDtor(Taxi *t_)
{
    printf("Taxi::Dtor()\n");
    *(void **)t_ = &pt_ptr_func_table; //no longer derived class
    vPublicTransportDtor((PublicTransport *)t_);
}

void Taxidisplay_th(Taxi *t_)
{
    printf("Taxi::display() ID:%d\n", PublicTransportget_ID_th((PublicTransport *)t_));
}


/****************************Special Taxi****************************************/
typedef Taxi SpecialTaxi;

void SpecialTaxiDtor(SpecialTaxi *);
void SpecialTaxidisplay_th(SpecialTaxi *);
const PublicTransportvTable special_taxi_ptr_func_table = {SpecialTaxiDtor, SpecialTaxidisplay_th};

void SpecialTaxiCtor(SpecialTaxi *t_)
{
    TaxiCtor((Taxi *)t_);
    *(void **)t_ = (PublicTransportvTable *)&special_taxi_ptr_func_table;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi *t_, const SpecialTaxi *other_)
{
    TaxiCCtor((Taxi *)t_, (Taxi *)other_);
    *(void**)t_ = (PublicTransportvTable *)&special_taxi_ptr_func_table;
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDtor(SpecialTaxi *t_)
{
    printf("SpecialTaxi::Dtor()\n");
    *(void **)t_ = (PublicTransportvTable *)&taxi_ptr_func_table; //no longer derived class
    TaxiDtor((Taxi *)t_);
}

void SpecialTaxidisplay_th(SpecialTaxi *t_)
{
    printf("SpecialTaxi::display() ID:%d\n", PublicTransportget_ID_th((PublicTransport *)t_));
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

void print_infoInt(int i, PublicTransport *ret_pt)
{
    Minibus ret;
    (void)i;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    Minibusdisplay_th(&ret);

    PublicTransportCCtor(&ret_pt, &ret);
    MinibusDtor(&ret);
}

void taxi_display(Taxi *s)
{
    Taxidisplay_th(s);
    TaxiDtor(s);
}

/********************************main()***************************************/
int main(void)
{
    Minibus m;
    PublicTransport display_temp;
    PublicTransport *array[3];
    Minibus arr2_temp1;
    Taxi arr2_temp2;
    PublicTransport arr2[3];
    Minibus m2;
    Minibus arr3[4];
    Taxi *arr4;
    SpecialTaxi special_taxi;
    Taxi taxi_display_temp;
    int i;

    MinibusCtor(&m);
    vprint_infoMinibus(&m);

    print_infoInt(3, &display_temp);
    vPublicTransportDisplay_th(&display_temp);
    vPublicTransportDtor(&display_temp);

    array[0] = malloc(sizeof(Minibus));
    MinibusCtor((Minibus *)array[0]);
    array[1] = malloc(sizeof(Taxi));
    TaxiCtor(array[1]);
    array[2] = malloc (sizeof(Minibus));
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

    MinibusCtor(&arr2_temp1);
    PublicTransportCCtor(&arr2, (const PublicTransport *)&arr2_temp1);
    MinibusDtor(&arr2_temp1);

    TaxiCtor(&arr2_temp2);
    PublicTransportCCtor(&arr2 + 1, &arr2_temp2);
    TaxiDtor(&arr2_temp2);
    
    PublicTransportCtor(arr2 + 2);

    for (i = 0; i < 3; ++i)
    {
        vPublicTransportDisplay_th(&arr2[i]);
    }
    print_infoPublicTransport(&arr2[0]);

    PublicTransportprint_count();
    MinibusCtor(&m2);
    PublicTransportprint_count();

    for (i = 0; i < 4; ++i)
    {
        MinibusCtor(&arr3[i]);
    }

    arr4 = malloc(sizeof(Taxi) * 4 + sizeof(size_t));
    *(size_t *)arr4 = 4;
    arr4 = (size_t *)arr4 + 1;

    for (i = 0; i < 4; ++i)
    {
        TaxiCtor(arr4 + i);
    }

    for (i = *( (size_t *)arr4 - 1 ) - 1; i >= 0; --i)
    {
        TaxiDtor(&arr4[i]);
    }
    free((size_t *)arr4 - 1);

    printf("%d\n", 2);
    printf("%d\n", 2);

    SpecialTaxiCtor(&special_taxi);

    TaxiCCtor(&taxi_display_temp, (const Taxi *)&special_taxi);
    taxi_display(&taxi_display_temp);

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

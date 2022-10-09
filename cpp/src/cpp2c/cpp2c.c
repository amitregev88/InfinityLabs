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
    void (*wash) (void *, int);
}PublicTransportvTable;

typedef struct PublicTransport
{
    PublicTransportvTable *vtable;
    int m_license_plate;
}PublicTransport;

void vPublicTransportDtor(PublicTransport *);
void vPublicTransportDisplay(PublicTransport *);
PublicTransportvTable pt_ptr_func_table = {vPublicTransportDtor, vPublicTransportDisplay, NULL};

static int g_s_count = 0;

void PublicTransportCtor(PublicTransport *this)
{
    this->vtable = &pt_ptr_func_table;
    this->m_license_plate = ++g_s_count;
    printf("PublicTransport::PublicTransportCtor()%d\n", this->m_license_plate);
}

void vPublicTransportDtor(PublicTransport *this)
{
    --g_s_count;
    printf("PublicTransport::Dtor()%d\n", this->m_license_plate);
}

void PublicTransportCCtor(PublicTransport *this, const PublicTransport *other)
{
    this->vtable = other->vtable;
    this->m_license_plate = ++g_s_count;
    printf("PublicTransport::CCtor() %d\n", this->m_license_plate);
}

void vPublicTransportDisplay(PublicTransport *this)
{
    printf("PublicTransport::display(): %d\n", this->m_license_plate);
}

static void PublicTransportprint_count(void)
{
    printf("s_count: %d\n", g_s_count);
}

int PublicTransportget_ID(PublicTransport *this)
{
    return this->m_license_plate;
}

PublicTransport operator_assignment(const PublicTransport *);


/*********************************Minibus*************************************/
typedef struct Minibus
{
    PublicTransport pt;
    int m_numSeats;
} Minibus;

void MinibusDtor(Minibus *);
void Minibusdisplay(Minibus *);
void vWash(Minibus *, int);
PublicTransportvTable minibus_ptr_func_table = {MinibusDtor, Minibusdisplay, vWash};

void MinibusCtor(Minibus *this)
{
    PublicTransportCtor((PublicTransport *)this);
    this->pt.vtable = &minibus_ptr_func_table;
    this->m_numSeats = 20;
    printf("Minibus::PublicTransportCtor()\n");
}

void MinibusCCtor(Minibus *this, const Minibus *other)
{
    PublicTransportCCtor((PublicTransport*)this, (PublicTransport*)other);
    this->m_numSeats = other->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void MinibusDtor(Minibus *this)
{
    printf("Minibus::Dtor()\n");
    vPublicTransportDtor((PublicTransport *)this);
}

void Minibusdisplay(Minibus *this)
{
    printf("Minibus::display() ID:%d num seats:%d\n", PublicTransportget_ID((PublicTransport *)this), this->m_numSeats);
}

void vWash(Minibus *this, int minutes)
{
    printf("Minibus::wash(%d) ID:%d\n", minutes, PublicTransportget_ID((PublicTransport *)this));
}


/*******************************Taxi*****************************************/
typedef struct Taxi
{
    PublicTransport pt;
} Taxi;

void TaxiDtor(Taxi *);
void Taxidisplay(Taxi *);
PublicTransportvTable taxi_ptr_func_table = {TaxiDtor, Taxidisplay, NULL};

void TaxiCtor(Taxi *this)
{
    PublicTransportCtor((PublicTransport *)this);
    this->pt.vtable = &taxi_ptr_func_table; 
    /**(PublicTransportvTable**)this = &taxi_ptr_func_table;*/
    printf("Taxi::PublicTransportCtor()\n");
}

void TaxiCCtor(Taxi *this, const Taxi *other)
{
    PublicTransportCCtor((PublicTransport *)this, (PublicTransport *)other);
    printf("Taxi::CCtor()\n");
}

void TaxiDtor(Taxi *this)
{
    printf("Taxi::Dtor()\n");
    vPublicTransportDtor((PublicTransport *)this);
}

void Taxidisplay(Taxi *this)
{
    printf("Taxi::display() ID:%d\n", PublicTransportget_ID((PublicTransport *)this));
}


/****************************Special Taxi****************************************/
typedef struct SpecialTaxi
{
    Taxi taxi;
} SpecialTaxi;

void SpecialTaxiDtor(SpecialTaxi*);
void SpecialTaxidisplay(SpecialTaxi*);
PublicTransportvTable special_taxi_ptr_func_table = {SpecialTaxiDtor, SpecialTaxidisplay, NULL};

void SpecialTaxiCtor(SpecialTaxi *this)
{
    TaxiCtor((Taxi *)this);
    this->taxi.pt.vtable = &special_taxi_ptr_func_table;
    /*(PublicTransportvTable**)this = &special_taxi_ptr_func_table;*/
    printf("SpecialTaxi::PublicTransportCtor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi *this, const SpecialTaxi *other)
{
    TaxiCCtor((Taxi *)this, (Taxi *)other);
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDtor(SpecialTaxi *this)
{
    printf("SpecialTaxi::Dtor()\n");
    TaxiDtor((Taxi *)this);
}

void SpecialTaxidisplay(SpecialTaxi *this)
{
    printf("SpecialTaxi::display() ID:%d\n", PublicTransportget_ID((PublicTransport *)this));
}
/******************************************************************************/


void vprint_infoPublicTransport(PublicTransport *a)
{
    vPublicTransportDisplay(a);
}

void vPrintInfo(void)
{
    PublicTransportprint_count();
}

void vprint_infoMinibus(Minibus *m)
{
    vWash(m, 3);
}

PublicTransport print_infoInt(int i)
{
    Minibus ret;
    MinibusCtor(&ret);
    printf("print_info(int i)\n");
    Minibusdisplay(&ret);

    PublicTransport tmp;
    PublicTransportCCtor(&tmp, (PublicTransport *)&ret);
    MinibusDtor(&ret);

    return tmp;
}

void taxi_display(Taxi s)
{
    Taxidisplay(&s);
}


/********************************main()***************************************/
int main(void)
{
    Minibus m;
    int i = 0;
    MinibusCtor(&m);

    vprint_infoMinibus(&m);

    PublicTransport tmp = print_infoInt(3);
    vPublicTransportDisplay(&tmp);
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
        vPublicTransportDisplay(&arr2[i]);
    }
    vprint_infoPublicTransport(&arr2[0]);

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

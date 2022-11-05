/*******************************************************************************/
/* Project: cpp2c2   v2                                                        */
/* Date: 10/10/2022                                                            */
/* Name: Amit Regev                                                            */ 
/* Reviewer:                                                                   */
/*******************************************************************************/

/************************includes**********************************************/
#include <stdio.h>  /* printf */
#include <stdlib.h> /* malloc, free */
/*************************PublicTransport************************************/

typedef struct 
{
    void *vtable;
    int m_license_plate;
}PublicTransport;

void vPublicTransportDtor(PublicTransport *);
void vPublicTransportDisplay_th(PublicTransport *);

const void *const g_pub_vt[] = {(void *)vPublicTransportDtor, (void *)vPublicTransportDisplay_th};


int PT_s_count = 0;

void PublicTransportCtor(PublicTransport *t_)
{
    t_->vtable = &g_pub_vt;
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
    t_->vtable = &g_pub_vt;
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

void vMinibusWash_th(Minibus *, int);
void MinibusDtor(Minibus *);
void Minibusdisplay_th(Minibus *);

const void *const g_min_vt[] = {(void *)MinibusDtor, (void *)Minibusdisplay_th, (void *)vMinibusWash_th};

void MinibusCtor(Minibus *t_)
{
    PublicTransportCtor((PublicTransport *)t_);
    t_->pt_base.vtable = &g_min_vt;
    t_->m_numSeats = 20;
    printf("Minibus::Ctor()\n");
}

void MinibusCCtor(Minibus *t_, const Minibus *other_)
{
    PublicTransportCCtor((PublicTransport *)t_, (PublicTransport *)other_);
    t_->pt_base.vtable = &g_min_vt;
    t_->m_numSeats = other_->m_numSeats;
    printf("Minibus::CCtor()\n");
}

void MinibusDtor(Minibus *t_)
{
    printf("Minibus::Dtor()\n");
    t_->pt_base.vtable = &g_pub_vt; //no longer derived class
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
const void *const g_taxi_vt[] = {(void *)TaxiDtor, (void *)Taxidisplay_th};

void TaxiCtor(Taxi *t_)
{
    PublicTransportCtor((PublicTransport *)t_);
    t_->vtable = g_taxi_vt;
    printf("Taxi::Ctor()\n");
}

void TaxiCCtor(Taxi *t_, const Taxi *other_)
{
    PublicTransportCCtor((PublicTransport *)t_, (PublicTransport *)other_);
    t_->vtable = &g_taxi_vt;
    printf("Taxi::CCtor()\n");
}

void TaxiDtor(Taxi *t_)
{
    printf("Taxi::Dtor()\n");
    t_->vtable = &g_pub_vt; //no longer derived class
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

const void *const g_st_vt[] = {(void *)SpecialTaxiDtor, (void *)SpecialTaxidisplay_th};

void SpecialTaxiCtor(SpecialTaxi *t_)
{
    TaxiCtor((Taxi *)t_);
    t_->vtable = &g_st_vt;
    printf("SpecialTaxi::Ctor()\n");
}

void SpecialTaxiCCtor(SpecialTaxi *t_, const SpecialTaxi *other_)
{
    TaxiCCtor((Taxi *)t_, (Taxi *)other_);
    t_->vtable = &g_st_vt;
    printf("SpecialTaxi::CCtor()\n");
}

void SpecialTaxiDtor(SpecialTaxi *t_)
{
    printf("SpecialTaxi::Dtor()\n");
    t_ ->vtable = &g_taxi_vt; //no longer derived class
    TaxiDtor((Taxi *)t_);
}

void SpecialTaxidisplay_th(SpecialTaxi *t_)
{
    printf("SpecialTaxi::display() ID:%d\n", PublicTransportget_ID_th((PublicTransport *)t_));
}

/******************************************************************************/
typedef void (*display)(PublicTransport*);

void print_infoPublicTransport(PublicTransport *a)
{
    ((display)(*((void **)(a->vtable) + 1)))(a);
}

void vPrintInfo(void)
{
    PublicTransportprint_count();
}

typedef void (*wash)(Minibus*, int);

void vprint_infoMinibus(Minibus *m)
{ 
    ((wash)(*((void **)(m->pt_base.vtable) + 2)))(m, 3);
}

void print_infoInt(int i, PublicTransport *ret_pt)
{
    Minibus ret;
    (void)i;
    MinibusCtor(&ret);
    void PublicConvoyDtor();
    printf("print_info(int i)\n");
    Minibusdisplay_th(&ret);

    PublicTransportCCtor(ret_pt, &ret);
    MinibusDtor(&ret);
}

void taxi_display(Taxi *s)
{
    Taxidisplay_th(s);
    TaxiDtor(s);
}
/************************************PublicConvoy****************************************/
typedef struct 
{
    PublicTransport base;
    PublicTransport *m_pt1;
    PublicTransport *m_pt2;
    Minibus m_m;
    Taxi m_t;
}PublicConvoy;

/* typedef void (*dtor)(void*);*/
 
void PublicConvoyDtor();
void PublicConvoydisplay_th();

const void *const g_pc_vt[] = {(void *)PublicConvoyDtor, (void *)PublicConvoydisplay_th};

void PublicConvoyCtor(PublicConvoy *t_)
{
    PublicTransportCtor((PublicTransport *) t_);
        
    t_->m_pt1 = malloc (sizeof(Minibus));
    MinibusCtor(t_->m_pt1);

    t_->m_pt2 = malloc (sizeof(Taxi));
    TaxiCtor(t_->m_pt2);

    MinibusCtor(&t_->m_m);

    TaxiCtor(&t_->m_t);
        
    t_= &g_pc_vt;   
};


void PublicConvoyCCtor(PublicConvoy *t_, const PublicConvoy *o_)
{
    PublicTransportCCtor( (PublicTransport*)t_, (const PublicTransport*)o_ );

    t_->m_pt1 = malloc(sizeof(Minibus));
    MinibusCCtor( (Minibus*)t_->m_pt1, (const Minibus*)o_->m_pt1 );

    t_->m_pt2 = malloc(sizeof(Taxi));
    TaxiCCtor(t_->m_pt2, o_->m_pt2);

    MinibusCCtor( (Minibus*)&t_->m_m, (const Minibus*)&o_->m_m );
    TaxiCCtor(&t_->m_t, &o_->m_t);

    t_ = &g_pc_vt;
}


void PublicConvoyDtor(PublicConvoy *t_)
{    
    /*((dtor)(**(void***)(t_->m_pt1)))(t_->m_pt1);*/
    MinibusDtor(t_->m_pt1);
    free(t_->m_pt1);

    /*((dtor)(**(void***)(t_->m_pt2)))(t_->m_pt2);*/
    TaxiDtor(t_->m_pt2);
    free(t_->m_pt2);

    t_ = &g_taxi_vt;
    TaxiDtor(&t_->m_t);

    t_ = &g_min_vt;
    MinibusDtor(&t_->m_m);

    vPublicTransportDtor((PublicTransport *) t_);
}



void PublicConvoydisplay_th(PublicConvoy *t_)
{
    ((display)(*(*(void***)(t_->m_pt1)+1)))(t_->m_pt1);

    ((display)(*(*(void***)(t_->m_pt2)+1)))(t_->m_pt2);

    Minibusdisplay_th(&t_->m_m);

   Taxidisplay_th(&t_->m_t);
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
    PublicConvoy *t1;
    PublicConvoy *t2;

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
        ((display)(*((void **)(array[i]->vtable) + 1)))(array[i]);
    }

    for (i = 0; i < 3; ++i)
    {
        ((display)(*((void **)(array[i]->vtable))))(array[i]);               
        free(array[i]);
    } 

    MinibusCtor(&arr2_temp1);
    PublicTransportCCtor(&arr2, (const PublicTransport *)&arr2_temp1);
    MinibusDtor(&arr2_temp1);

    TaxiCtor(&arr2_temp2);
    PublicTransportCCtor(arr2 + 1, &arr2_temp2);
    TaxiDtor(&arr2_temp2);
    PublicTransportCtor(arr2 + 2);

    for (i = 0; i < 3; ++i)
    {
     
        ((display)(*((void **)(arr2[i].vtable) + 1)))(&arr2[i]);

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

    t1 = malloc(sizeof(PublicConvoy));
    PublicConvoyCtor(t1);
    t2 = malloc(sizeof(PublicConvoy));
    PublicConvoyCCtor(t2, t1);

    ((display)(*(*(void***)(t1) + 1)))(t1);
    ((display)(*(*(void***)(t2) + 1)))(t2);
   /*  ((display)(*((void **)(arr2[i].vtable) + 1)))(&arr2[i]); */

    PublicConvoyDtor(t1);
  #ifdef kjd 
    free(t1);
    ((display)(*(*(void***)(t2) + 1)))(t2);
    PublicConvoyDtor(t2);
    free(t2);
#endif 



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





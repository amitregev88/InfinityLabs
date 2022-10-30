/*******************************************************************************/
/* Project: cpp2c2   v2                                                          */
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

const void *const g_pub_vt[] = {vPublicTransportDtor, vPublicTransportDisplay_th};


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


/********************************main()***************************************/
int main(void)
{
    PublicTransport a;

    return 0;
}

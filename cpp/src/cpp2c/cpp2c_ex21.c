/******************************************************************************/
/*	PROJECT:    C++ RC String                  							      */
/*	FILE:		cpp2c_ex21.cpp  									    	  */
/*	DATE: 		22/09/22    												  */
/*	NAME: 		Tamar .N.													  */
/*	REVIEWER:														          */
/*	VERSION: 	1.0												              */
/******************************************************************************/

#include<stdio.h>
#include "../../include/template.h"

TEMPLATE_MAX(int)
TEMPLATE_MAX(double)


int main()
{
    int a = Max_int(5,6);
    float b = Max_double(5.5,6.5);

    printf("a = %d \n", a);
    printf("b = %f\n", b);
    
    return 0;

}





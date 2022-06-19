/*************************************************************
* Author: Amit Regev
* Reviewer:
* Date: 16/6/22 
* OL124 calculator project
*     
***************************************************************/


#include <ctype.h> /* isdigit, ispunct */ 
#include "calculator.h"
#include "stack.h"



typedef double (*FuncPtr)(double, double);
static double add(double, double);
static double sub(double, double);
static double mult(double, double);
static double div(double, double);


double calculator(const char *expression);
{

    stack_ty *output_stack;

    stack_ty *operator_stack;

    output_stack = StackCreate()

    for(i = 0; i < 128; ++i)
    {
        arr[i] = ptr_def;

    }

    for(i = '0'; i < '9'; ++i)
    {
        arr[i] = GetOperand()

    }


    strtod(str, &ptr);



    LutOper['+']
    LutOper['-']
    LutOper['*']
    LutOper['/']




    
    
    



}

static double GetOperand( )


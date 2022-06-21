/*************************************************************
* Author: Amit Regev
* Reviewer:
* Date: 16/6/22 
* OL124 calculator project
***************************************************************/


#include <ctype.h> /* isdigit, ispunct */ 
#include <string.h> /* strlen */
#include "calculator.h"
#include "stack.h"




typedef void (*FuncPtr_ty)(stack_ty output_stack);

typedef struct operator
{
    int priority;
    FuncPtr_ty func;
}operator_ty;



static void add(stack_ty output_stack);
static void sub(stack_ty output_stack);
static void mult(stack_ty output_stack);
static void div(stack_ty output_stack);


typedef int (*action_ty)(stack_ty *output_stack, stack_ty *operator_stack, operator_ty LutOper[], double *operand, char *operator);



double calculator(const char *expression)
{

    stack_ty *output_stack = NULL;

    stack_ty *operator_stack = NULL;

    size_t i = 0;

    int index_act = 0;

    size_t exp_length = strlen(expression);

    operator_ty LutOper[128];

    action_ty LutAct[2] = {PushToStacks,CalcSubExp};

    double output_exp_num[50] = {0};

    double result = 0;

    char *iter_exp = NULL;

    char *iter_operator = NULL;




    LutOper['+'].priority = 1;
    LutOper['+'].func = add;

    LutOper['-'].priority = 1;
    LutOper['-'].func = sub;

 
    LutOper['*'].priority = 2;
    LutOper['*'].func = mult;

    LutOper['/'].priority = 2;
    LutOper['/'].func = div;

    output_stack = StackCreate(exp_length,sizeof(double));
    
    if (output_stack == NULL) 
    {
        return -1;
    }

    operator_stack = StackCreate(exp_length, sizeof(char));

    if (operator_stack == NULL) 
    {
        StackDestroy(output_stack);
        return -1;
    }

    output_exp_num[i] = strtod(expression, &iter_exp);
    iter_exp += 1;
    StackPush(output_stack, &output_exp_num[i]);
    i++;

    while(*iter_exp != '\0' && *iter_exp != '\n') /* checks if iter_exp is num or operator*/
    {      
        iter_operator = iter_exp;

        output_exp_num[i] = strtod(iter_exp + 2, &iter_exp);

        iter_exp = iter_exp + 1;

        
        /*lut act operator -  */
        while (!StackIsEmpty(operator_stack) && LutOper[(int)*iter_operator].priority < LutOper[(int)StackPeek(operator_stack)].priority);)
        {
            LutAct[1](output_stack,operator_stack,LutOper,NULL,NULL);  /*sub-calc*/
            StackPop(operator_stack);
            i++;
        }
           
        LutAct[0](output_stack,operator_stack,LutOper,NULL,&output_exp_num[i],iter_operator); /*push*/

        i++;  
    }


    while(!StackIsEmpty(operator_stack))
    {
        LutAct[1](output_stack,operator_stack, LutOper, NULL, NULL);
        StackPop(operator_stack);
        
    }

    result = *(double *)StackPeek(output_stack);

    StackDestroy(output_stack);
    StackDestroy(operator_stack);

    return result;
}

    static void PushToStacks(stack_ty output_stack, stack_ty operator_stack, double *operand, char *operator)
    {
        StackPush(operator_stack, operator);
        StackPush(output_stack, operand);
    }
    
    
    static void CalcSubExp(stack_ty output_stack, stack_ty operator_stack, operator_ty LutOper[], double *operand, char *operator)
    {
        while(!StackIsEmpty(operator_stack))
        {
            double res = 0;

            char operator = *(char *)StackPeek(operator_stack);
            res = LutOper[(int)operator].func(output_stack);
        }

    ????



        
        return 0;
    }


static void add(stack_ty output_stack)
{
    double *a = NULL , *b = NULL;
    
    *a = *(double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b += *a;


}

static void sub(stack_ty output_stack)
{
    double *a = NULL , *b = NULL;
    
    *a = *(double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b -= *a;

}

static void mult(stack_ty output_stack)
{
    double *a = NULL , *b = NULL;
    
    *a = *(double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b *= *a;

}

static void div(stack_ty output_stack)
{
    double *a = NULL , *b = NULL;
    
    *a = *(double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b /= *a;

}

static char *GetNextChar(char *s)
{
    while(*s = ' ' && *s != '\0' )
    {
        s += 1;
    }

    return s;
}


/*************************************************************
* Author: Amit Regev
* Reviewer:
* Date: 16/6/22 
* OL124 calculator project
***************************************************************/


#include <ctype.h> /* isdigit */ 
#include <string.h> /* strlen */
#include <ctype.h> /* isdigit */
#include <stdlib.h> /* strtod */
#include "calculator.h"
#include "stack.h"




typedef void (*FuncPtr_ty)(stack_ty *output_stack);

typedef struct operator
{
    int priority;
    FuncPtr_ty func;
}operator_ty;


typedef void (*action_ty)(stack_ty *output_stack, stack_ty *operator_stack, operator_ty LutOper[], char **p);

static void add(stack_ty *output_stack);
static void sub(stack_ty *output_stack);
static void mult(stack_ty *output_stack);
static void divide(stack_ty *output_stack);

static void PushToOutputStack(stack_ty *output_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p);
static void CalcSubExp(stack_ty *output_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p);

static char *GetNextChar(char *s);


double calculator(const char *expression)
{

    stack_ty *outputstack = NULL;

    stack_ty *operatorstack = NULL;

    size_t i = 0;

    int index_act = 0;

    size_t exp_length = strlen(expression);

    operator_ty LutOper[128];

    action_ty LutAct[2] = {&PushToOutputStack, &CalcSubExp};

    double output_exp_num[50] = {0};

    double result = 0;

    char *iter_exp = NULL;

    char *iter_operator = NULL;

    char user_exp[100];

    LutOper['+'].priority = 1;
    LutOper['+'].func = add;

    LutOper['-'].priority = 1;
    LutOper['-'].func = sub;
 
    LutOper['*'].priority = 2;
    LutOper['*'].func = mult;

    LutOper['/'].priority = 2;
    LutOper['/'].func = divide;

    outputstack = StackCreate(exp_length,sizeof(double));
    
    if (outputstack == NULL) 
    {
        return -1;
    }

    operatorstack = StackCreate(exp_length, sizeof(char));

    if (operatorstack == NULL) 
    {
        StackDestroy(outputstack);
        return -1;
    }
   
   
    strcpy(user_exp, expression);
    iter_exp = GetNextChar(user_exp);

   
    while(*iter_exp != '\0' && *iter_exp != '\n') /* checks if iter_exp is num or operator*/
    {      
       
        int index_act = !isdigit(*iter_exp);

        LutAct[index_act](outputstack, operatorstack, LutOper, &iter_exp); 
        
        iter_exp = GetNextChar(iter_exp);

    }



    while(!StackIsEmpty(operatorstack))
    {
        int index_operator = 0;
        
        index_operator = (int)*(char *)StackPeek(operatorstack);
        StackPop(operatorstack);

        LutOper[index_operator].func(outputstack);
        
    }

    result = *(double *)StackPeek(outputstack);

    StackDestroy(outputstack);
    StackDestroy(operatorstack);

    return result;
}

static void PushToOutputStack(stack_ty *output_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p)
{
    double number[10] = {0};

    number[0] = strtod(*p, p);
        
    StackPush(output_stack, &number[0]);
}  

static void CalcSubExp(stack_ty *output_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p)
{
        
    /* checks if operator_stack is not empty and the priority of given operator less than (or equal to)  operator in head of operator_stack */

    while (!StackIsEmpty(operator_stack) && LutOper[(int)**p].priority <= LutOper[(int)*(char *)StackPeek(operator_stack)].priority)
    {
        size_t index_operator = (int)*(char *)StackPeek(operator_stack);
        LutOper[index_operator].func(operator_stack);
    }
    
    StackPush(operator_stack, *p);
    ++*p;      
}


static void add(stack_ty *output_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b += *a;
}

static void sub(stack_ty *output_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b -= *a;
}

static void mult(stack_ty *output_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b *= *a;
}

static void divide(stack_ty *output_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(output_stack);

    StackPop(output_stack);

    b = (double *)StackPeek(output_stack);

    *b /= *a;
}

static char *GetNextChar(char *s)
{
    while((*s) == ' ' && (*s) != '\0')
    {
        ++s;
    }

    return s;
}


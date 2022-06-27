/*************************************************************
* Author: Amit Regev
* Reviewer: Noam Dan Hadad
* Date: 16/6/22 
* OL124 calculator project
***************************************************************/

#include <string.h> /* strlen */
#include <ctype.h> /* isdigit */
#include <stdlib.h> /* strtod */
#include "calculator.h"
#include "stack.h"


typedef void (*FuncPtr_ty)(stack_ty *operand_stack);

typedef struct operator
{
    int priority;
    FuncPtr_ty func;
}operator_ty;


typedef void (*action_ty)(stack_ty *operand_stack, stack_ty *operator_stack, operator_ty LutOper[], char **p);

static void add(stack_ty *operand_stack);
static void sub(stack_ty *operand_stack);
static void mult(stack_ty *operand_stack);
static void divide(stack_ty *operand_stack);

static void PushToOutputStack(stack_ty *operand_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p);
static void CalcSubExp(stack_ty *operand_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p);

static void OpenParanthesis(stack_ty *operand_stack, stack_ty *operator_stack, operator_ty LutOper[], char **p);
static void CloseParanthesis(stack_ty *operand_stack, stack_ty *operator_stack, operator_ty LutOper[], char **p);

static char *GetNextChar(char *s);
static int WhatParanthesIs(char *iter);

double calculator(const char *expression)
{

    stack_ty *operandstack = NULL;

    stack_ty *operatorstack = NULL;

    size_t exp_length = strlen(expression);

    operator_ty LutOper[128];

    action_ty LutAct[4] = {&PushToOutputStack, &CalcSubExp, &OpenParanthesis, &CloseParanthesis};

    double result = 0;

    char *iter_exp = NULL;

    char user_exp[100];

    LutOper['+'].priority = 3;
    LutOper['+'].func = add;

    LutOper['-'].priority = 3;
    LutOper['-'].func = sub;
 
    LutOper['*'].priority = 4;
    LutOper['*'].func = mult;

    LutOper['/'].priority = 4;
    LutOper['/'].func = divide;

    LutOper['('].priority = 1;
    LutOper['('].func = NULL;

    LutOper[')'].priority = 2;
    LutOper[')'].func = NULL;

    operandstack = StackCreate(exp_length,sizeof(double));
    
    if (operandstack == NULL) 
    {
        return -1;
    }

    operatorstack = StackCreate(exp_length, sizeof(char));

    if (operatorstack == NULL) 
    {
        StackDestroy(operandstack);
        return -1;
    }
   
    strcpy(user_exp, expression);
    iter_exp = GetNextChar(user_exp);

    while(*iter_exp != '\0' && *iter_exp != '\n') /* checks if iter_exp is num or operator*/
    {         
        int index_act = !isdigit(*iter_exp) + WhatParanthesIs(iter_exp);

        LutAct[index_act](operandstack, operatorstack, LutOper, &iter_exp); 
        
        iter_exp = GetNextChar(iter_exp);
    }

    while(!StackIsEmpty(operatorstack))
    {
        int index_operator = 0;
        
        index_operator = (int)*(char *)StackPeek(operatorstack);
        StackPop(operatorstack);

        LutOper[index_operator].func(operandstack);
        
    }

    result = *(double *)StackPeek(operandstack);

    StackDestroy(operandstack);
    StackDestroy(operatorstack);

    return result;
}

static void PushToOutputStack(stack_ty *operand_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p)
{
    double number[10] = {0};

    number[0] = strtod(*p, p);
        
    StackPush(operand_stack, &number[0]);

    operator_stack = operator_stack;
    LutOper = LutOper;

}  

static void CalcSubExp(stack_ty *operand_stack,stack_ty *operator_stack, operator_ty LutOper[], char **p)
{
        
    /* checks if operator_stack is not empty and the priority of given operator less than (or equal to)  operator in head of operator_stack */

    while (!StackIsEmpty(operator_stack) && LutOper[(int)**p].priority <= LutOper[(int)*(char *)StackPeek(operator_stack)].priority)
    {
        size_t index_operator = (int)*(char *)StackPeek(operator_stack);
        LutOper[index_operator].func(operand_stack);
        StackPop(operator_stack);
    }
    
    StackPush(operator_stack, *p);
    ++*p;      
}


static void OpenParanthesis(stack_ty *operand_stack, stack_ty *operator_stack, operator_ty LutOper[], char **p)
{
    StackPush(operator_stack, *p);
    ++*p;

    operand_stack = operand_stack;
    
    LutOper = LutOper;
}

static void CloseParanthesis(stack_ty *operand_stack, stack_ty *operator_stack, operator_ty LutOper[], char **p)
{
    int operator_peek = 0;

    operator_peek = (int)*(char *)StackPeek(operator_stack);

    while(operator_peek != '(')
    {
        LutOper[operator_peek].func(operand_stack);

        StackPop(operator_stack);

        operator_peek = (int)*(char *)StackPeek(operator_stack);
    }

    StackPop(operator_stack);
    ++*p;
}


static void add(stack_ty *operand_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(operand_stack);

    StackPop(operand_stack);

    b = (double *)StackPeek(operand_stack);

    *b += *a;
}

static void sub(stack_ty *operand_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(operand_stack);

    StackPop(operand_stack);

    b = (double *)StackPeek(operand_stack);

    *b -= *a;
}

static void mult(stack_ty *operand_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(operand_stack);

    StackPop(operand_stack);

    b = (double *)StackPeek(operand_stack);

    *b *= *a;
}

static void divide(stack_ty *operand_stack)
{
    double *a = NULL , *b = NULL;
    
    a = (double *)StackPeek(operand_stack);

    StackPop(operand_stack);

    b = (double *)StackPeek(operand_stack);

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

static int WhatParanthesIs(char *iter)
{
    while ((int)*iter == '(')
    {
        return 1;

    }


    while ((int)*iter == ')')
    {
        return 2;

    }

    return  0;
}

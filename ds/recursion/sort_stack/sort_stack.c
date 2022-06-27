/*************************************************************
* Author: Amit Regev
* Reviewer: 
* Date: 22/6/22 
* OL124 sort stack recursion
*******************************************************************/

#include <assert.h>
#include <stdio.h>
#include "stack.h"

void SortingStack(stack_ty *stack);
static void  SortedInsertionToStack(stack_ty *stack, int *num);
void PrintStackTopToBottom(stack_ty *stack);


int main(void)
{
    stack_ty *unsorted_stack = NULL;

    int num1 = 1, num2 = 2, num3 = 3, num4 = 4, num5 = 5;

    int num6 = 6, num7 = 7, num8 = 8, num9 = 9, num10 = 10;


    unsorted_stack = StackCreate(10, sizeof(int));
    if (NULL == unsorted_stack)
    {
        return 1;
    }

    StackPush(unsorted_stack, &num7);
    StackPush(unsorted_stack, &num9);
    StackPush(unsorted_stack, &num3);
    StackPush(unsorted_stack, &num10);
    StackPush(unsorted_stack, &num2);
    StackPush(unsorted_stack, &num1);
    StackPush(unsorted_stack, &num5);
    StackPush(unsorted_stack, &num8);
    StackPush(unsorted_stack, &num4);
    StackPush(unsorted_stack, &num6);

    printf("Before the sorting, following stack from top to bottom is:\n");

    PrintStackTopToBottom(unsorted_stack);

    printf("After the sorting, following stack from top to bottom is:\n");

    SortingStack(unsorted_stack);


    PrintStackTopToBottom(unsorted_stack);

    StackDestroy(unsorted_stack);

    return 0; 
}


void SortingStack(stack_ty *stack)
{
    assert(NULL != stack);

    if (StackIsEmpty(stack) == 0)
    {
        int tmp = *(int *)StackPeek(stack);
        StackPop(stack);

        SortingStack(stack);

        SortedInsertionToStack(stack, &tmp);
    }
}

static void  SortedInsertionToStack(stack_ty *stack, int *num)
{
    int tmp = 0;
    
    /*stop condition*/

    if (StackIsEmpty(stack) || *num >= *(int *)StackPeek(stack))
    {
        StackPush(stack, num);
        return;
    }

    tmp = *(int *)StackPeek(stack);
    StackPop(stack);
    SortedInsertionToStack(stack, num);
    StackPush(stack, &tmp);
}

void PrintStackTopToBottom (stack_ty *stack)
{

    if (StackIsEmpty(stack) == 0)
    {
        int tmp = *(int *)StackPeek(stack);
        
        printf("%d\n", *(int *)StackPeek(stack));

        StackPop(stack);

        PrintStackTopToBottom(stack);

        StackPush(stack, &tmp);
    }
}


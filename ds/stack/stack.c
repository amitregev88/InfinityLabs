#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include "stack.h"



struct stack
{
    void *stack;
    size_t size;
    size_t capacity;
    size_t size_of_element;
};



stack_ty *StackCreate(size_t capacity, size_t size_of_element)
{
	stack_ty *struct_stack = NULL;
	assert(capacity > 0);
	assert(size_of_element > 0);
	
	/* memory allocation for the struct of stack*/
	struct_stack = (stack_ty *) malloc (sizeof(stack_ty)); 
	if (NULL == struct_stack )
	{
		return NULL;
	}
	
	
	/* memory allocation for the stack*/
	struct_stack->stack = (void *) malloc (size_of_element * capacity); 
	if (struct_stack->stack == NULL)
	{
		/*clean up*/
		free(struct_stack);
		return NULL;
	}
	
	struct_stack->size = 0;
	struct_stack->capacity = capacity;
	struct_stack->size_of_element = size_of_element;
	
	return struct_stack;
} 


void StackDestroy(stack_ty *ptr)
{
		free(ptr->stack);
		free(ptr);
}

void StackPush(stack_ty* ptr, void *element)
{
	if (ptr == NULL)
	{
		printf("Memory allocation error\n");
	}
	
	if (ptr->size == ptr->capacity)
	{
		printf("The stack is full . unable to push element to stack\n");
	}	
	
	
	memcpy((char *)ptr->stack + ptr->size * ptr->size_of_element, element, ptr->size_of_element);
	
	++ptr->size;
	
}



void StackPop(stack_ty* ptr)
{
	if (ptr->size == 0)
	{
		return;
		
	}
	
	--ptr->size;
	
	
}


const void *StackPeek(const stack_ty* ptr)
{
	if (NULL == ptr || NULL == ptr->stack)
	{
		printf("memory allocation error\n"); 
		return NULL;
	}
	
	if (0 == ptr->size)
	{
		printf("the stack is empty\n"); 
	}
	
	return ((char *)(ptr->stack) + ((ptr->size - 1)* ptr->size_of_element));
}


int StackIsEmpty(const stack_ty *ptr)
{
	if(NULL == ptr)
	{
		return -1;
	}
	
	if(0 == ptr->size)
	{
		return 1;
	}
	
	return 0;
}

size_t StackSize(const stack_ty *ptr)
{
	if (NULL == ptr)
	{
		printf("memory allocation error\n");
	}
	
	return ptr->size;
}

size_t StackCapacity(const stack_ty *ptr)
{
	if (NULL == ptr)
	{
		printf("memory allocation error\n");
	}
	
	return ptr->capacity;
}










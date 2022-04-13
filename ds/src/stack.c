#include <stdio.h>
#include <stdlib.h>


struct stack
{
    size_t size;
    void *stack;
    size_t capacity;
    size_t size_of_element;
};


typedef struct stack stack_ty;


stack_ty *StackCreate(size_t capacity, size_t size_of_element);
void StackDestroy(stack_ty *ptr);
void StackPush(stack_ty* ptr, void *element);
void StackPop(stack_ty* ptr);




stack_ty *StackCreate(size_t capacity, size_t size_of_element)
{
	
	stack_ty *struct_stack = (stack_ty *) malloc (sizeof(stack_ty)); /* memory allocation for the struct of stack*/
	
	if (struct_stack == NULL)
	{
		printf("error of memory allocation\n");  
		return NULL;
	}
	else if (capacity == 0)
	{
		free(struct_stack);
		return NULL;
	}
	
	struct_stack->size = 0;
	struct_stack->capacity = capacity;
	struct_stack->size_of_element = size_of_element;
	struct_stack->stack = (void *) malloc (size_of_element * capacity); /* memory allocation for the stack*/
	if (struct_stack->stack == NULL)
	{
		printf("error of memory allocation\n");  
		return NULL;
	}
	
	
	return struct_stack;
} 


void StackDestroy(stack_ty *ptr)
{
	if (*ptr.stack != NULL)
	{
		free(*ptr.stack);
	}
	
	if(ptr != NULL)
	{
		free(ptr);
	}
	
}

void StackPush(stack_ty* ptr, void *element)
{
	if (ptr == NULL)
	{
		printf("Memory allocation error\n");
	}
	
	if (*ptr.size == *ptr.capacity)
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
	if (ptr == NULL)
	{	
		printf("memory allocation of stack error\n");
		return NULL;
	}
			
	ptr


}

int main()
{






}






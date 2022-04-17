#include <stdio.h>
#include <stdlib.h>
#include "../dynamic_vector.h"

#define SIZE_FACTOR 2

struct dynamic_vector
{
    void *data;
    size_t size;
    size_t capacity;
    size_t size_of_element;
};




dynamic_vector_ty *VectorCreate(size_t capacity , size_t size_of_element)
{

	
	dynamic_vector_ty *dynamic_vector = (dynamic_vector_ty *) calloc (sizeof(dynamic_vector_ty)); /* memory allocation for the struct of dynamic_vector*/
	
	if (dynamic_vector == NULL)
	{
		printf("error of memory allocation\n");  
		return NULL;
	}
	else if ((capacity == 0) || (size_of_element == 0) )
	{
		free(dynamic_vector);
		return NULL;
	}

	
	dynamic_vector->size = 0;
	dynamic_vector->capacity = capacity;
	dynamic_vector->size_of_element = size_of_element;
	dynamic_vector->data = (void *) malloc (size_of_element * capacity); /* memory allocation for the dynamic vector*/
	if (dynamic_vector->data == NULL)
	{
		printf("error of memory allocation\n");  
		return NULL;
	}
	
	
	return dynamic_vector;
} 

dynamic_vector_ty *VectorCreate(size_t capacity , size_t size_of_element)

void VectorDestroy(dynamic_vector_ty *vector)
{
    free(vector->data);
    free(vector);
}

dynamic_vector_ty *VectorReserve(dynamic_vector_ty *vector, size_t new_capacity)
{
	void *tmp = NULL;
	if (vector->size >  new_capacity)
	{
		vector->size = new_capacity;
	}

	tmp = (dynamic_vector_ty *)realloc(vector, new_capacity * sizeof(vector->size_of_element);
	
	if (NULL == tmp)
	{
			printf("error of memory allocation\n");  
			return NULL;
	}

	vector->data = tmp;
	
	return vector;
}

int VectorPushBack(dynamic_vector_ty *vector, void *element)
{
	void *tmp = NULL;
	void *tmp2 = NULL;
		
	if (NULL == vector)
	{
		printf("Memory allocation error\n");
	}

	if (vector->size == vector->capacity)
	{
		
		tmp =  (dynamic_vector_ty *)realloc(vector->data, vector->size_of_element * vector->capacity * SIZE_FACTOR);
		if	(tmp == NULL)
		{
			return 0;
		}
		
		vector->capacity *= SIZE_FACTOR;
		vector->data = tmp;
	}
	
		
		
		
/*exemple        1     &0(address)       10(elements)   4(bytes) -----> 40 byte right to the address known*/
		tmp2 = (char *)(vector->data) + ((vector->size) * vector->size_of_element) 
		
	vector->data = memcpy(tmp2, element, vector->size_of_element);
	
	++vector->size;
	return 1;
	
}


void VectorPopBack(dynamic_vector_ty *vector)
{

	void *tmp = NULL;
	
	if (vector->size == 0)
	{
		return;
		
	}
	
	if	(vector->size * 4 <=  vector->capacity)
	{
		tmp = (dynamic_vector_ty *)realloc(vector->data, vector->size_of_element * vector->capacity / SIZE_FACTOR);
	
	if	(vector->data == NULL)
	{	
			return;
	}
	
	
	vector->capacity /= SIZE_FACTOR; 
	vector->data = tmp;
			
	}
	
		--vector->size;

}


void *VectorGetAccessToElement(const dynamic_vector_ty *vector, size_t index)
{
	if(index > (vector->size) -1 )
	{
		return NULL;
	}
	
	return (char *)(vector->data) + ((index * vector->size_of_element); 

}
	
	
int VectorIsEmpty(const dynamic_vector_ty *vector)
{
	if (NULL == vector)
	{
		return 0;
	}
	
	return (0 == vector->size);

} 


size_t VectorSize(const dynamic_vector_ty *vector)
{
	if (NULL == vector)
	{
		return 0;
	}
	
	return (vector->size);

}	

size_t VectorCapacity(const dynamic_vector_ty *vector)
{
	if (NULL == vector)
	{
		return 0;
	}
	
	return (vector->capacity);

}


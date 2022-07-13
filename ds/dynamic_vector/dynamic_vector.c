#include <stdio.h>
#include <stdlib.h> /*malloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include "dynamic_vector.h"

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
	
	dynamic_vector_ty *dynamic_vector = NULL; 
	
	assert(capacity > 0);
	assert(size_of_element > 0);
	
	/* memory allocation for the struct of dynamic_vector*/
	dynamic_vector = (dynamic_vector_ty *)malloc(sizeof(dynamic_vector_ty));
	if (dynamic_vector == NULL)
	{
		return NULL;
	}

	/* memory allocation for the dynamic vector*/	
	dynamic_vector->data = (void *) malloc (size_of_element * capacity); 
	if (dynamic_vector->data == NULL)
	{
		/*clean up*/
		free(dynamic_vector);
		return NULL;
	}
	
	dynamic_vector->size = 0;
	dynamic_vector->capacity = capacity;
	dynamic_vector->size_of_element = size_of_element;
	
	return dynamic_vector;
} 


void VectorDestroy(dynamic_vector_ty *vector)
{
    free(vector->data);
    vector->data = NULL;
    
    free(vector);
}

dynamic_vector_ty *VectorReserve(dynamic_vector_ty *vector, size_t new_capacity)
{
	void *tmp = NULL;
	

	tmp = realloc(vector->data, new_capacity * (vector->size_of_element));
	if (NULL == tmp)
	{
			printf("error of memory allocation\n");  
			return NULL;
	}
	
	
	if (vector->size >=  new_capacity)
	{
		vector->size = new_capacity;
	}
	
	

	vector->data = tmp;
	vector->capacity = new_capacity;
	
	return vector;
}

int VectorPushBack(dynamic_vector_ty *vector, void *element)
{
	dynamic_vector_ty *tmp = NULL;
	
		
	if (NULL == vector)
	{
		return 1;
	}

	if (vector->size == vector->capacity)
	{
		
		tmp = VectorReserve(vector, SIZE_FACTOR * vector->capacity);
		if	(tmp == NULL)
		{
			return 1;
		}
		
		vector->capacity *= SIZE_FACTOR;
		
	}
	
		
		
		
/*exemple        1     &0(address)       10(elements)   4(bytes) -----> 40 byte right to the address known*/
		
		
	memcpy((char *)(vector->data) + ((vector->size) * vector->size_of_element), element, vector->size_of_element);
	
	++vector->size;
	return 0;
	
}


void VectorPopBack(dynamic_vector_ty *vector)
{

	dynamic_vector_ty *tmp = NULL;
	
	if (vector->size == 0)
	{
		return;
		
	}
	--vector->size;
	if	((vector->size) * 4 <=  (vector->capacity))
	
	{
		tmp = VectorReserve(vector, vector->capacity / SIZE_FACTOR);
	
		if	(NULL == tmp)
		{	
			return;
		}
	
		
		vector->capacity /= SIZE_FACTOR; 
	
			
	}
	
	

}


void *VectorGetAccessToElement(const dynamic_vector_ty *vector, size_t index)
{
	if(index > (vector->size) -1 )
	{
		return NULL;
	}
	
	return ((char *)(vector->data) + (index * vector->size_of_element)); 

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


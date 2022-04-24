#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include <string.h> /*memcpy*/



struct circ_buffer
{
    void *data;
    void *head;
    void *tail;
    size_t size;
};


typedef struct circ_buffer circ_buffer_ty;


circ_buffer_ty *BufferCreate(size_t size)
{
	
	circ_buffer_ty *circ_buffer = (circ_buffer_ty *) malloc (sizeof(circ_buffer_ty)); 
	
	if (NULL == circ_buffer)
	{
		printf("Error of memory allocation\n");  
		return NULL;
	}
	else if (0 == size)
	{
		printf("Error - size input is 0\n"); 
		free(circ_buffer);
		return NULL;
	}
	
	circ_buffer->data = (void *) malloc (size); /* memory allocation for the buffer*/
	if (NULL == circ_buffer->data)
	{
		printf("Error of memory allocation\n");  
		return NULL;
	}
	
	circ_buffer->head = data;
	
	circ_buffer->tail = data;
	
	circ_buffer->size = size;
	
	
	return circ_buffer;
} 


void BufferDestroy(circ_buffer_ty *buffer);
{
	if (NULL != buffer->data)
	{
		free(buffer->data);
	}
	
	if(NULL != buffer)
	{
		free(buffer);
	}
	
}

size_t BufferWrite(circ_buffer_ty *buffer, const void *data, size_t count)
{

	
}






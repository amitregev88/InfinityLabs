/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 04.24.22
* OL124 Circular Buffer Project
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include <string.h> /*memcpy*/
#include "../include/circ_buffer.h" 


struct circ_buffer
{
    void *data;
    void *head;
    size_t *tail;
    size_t size;
    size_t buffer_full;
};





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
		free(circ_buffer);
		return NULL;
	}
	
	circ_buffer->head = circ_buffer->data;
	
	circ_buffer->tail = circ_buffer->data;
	
	circ_buffer->size = size;
	
	return circ_buffer;
} 

void BufferDestroy(circ_buffer_ty *buffer);
{
	free(buffer->data);
	free(buffer);
}

size_t BufferWrite(circ_buffer_ty *buffer, const void *data, size_t count)
{
	size_t data_part_one;
	
		
	if (BufferFreeSpace(buffer) <= count)
	{
		count = BufferFreeSpace(buffer);
		buffer->buffer_full = 1;
	}
	
	if (buffer->head + count <= buffer->data + buffer->size)
	{ 
		memcpy(buffer->head, data, count);
		buffer->head = ((char *)buffer->head + count);
	}
	
	else
	{
		data_part_one = buffer->data + buffer->size - buffer->head;
		
		memcpy(buffer->head, data, data_part_one);
		buffer->head = buffer->data;
		
		memcpy(buffer->head, data + data_part_one , count - data_part_one)
		
	}
	
			
}


size_t BufferRead(const circ_buffer_ty *buffer, void *_data, size_t count)
{

	



}

size_t BufferFreeSpace(const circ_buffer_ty *buffer)			
{			
	return (buffer->size - buffer->head + buffer->tail);
}

int BufferIsEmpty(const circ_buffer_ty *buffer);
{	
	if (0 == buffer->offset)
	{
		return 1;
	}	
	return 0;   
}

size_t BufferSize(const circ_buffer_ty *buffer)
{
	return buffer->size;
}




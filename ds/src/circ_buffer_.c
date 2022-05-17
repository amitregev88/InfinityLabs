/*************************************************************************************
* Name: Amit Regev 
* Reviewer: 
* Date: 04.24.22
* OL124 Circular Buffer Project
*************************************************************************************/

#include <stdio.h>	/*printf*/
#include <stdlib.h>	/* malloc*/
#include <string.h> /*memcpy*/
#include <assert.h> /*assert*/
#include "circ_buffer.h" 


struct circ_buffer
{
    void *data;
    void *head;
    void *tail;
    size_t size;
    size_t buffer_full;
};


circ_buffer_ty *BufferCreate(size_t size)
{
	circ_buffer_ty *buffer = NULL;
	
	assert(size > 0);
	
	buffer = (circ_buffer_ty *)malloc(sizeof(struct circ_buffer) + size); 	
	if (NULL == buffer)
	{	  
		return NULL;
	}
	
	
	buffer->data = (char *)buffer + sizeof(struct circ_buffer);
	
	buffer->head = buffer->data;
	
	buffer->tail = buffer->data;
	
	buffer->size = size;
	
	buffer->buffer_full = 0;
	
	return buffer;
} 

void BufferDestroy(circ_buffer_ty *buffer)
{
	
	free(buffer);
}

size_t BufferWrite(circ_buffer_ty *buffer, const void *data, size_t count)
{
	size_t data_part_one;
	void *data_part_two;
	
		
	if (BufferFreeSpace(buffer) <= count)
	{
		count = BufferFreeSpace(buffer);
		buffer->buffer_full = 1;
	}
	
	if ((char *)buffer->head + count <= (char *)buffer->data + buffer->size)
	{
	 
		memcpy(buffer->head, data, count);
		buffer->head = ((char *)buffer->head + count);
	}
	
	else
	{
		data_part_one = (char *)buffer->data + buffer->size - (char *)buffer->head;
		
		memcpy(buffer->head, data, data_part_one);
		buffer->head = buffer->data;
		
		data_part_two = (char *)data + data_part_one;
		memcpy(buffer->head, data_part_two , count - data_part_one);
		buffer->head = ((char *)buffer->head + count - data_part_one);
		
	}
	return count;	
}


size_t BufferRead(circ_buffer_ty *buffer, void *_data, size_t count)
{
	if(BufferIsEmpty(buffer))
	{
		return 0;
	}
	
	if (buffer->size - BufferFreeSpace(buffer) <= count) /*checking if count is greater than size  */
	{
		count = buffer->size - BufferFreeSpace(buffer);
		if(count)
		{
			 buffer->buffer_full = 0;
		}
	}
	
	
	if ((char *)buffer->tail + count <= (char *)buffer->data + buffer->size )
	{
		memcpy(_data, buffer->tail, count);
		buffer->tail = ((char *)buffer->tail + count);
	}
	
	
	else
	{
		size_t data_part_one = (char *)buffer->data + buffer->size - (char *)buffer->tail;
		void *data_part_two;
	
		memcpy(_data, buffer->tail, data_part_one);
		buffer->tail = buffer->data;
	
		data_part_two = (char *)_data + data_part_one;
	
		memcpy(data_part_two, buffer->tail, count - data_part_one);
		buffer->tail = ((char *)buffer->tail + count - data_part_one);
	}
	
	
	return count;

}

size_t BufferFreeSpace(const circ_buffer_ty *buffer)			
{			
	if (buffer->buffer_full)
	{
		return 0;
	}
	
	if (BufferIsEmpty(buffer))
	{
		return buffer->size;
	}

	if ((size_t)buffer->head > ((size_t)buffer->head))
	{
		return (buffer->size - (size_t)buffer->head + (size_t)buffer->tail);
	{
	
	if
	{
		return (((size_t)buffer->tail) - ((size_t)buffer->head));
	}
	
	return 0;
	
}


int BufferIsEmpty(const circ_buffer_ty *buffer)
{	
	if ((char *)buffer->head == (char *)buffer->tail && (!(buffer->buffer_full))) 
	{
		return 1;
	}
	
	if (((char *)buffer->tail == (char *)buffer->data) && ((char *)buffer->head == (char *)buffer->data + buffer->size))
	{
		return 1;
	}
	
	return 0;   
}

size_t BufferSize(const circ_buffer_ty *buffer)
{
	return buffer->size;
}




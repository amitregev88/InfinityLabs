/*************************************************************************************
* OL124 Circular Buffer Project
* 
* Name: Alexander Bor 
* Reviewer: 
* Date: 24.04.2022
*   
*************************************************************************************/


#include <stdio.h>	/* */
#include <stdlib.h> /* malloc */
#include <string.h> /* memcpy */
#include "circ_buffer.h" /* API */

struct circ_buffer 
{
    void *data;
    void *tail;
    size_t bytes_to_read;
    size_t size;
};


/*************************************************************************************
* ---BufferCreate---returns the *buffer to an object <circ_buffer_ty *> type in case of success
*  or NULL in case of Failure
**************************************************************************************/
circ_buffer_ty *BufferCreate(size_t size)
{	
	circ_buffer_ty *buffer = malloc (sizeof(struct circ_buffer) + size);
	
	if (NULL == buffer)
	{
		return NULL;
	}
	
	buffer->data = (char *)buffer + sizeof(struct circ_buffer);
	buffer->size = size;
	buffer->tail = buffer->data;
	buffer->bytes_to_read = 0;
	
	return buffer;
	
}

/*************************************************************************************
* ---BufferDestroy--- releases the circ_buffer_ty *buffer and to all its allocated memory
**************************************************************************************/
void BufferDestroy(circ_buffer_ty *buffer)
{	
	free(buffer);
}

/*************************************************************************************

* ---BufferWrite--- writes element in allocated buffer, return 1 success
**************************************************************************************/
size_t BufferWrite(circ_buffer_ty *buffer, const void *_data, size_t count)
{
	size_t bytes_to_write = 0, temp = 0;
	
	/*	computing the size of free space in to write BUFFER */
	count = (BufferFreeSpace(buffer) < count)? BufferFreeSpace(buffer): count;
	
	/* tmp for return the count of written bytes */
	temp = count;
	

	/* in case I have some free space to write before the split and return by circle to beggining*/
	if ((count) &&  ((size_t)buffer->tail + buffer->bytes_to_read   < (size_t)buffer->data + buffer->size ))
	{
		/* computing how many bytes i have till the END of my array */
		size_t free_space = (size_t)buffer->data + buffer->size - (size_t)buffer->tail - buffer->bytes_to_read;
		
		/*	finds the pointer from which i start to write : */
		void *write_here = (char *)buffer->tail + buffer->bytes_to_read;
		
		/* counting the bytes i can write till the END of the buffer->data array */
		bytes_to_write = (count <= free_space)? count: free_space;
		
		/* writing to buffer->data */
		memcpy(write_here, _data, bytes_to_write);
		
		/* updating the bytes to read & bytes that left to copy*/
		buffer->bytes_to_read += bytes_to_write;
		
		/* updating the count */
		count -= bytes_to_write;
	}
	
	/* in case I need to split the writing*/
	if (count)
	{
		/*	finds the pointer from which i start to write : */
		void *write_here = (char *)buffer->tail + buffer->bytes_to_read - buffer->size;
		
		memcpy(write_here, (char *)_data + bytes_to_write, count);
		
		/* updating the buffer->bytes_to_read */
		buffer->bytes_to_read += count;
	}
	
	return temp;
}

/*************************************************************************************
* ---BufferRead--- return pointer to tail element or NULL if is empty
**************************************************************************************/
size_t BufferRead(circ_buffer_ty *buffer, void *_data, size_t count)
{
	size_t temp = 0, bytes_to_read = 0;
	
	/*checking how many bytes i can read and updating the count*/
	count = (count > buffer->bytes_to_read)? buffer->bytes_to_read: count;
	
	/* "temp" to return quantity of readen bytes */
	temp = count;
	
	/* starting to read  until end of array / end of count */
	if (count)
	{
		/*checks how many bytes to read after the buffer->tail ptr */
		size_t occup_space = ((size_t)buffer->tail + buffer->bytes_to_read > (size_t)buffer->data + buffer->size)? (size_t)buffer->data + buffer->size - (size_t)buffer->tail: buffer->bytes_to_read;
		
		
		/* */
		bytes_to_read = count > occup_space? occup_space: count;
		
		memcpy(_data, buffer->tail, bytes_to_read);
		
		/* updating my struct fields and variables in use */
		count -= bytes_to_read;
		buffer->bytes_to_read -= bytes_to_read;
		
		/* check if I need to move my buffer->tail ptr to beggining of array */
		buffer->tail = (count)? buffer->data: (char *)buffer->tail + bytes_to_read;
	}
	/* continue to read from beggining if i do need */
	if (count)
	{
		memcpy((char *)_data + bytes_to_read, buffer->data, count);
		
		buffer->tail = (char *)buffer->data + count;
		buffer->bytes_to_read -= count;
	}
	
	return temp;
}

/*************************************************************************************
* ---BufferFreeSpace--- returns how many byts are free to write in the buffer.
**************************************************************************************/
size_t BufferFreeSpace(const circ_buffer_ty *buffer)
{
	return buffer->size - buffer->bytes_to_read;
}

/*************************************************************************************
* ---BufferIsEmpty--- if the buffer is EMPTY returns 1, if not returns 0, 
**************************************************************************************/
int BufferIsEmpty(const circ_buffer_ty *buffer)
{
	if (NULL == buffer || NULL == buffer->data)
	{
		return -1;
	}
	
	if (0 == buffer->bytes_to_read)
	{
		return 1;
	}
	
	return 0;
}

/*************************************************************************************
* ---BufferSize--- returns the capacity of the buffer 
**************************************************************************************/
size_t BufferSize(const circ_buffer_ty *buffer)
{
	if (NULL == buffer || NULL == buffer->data)
	{
		return 0;
	}
	
	return buffer->size;
}
/*************************************************************************************/













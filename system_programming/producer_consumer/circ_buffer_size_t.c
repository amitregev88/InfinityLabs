/******************************************
* OL124 circ_buffer_new.c
* 
* 
*  
*
* Revision 2.0
******************************************/
#include <stddef.h>
#include <stdlib.h>
#include "circ_buffer_size_t.h"
#include <assert.h>
struct circ_buffer_sizet
{
    size_t *data;
    size_t to_read;
    size_t to_write;
    size_t size;
};


/*************************************************************************************
* ---BufferCreate---returns the *buffer to an object <circ_buffer_ty *> type in case of success
*  or NULL in case of Failure
**************************************************************************************/
circ_buffer_sizet_ty *BufferCreate(size_t size)
{
    circ_buffer_sizet_ty *buffer = NULL;
    
    assert(size);

    buffer = malloc (sizeof(circ_buffer_sizet_ty) + size);	
	if (NULL == buffer)
	{
		/* clean up */
		return NULL;
	}
	
	buffer->data = (size_t *)((char *)buffer + sizeof(circ_buffer_sizet_ty));
	buffer->size = size;
    buffer->to_read = 0;
    buffer->to_write = 0;
	
	return buffer;
}

/*************************************************************************************
* ---BufferDestroy--- releases the circ_buffer_ty *buffer and to all its allocated memory
**************************************************************************************/
void BufferDestroy(circ_buffer_sizet_ty *buffer)
{	
	assert(buffer);

	free(buffer);
}


/*************************************************************************************
* ---BufferWrite--- writes element in allocated buffer
**************************************************************************************/
void BufferWrite(circ_buffer_sizet_ty *buffer, size_t data)
{
    assert(buffer);

	buffer->data[buffer->to_write] = data;
	
    buffer->to_write = (buffer->to_write + 1) % buffer->size;
}

/*************************************************************************************
* ---BufferRead--- returns the size_t data 
**************************************************************************************/
size_t BufferRead(circ_buffer_sizet_ty *buffer)
{
    size_t data_to_return;
	assert(buffer);

    data_to_return = buffer->data[buffer->to_read];

    buffer->to_read = (buffer->to_read + 1) % buffer->size;
	
    return data_to_return;
}
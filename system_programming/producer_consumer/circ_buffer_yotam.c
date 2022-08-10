/*************************************************************
*OL124 CIRCULAR BUFFER Project
*
* Author: Yotam Aharon
* Reviewer: Alexander Bor
* Description:  implement CIRCULAR BUFFER
* 
* 
* Infinity Labs OL124
******************************************************************/

#include "circ_buffer.h"
#include <stdio.h> /* puts */
#include <stdlib.h> /* malloc, free */
#include <string.h> /* memcpy */
#include <assert.h> /*assert */

struct circ_buffer 
{
    void *data;
    void *write; /* place to write from */
    size_t offset_to_read; /* index to read from */
    size_t size;
	int is_full;
   
};

/* -----------inner functions for read and write readability------------------- */
static void OneCopyWrite(circ_buffer_ty *buffer, const void *data, size_t count);

static void TwoCopyWrite(circ_buffer_ty *buffer, const void *data, size_t count);

static void OneCopyRead( void *_data, circ_buffer_ty *buffer, size_t count);

static void TwoCopyRead( void *_data, circ_buffer_ty *buffer, size_t count);



circ_buffer_ty *BufferCreate(size_t size)
{
	circ_buffer_ty *buffer = NULL;

	buffer = malloc (sizeof(circ_buffer_ty)+ size);
	if (NULL == buffer)
	{
		return NULL;
	}

	buffer->data = (char *)buffer + sizeof(circ_buffer_ty);
		if (NULL == buffer->data)
	{	/* cleanup */
		free(buffer);
		return NULL;
	}

	buffer->write = buffer->data;
	buffer->offset_to_read = 0;
	buffer->is_full = 0;
	buffer->size = size;

	return buffer;
}

void BufferDestroy(circ_buffer_ty *buffer)
{
	assert(buffer);
	free(buffer);
}

size_t BufferWrite(circ_buffer_ty *buffer, const void *data, size_t count)
{	
	assert(buffer);

	if (BufferFreeSpace(buffer) <= count)
	{
		count = BufferFreeSpace(buffer);
		buffer->is_full = 1;
	}

	if (((char *)(buffer->write) + count) <= ((char *)(buffer->data) + buffer->size)) /* 1 copy case */	
	{
		OneCopyWrite(buffer,data, count);
	}
	else /* 2 chunks case */
	{
		TwoCopyWrite(buffer, data, count);
	}
	return count;
}

size_t BufferRead(circ_buffer_ty *buffer, void *_data, size_t count)
{
	assert(buffer);

	if ((buffer->size - BufferFreeSpace(buffer)) <= count)
	{
		count = buffer->size - BufferFreeSpace(buffer);
	}

	if (((char *)(buffer->data) + buffer->offset_to_read + count) <= ((char *)(buffer->data) + buffer->size)) /* 1 copy case */	
	{
		OneCopyRead(_data,buffer, count);
	}
	else /* 2 chunks case */
	{
		TwoCopyRead(_data, buffer, count);
	}

	if (count != 0)
	{
		buffer->is_full = 0;
	}
	return count;
}

size_t BufferFreeSpace(const circ_buffer_ty *buffer)
{
	assert(buffer);

	if (BufferIsEmpty(buffer))
	{
		return buffer->size;
	}
	
	if (buffer->is_full)
	{
		return 0;
	}
		
	if ((char *)buffer->write > ((char *)buffer->data + buffer->offset_to_read))
	{	
		size_t left_to_end = (char *)buffer->data + buffer->size - (char *)buffer->write;
		size_t left_from_start = buffer->offset_to_read;
		return (left_from_start + left_to_end);
	}

	if ((char *)buffer->write < ((char *)buffer->data + buffer->offset_to_read))
	{	
		return ((char *)buffer->data + buffer->offset_to_read - (char *)buffer->write);
	}
	
	return 0;
}


int BufferIsEmpty(const circ_buffer_ty *buffer)
{
	int not_full = 0;
	int read_eq_write = 0; 
	assert(buffer);

	not_full = (!(buffer->is_full));
	read_eq_write = ((char *)buffer->write == ((char *)buffer->data + buffer->offset_to_read));
	return (not_full && read_eq_write );
}

size_t BufferSize(const circ_buffer_ty *buffer)
{
	assert(buffer);
	return buffer->size;
}

/* -----------inner functions------------------- */
static void OneCopyWrite(circ_buffer_ty *buffer, const void *data, size_t count)
{
	memcpy(buffer->write, data, count);
	buffer->write = ((char *)buffer->write + count);
}

static void TwoCopyWrite(circ_buffer_ty *buffer, const void *data, size_t count)
{
	void *data_second_part = NULL;
	size_t first_part_size = ((char *)(buffer->data) + buffer->size) - (char *)buffer->write;
	
	memcpy(buffer->write, data, first_part_size);
	buffer->write = buffer->data;
	data_second_part = (char *)data + first_part_size;
	OneCopyWrite(buffer,data_second_part,count - first_part_size);
}

static void OneCopyRead( void *_data, circ_buffer_ty *buffer, size_t count)
{
	void *buf = (char *)buffer->data + buffer->offset_to_read;
	memcpy(_data, buf, count);
	buffer->offset_to_read +=  count;
}

static void TwoCopyRead( void *_data, circ_buffer_ty *buffer, size_t count)
{
	void *data_second_part = NULL;
	size_t first_part_size = buffer->size - buffer->offset_to_read;
	
	OneCopyRead(_data,buffer, first_part_size);
	buffer->offset_to_read = 0;
	data_second_part = (char *)_data + first_part_size;
	OneCopyRead(data_second_part,buffer,count - first_part_size);

}


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
    size_t offset;
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
		free(buffer);
		return NULL;
	}
	
	circ_buffer->head = circ_buffer->data;
	
	circ_buffer->offset = 0;
	
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
		
		if (buffer->tail == buffer->head)
		{
			if	(IsEmpty(buffer->data))
			{					1056			1032			1008						
				if (count <= (buffer->size -(buffer->head - buffer->tail sizeof(buffer->tail ))
				{
			  		memcpy(buffer->head, data, count);
			  	}
			  	else
			  	{ 
			  		memcpy(buffer->head, data, (buffer->head - buffer->tail));
			  	}
			}
			else
			{
			return 0;
			}
		}


size_t BufferRead(const circ_buffer_ty *buffer, void *_data, size_t count)
{

	



}

size_t BufferFreeSpace(const circ_buffer_ty *buffer)			
{			
	return (buffer->size - buffer->offset);
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




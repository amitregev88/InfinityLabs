/*************************************************************************************
* OL124 CIRCULAR BUFFER Project
*************************************************************************************/
#ifndef OL124_CIRCULAR_BUFFER_H
#define OL124_CIRCULAR_BUFFER_H

#include <stddef.h>
/*
struct circ_buffer 
{
    void *data;
    void *head;
    void *tail;
    size_t size;
   
};
*/
typedef struct circ_buffer circ_buffer_ty;

/*************************************************************************************
* ---BufferCreate---returns the *buffer to an object <circ_buffer_ty *> type in case of success
*  or NULL in case of Failure
**************************************************************************************/
circ_buffer_ty *BufferCreate(size_t size);

/*************************************************************************************
* ---BufferDestroy--- releases the circ_buffer_ty *buffer and to all its allocated memory
**************************************************************************************/
void BufferDestroy(circ_buffer_ty *buffer);

/*************************************************************************************

* ---BufferWrite--- writes element in allocated buffer, return count of write
**************************************************************************************/
size_t BufferWrite(circ_buffer_ty *buffer, const void *data, size_t count);

/*************************************************************************************
* ---BufferRead--- return count of read 
**************************************************************************************/
size_t BufferRead(circ_buffer_ty *buffer, void *_data, size_t count);

/*************************************************************************************
* ---BufferFreeSpace--- returns how many byts are free to write in the buffer.
**************************************************************************************/
size_t BufferFreeSpace(const circ_buffer_ty *buffer);

/*************************************************************************************
* ---BufferIsEmpty--- if the buffer is EMPTY returns 1, if not returns 0, 
**************************************************************************************/
int BufferIsEmpty(const circ_buffer_ty *buffer);

/*************************************************************************************
* ---BufferSize--- returns the capacity of the buffer 
**************************************************************************************/
size_t BufferSize(const circ_buffer_ty *buffer);

/*************************************************************************************/

#endif /*OL124_CIRCULAR_BUFFER_H*/

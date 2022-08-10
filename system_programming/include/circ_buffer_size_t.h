/******************************************
* OL124 circ_buffer_new.c
* 
* 
*  
*
* Revision 2.0
******************************************/

#ifndef __CIRC_BUFFER_SIZET_T__H__
#define __CIRC_BUFFER_SIZET_T__H__

#include <stddef.h>

typedef struct circ_buffer_sizet circ_buffer_sizet_ty;



/*************************************************************************************
* ---BufferCreate---returns the *buffer to an object <circ_buffer_ty *> type in case of success
*  or NULL in case of Failure
**************************************************************************************/
circ_buffer_sizet_ty *BufferCreate(size_t size);

/*************************************************************************************
* ---BufferDestroy--- releases the circ_buffer_ty *buffer and to all its allocated memory
**************************************************************************************/
void BufferDestroy(circ_buffer_sizet_ty *buffer);

/*************************************************************************************
* ---BufferWrite--- writes element in allocated buffer
**************************************************************************************/
void BufferWrite(circ_buffer_sizet_ty *buffer, size_t data);
/*************************************************************************************
* ---BufferRead--- returns the size_t data 
**************************************************************************************/
size_t BufferRead(circ_buffer_sizet_ty *buffer);

#endif /* __CIRC_BUFFER_SIZET_T__H__ */
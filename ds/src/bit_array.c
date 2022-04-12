#include<stdio.h>
#include "../include/bit_array.h"


int BitArrayGetVal(const bit_arr_ty *bptr, unsigned char index)
{
	bit_arr_ty num = *bptr;
	
	if (index > 63)
		return -1;
		
	num >>= index;
	
	if (num & 1) 
	{
		return 1;
	}
		
	else
	{
		return 0; 
	}
}

int BitArraySetOn(bit_arr_ty *bptr,  unsigned char index)
{
	bit_arr_ty num = *bptr;
	
	if (index > 63)
		return -1;
		
		
	if (!((num>> index)&1))
	{
	 	*bptr = ((((num>> index)| 1 ) << index) | num);
	}	
	return 0;
}


int BitArraySetOff(bit_arr_ty *bptr,  unsigned char index)
{
	bit_arr_ty num = *bptr;
	
	if (index > 63)
		return -1;
		
		
	if (((num>> index)&1))
	{
	 	*bptr = ((((num>> index) ^ 1 ) << index) & num);
	}	
	return 0;
}

int BitArraySetBit(bit_arr_ty *bptr, unsigned char index, unsigned char option)
{
	int result = 0;
	if (option > 1 || option < 0)
		return -1;
		
		switch(option)
		{
			case 0:		result = BitArraySetOff(bptr, index);
						return result;
						break;
			case 1:		result = BitArraySetOn(bptr, index);
						return result;
						break;
			default:	break;
						
		}
	
}


int BitArrayFlip(bit_arr_ty *bptr, unsigned char index)
{
	if (index > 63)
		return -1;
		
	if (((*bptr>>index)&1))
	{
	 	BitArraySetOff(bptr, index);
	}		
	else BitArraySetOn(bptr, index);

	return 0;
}

void BitArrayRotateLeft(bit_arr_ty *bptr, unsigned int steps)
{
 	bit_arr_ty tmp = *bptr >> (64 - steps);
	*bptr <<= (steps%64);
	*bptr |= tmp;
	
	
}

void BitArrayRotateRight(bit_arr_ty *bptr, unsigned int steps)
{
	 bit_arr_ty tmp = *bptr<< (64 - steps);
	
	*bptr >>= (steps%64);
	*bptr |= tmp;
}


int BitArrayCountBitsOn(const bit_arr_ty *bptr)
{

	int count = 0;
	bit_arr_ty tmp = *bptr;
	
	while(tmp)
	{
		if(tmp&1)
		{		
			++count;
			
		}
		tmp>>=1;
	}
	return count;	 
}

int BitArrayCountBitsOff(const bit_arr_ty *bptr)
{

	int count = 0;
	bit_arr_ty tmp = *bptr;
	int i = 64;
	while(i>0)
	{
		if(!(tmp&1))
		{		
			++count;
			
		}
		tmp>>=1;
	i--;
	}
	
	return count;	 
}


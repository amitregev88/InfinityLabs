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
	{
		return -1;
	}
	
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
	
	if (option > 1)
	{
		result = -1;
		return result;
	}
	
	if (index > 63)
	{
		result = -1;
		return result;
	}	
	
		switch(option)
		{
				
			case 0:		result = BitArraySetOff(bptr, index);
						break;
						
			case 1:		result = BitArraySetOn(bptr, index);
						break;
						
			default:	break;
						
		}
	
	return result;
	
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

void BitArraySetAllOn( bit_arr_ty *bptr)
{
	*bptr= 0xffffffffffffffff;

}

void BitArraySetAllOff( bit_arr_ty *bptr)
{
	*bptr= 0;

}

void BitArrayMirror(bit_arr_ty *bptr)
{
	int i = 63, j = 0;
	bit_arr_ty tmp = 0;  
	
	while  (i >= 0) 

	{
		tmp |= ((*bptr>>j)&1)<< i;
		j++;
		i--;
	}
	*bptr = tmp;
}

void BitArrayString(const bit_arr_ty *bptr, char *_dest)
{
	int i =0;
	bit_arr_ty isolator = 1;
	bit_arr_ty tmp = *bptr;
		
	_dest[64] = '\0';
	
	for(i=63; i>=0; --i)
	{
		if(tmp & isolator)
		{	_dest[i] = '1';
		}
		else
		{
			_dest[i] = '0';
		}
		
		tmp >>=1;
	}
	

}






#include<stdio.h>
#include<string.h> /* strcmp*/
#include "../include/bit_array.h"



void TestBitArrayGetVal(void);
void TestBitArraySetOn(void);
void TestBitArraySetOff(void);
void TestBitArraySetBit(void);
void TestBitArrayFlip(void);
void TestBitArrayRotateLeft(void);
void TestBitArrayRotateRight(void);
void TestBitArrayCountBitsOn(void);
void TestBitArrayCountBitsOff(void);
void TestBitArraySetAllOff(void);
void TestBitArraySetAllOn(void);
void TestBitArrayMirror(void);
void TestBitArrayString(void);

int main()
{
		
	TestBitArrayGetVal();
	TestBitArraySetBit();
	TestBitArraySetOn();
	TestBitArraySetOff();
	TestBitArrayFlip();
	TestBitArrayRotateLeft();	
	TestBitArrayRotateRight();
	TestBitArrayCountBitsOn();
	TestBitArrayCountBitsOff();
	TestBitArraySetAllOn();
	TestBitArraySetAllOff();
	TestBitArrayMirror();
	TestBitArrayString();
	
	return 0;
	
}


void TestBitArrayGetVal(void)
{
	bit_arr_ty num = 7; /* 00000111    from right to left*/
	
	int result = BitArrayGetVal(&num, 0);
	
	switch (result)
	{
		case 0: printf("test BitArrayGetVal failed on index 0\n");
				break;
		
		case 1: printf("test BitArrayGetVal succeeded on index 0\n");
				break;
				
		default: break;
	}
	
	result = BitArrayGetVal(&num, 4);
	
	switch (result)
	{
		case 0: printf("test BitArrayGetVal succeeded on index 4\n");
				break;
		
		case 1: printf("test BitArrayGetVal failed on index 4\n");
				break;
				
		default: break;
	}
	result = BitArrayGetVal(&num, 64);
	
	
		switch (result)
		{
		case -1: printf("test BitArrayGetVal succeeded on index out of range\n");
				break;
		
		case 0: printf("test BitArrayGetVal failed on index out of range\n");
				break;
				
		case 1: printf("test BitArrayGetVal failed on index out of range\n");
				break;
		}
}
		
	 




void TestBitArraySetOn(void)
{
	bit_arr_ty num = 59; /*00111011*/
	bit_arr_ty num2 = 59;  
	int result = 0; 

	BitArraySetOn(&num, 0);
	
	if 	(num == num2) /* checking case of bit already on*/
	
		printf("test BitArraySetOn succeeded on index 0 , num %ld\n", num);
	else
	
		printf("test BitArraySetOn failed on index 0\n, num %ld", num);
		
	BitArraySetOn(&num, 2);
	
	if 	(num == 63) 
	
		printf("test BitArraySetOn succeeded on index out of range, num %ld\n", num);
	else
	
		printf("test BitArraySetOn failed on index out of range, num %ld\n", num);
	
	result = BitArraySetOn(&num, 64);
	
	if 	(result  == -1) 
	
		printf("test BitArraySetOn succeeded on index out of range, res %d num %ld\n",result , num);
	else
	
		printf("test BitArraySetOn failed on index out of range, num %ld\n", num);
	
}

void TestBitArraySetOff(void)
{
	
	bit_arr_ty num = 59; /*00111011*/
	bit_arr_ty num2 = 59;  
	int result = 0; 
	
	
	BitArraySetOff(&num, 2);
	
	
	if 	(num == num2) /* checking case of bit already off*/
	
		printf("test BitArraySetOff succeeded on index 2 , num %ld\n", num);
	else
	
		printf("test  BitArraySetOff failed on index 2\n, num %ld", num);
		
	BitArraySetOff(&num, 0);
	
	if 	(num == 58) 
	
		printf("test BitArraySetOff succeeded on index 0, num %ld\n", num);
	else
	
		printf("test BitArraySetOff failed on index 0 , num %ld\n", num);
	
	result = BitArraySetOff(&num, 64);
	
	if 	(result  == -1) 
	
		printf("test BitArraySetOff succeeded on index out of range, res %d num %ld\n",result , num);
	else
	
		printf("test BitArraySetOff failed on index out of range, num %ld\n", num);
	
}



void TestBitArraySetBit(void)
{
	int result = 0;
	bit_arr_ty num = 59; /*111011*/
	

	result = BitArraySetBit(&num,2,3); /*checking wrong option*/
	
	if (result == -1 )
	{
		printf("test BitArraySetBit sucessed - worng option value\n");
	}
	else
	{	
		printf("test BitArraySetBit failed - worng option value\n");
	}
	num = 59;
	result=BitArraySetBit(&num,2,0);
	
	if (result == 0 )
	{
		printf("test BitArraySetBit sucessed - set bit off\n");
	}
	else
	{	
		printf("test BitArraySetBit failed - worng index value\n");
	}
	
	num = 59;
	result=BitArraySetBit(&num,2,1);
	
	if (result == 0 )
	{
		printf("test BitArraySetBit sucessed - set bit on\n");
	}
	else
	{	
		printf("test BitArraySetBit failed - worng index value\n");
	}
	
}


void TestBitArrayFlip(void)
{
	bit_arr_ty num = 59; /*111011*/
	int result = BitArrayFlip(&num, 64);
	
	if 	(result  == -1) 
	{	
		printf("test BitArrayFlip succeeded on index out of range, res %d num %ld\n",result, num);
	}
	else
	{
		printf("test BitArrayFlip failed on index out of range, num %ld\n", num);
	}
		
	result = BitArrayFlip(&num, 0); /* checking flip from 1 to 0 */
	
	if 	(num == 58) 
	{
		printf("test BitArrayFlip succeeded on index 0 : fliped res %d num %ld\n",result, num);
	}
	else
	{	
		printf("test BitArrayFlip failed on index 0 not fliped, num %ld\n", num);
	}	
		result = BitArrayFlip(&num, 0); /* checking flip from 0 to 1 */
	
	if 	(num == 59) 
	{
		printf("test BitArrayFlip succeeded on index 0 : fliped res %d num %ld\n",result, num);
	}
	else
	{
		printf("test BitArrayFlip failed on index 0 not fliped, num %ld\n", num);
	}

}

void TestBitArrayRotateLeft(void)
{
	bit_arr_ty num = 59; /*111011*/
	
	BitArrayRotateLeft(&num, 128);
	
	if 	(num == 59) 
	{
		printf("test BitArrayRotateLeft succeeded on 2 cycles left : num %ld\n", num);
	}
	else
	{
		printf("test BitArrayRotateLeft failed on on 2 cycles left : num %ld\n", num);
	}
		
		num = 59;
		BitArrayRotateLeft(&num, 65);

	
	if 	(num == 118) 
	{
		printf("test BitArrayRotateLeft succeeded on on 1 step left: num %ld\n", num);
	}
	else
	{
		printf("test BitArrayRotateLeft failed on 1 step left: num %ld\n", num);
	}
	
}

void TestBitArrayRotateRight(void)
{
	bit_arr_ty num = 59; /*111011*/
	
	BitArrayRotateRight(&num, 128);
	
	if 	(num == 59) 
	{
		printf("test BitArrayRotateRight succeeded on 2 cycles right: num %ld\n", num);
	}
	else
	{
		printf("test BitArrayRotateRight failed on on 2 cycles right: num %ld\n", num);
	}
		
		num = 59;
		BitArrayRotateRight(&num, 1);

	
	if 	(num == 0x800000000000001D) 
	
		printf("test BitArrayRotateRight succeeded on 1 step right : num %ld\n", num);
	else
	
		printf("test BitArrayRotateRight failed on on 1 step right : num %ld\n", num);
	
}
	
void TestBitArrayCountBitsOn(void)
{
	bit_arr_ty num = 59; /*111011*/

	
	if( BitArrayCountBitsOn(&num) == 5)
	{
		printf("test BitArrayCountBitsOn succeed\n");
	}
	else
	{
		printf("test BitArrayCountBitsOn failed ");
	}	
}

void TestBitArrayCountBitsOff(void)
{
	bit_arr_ty num = 59; /*111011*/

	
	if( BitArrayCountBitsOff(&num) == 59)
	{
		printf("test BitArrayCountBitsOff succeed \n");
	}
	else
	{
		printf("test BitArrayCountBitsOff failed ");
	}	
}


void TestBitArraySetAllOn(void)
{
	bit_arr_ty num = 59; /*111011*/
	
	
	BitArraySetAllOn(&num);
	if( num == 0xFFFFFFFFFFFFFFFF)
	{
		printf("test BitArraySetAllOn succeed\n");
	}
	else
	{
		printf("test BitArraySetAllOn failed\n");
	}	
}

void TestBitArraySetAllOff(void)
{
	bit_arr_ty num = 59; /*111011*/
	BitArraySetAllOff(&num);
	
	if( num == 0)
	{
		printf("test ArraySetAllOff succeed\n");
	}
	else
	{
		printf("test ArraySetAllOff failed\n");
	}	
}


void TestBitArrayMirror(void)
{
	bit_arr_ty num = 1; 
	BitArrayMirror(&num);
	
	if( num == 0x8000000000000000)
	{
		printf("test BitArrayMirror succeed\n");
	}
	else
	{
		printf("test BitArrayMirror failed\n");
	}	
}

void TestBitArrayString(void)
{
	bit_arr_ty num = 59; /*111011*/
	char buf[64];
	BitArrayString(&num, buf);
	
	if( strcmp(buf,"0000000000000000000000000000000000000000000000000000000000111011") == 0)
	{
		printf("test BitArrayString succeeded\n");
	}
	else
	{
		printf("test BitArrayString failed\n");
	}

}




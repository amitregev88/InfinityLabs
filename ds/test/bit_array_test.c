#include<stdio.h>
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
		
	/*TestBitArrayGetVal();
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
	TestBitArrayMirror();*/
	
	TestBitArrayString();
	
	
}


void TestBitArrayGetVal(void)
{
	bit_arr_ty num = 7; /* 00000111    from right to left*/
	
	int result = BitArrayGetVal(&num, 0);
	
	switch (result)
	{
		case 0: printf("test failed on index 0\n");
				break;
		
		case 1: printf("test successed on index 0\n");
				break;
				
		default: break;
	}
	
	result = BitArrayGetVal(&num, 4);
	
	switch (result)
	{
		case 0: printf("test successed on index 4\n");
				break;
		
		case 1: printf("test failed on index 4\n");
				break;
				
		default: break;
	}
	result = BitArrayGetVal(&num, 64);
	
	
		switch (result)
		{
		case -1: printf("test successed on index out of range\n");
				break;
		
		case 0: printf("test failed on index out of range\n");
				break;
				
		case 1: printf("test failed on index out of range\n");
				break;
		}
}
		
	 




void TestBitArraySetOn(void)
{
	
	bit_arr_ty num = 59; /*00111011*/  
	int result = 0; 

		
	
	
	BitArraySetOn(&num, 0);
	
	
	
	if 	(num == num) /* checking case of bit already on*/
	
		printf("test successed on index 0 , num %ld\n", num);
	else
	
		printf("test failed on index 0\n, num %ld", num);
		
	BitArraySetOn(&num, 2);
	
	if 	(num == 63) 
	
		printf("test successed on index out of range, num %ld\n", num);
	else
	
		printf("test failed on index out of range, num %ld\n", num);
	
	result = BitArraySetOn(&num, 64);
	
	if 	(result  == -1) 
	
		printf("test successed on index out of range, res %d num %ld\n",result , num);
	else
	
		printf("test failed on index out of range, num %ld\n", num);
	
}

void TestBitArraySetOff(void)
{
	
	bit_arr_ty num = 59; /*00111011*/  
	int result = 0; 
	
	
	BitArraySetOff(&num, 2);
	
	
	if 	(num == num) /* checking case of bit already on*/
	
		printf("test successed on index 2 , num %ld\n", num);
	else
	
		printf("test failed on index 2\n, num %ld", num);
		
	BitArraySetOff(&num, 0);
	
	if 	(num == 58) 
	
		printf("test successed on index 0, num %ld\n", num);
	else
	
		printf("test failed on index 0 , num %ld\n", num);
	
	result = BitArraySetOff(&num, 64);
	
	if 	(result  == -1) 
	
		printf("test successed on index out of range, res %d num %ld\n",result , num);
	else
	
		printf("test failed on index out of range, num %ld\n", num);
	
}



void TestBitArraySetBit(void)
{
	int result = 0;
	bit_arr_ty num = 59; /*111011*/

	result = BitArraySetBit(&num,2,3); /*checking wrong option*/
	
	if (result == -1 )
	{
		printf("test setBit sucessed - worng option value\n");
	}
	else
	{	
		printf("test setBit failed - worng option value\n");
	}
	num = 59;
	result=BitArraySetBit(&num,2,0);
	
	if (result == 0 )
	{
		printf("test setBit sucessed - set bit off\n");
	}
	else
	{	
		printf("test setBit failed - worng index value\n");
	}
	
	num = 59;
	result=BitArraySetBit(&num,2,1);
	
	if (result == 0 )
	{
		printf("test setBit sucessed - set bit on\n");
	}
	else
	{	
		printf("test setBit failed - worng index value\n");
	}
	
}


void TestBitArrayFlip(void)
{
	bit_arr_ty num = 59; /*111011*/
	int result = BitArrayFlip(&num, 64);
	
	if 	(result  == -1) 
	
		printf("test successed on index out of range, res %d num %ld\n",result , num);
	else
	
		printf("test failed on index out of range, num %ld\n", num);
		
	result = BitArrayFlip(&num, 0); /* checking flip from 1 to 0 */
	
	if 	(num == 58) 
	
		printf("test successed on index 0 : fliped res %d num %ld\n",result , num);
	else
	
		printf("test failed on index 0 not fliped, num %ld\n", num);
		
		result = BitArrayFlip(&num, 0); /* checking flip from 0 to 1 */
	
	if 	(num == 59) 
	
		printf("test successed on index 0 : fliped res %d num %ld\n",result , num);
	else
	
		printf("test failed on index 0 not fliped, num %ld\n", num);

}

void TestBitArrayRotateLeft(void)
{
	bit_arr_ty num = 59; /*111011*/
	
	BitArrayRotateLeft(&num, 128);
	
	if 	(num == 59) 
	
		printf("test successed on 2 cycles : num %ld\n" , num);
	else
	
		printf("test failed on on 2 cycles : num %ld\n" , num);
		
		num = 59;
		BitArrayRotateLeft(&num, 65);

	
	if 	(num == 118) 
	
		printf("test successed on 2 cycles : num %ld\n" , num);
	else
	
		printf("test failed on on 2 cycles : num %ld\n" , num);
	
}

void TestBitArrayRotateRight(void)
{
	bit_arr_ty num = 59; /*111011*/
	
	BitArrayRotateRight(&num, 128);
	
	if 	(num == 59) 
	
		printf("test successed on 2 cycles : num %ld\n" , num);
	else
	
		printf("test failed on on 2 cycles : num %ld\n" , num);
		
		num = 59;
		BitArrayRotateRight(&num, 65);

	
	if 	(num == -9223372036854775779) 
	
		printf("test successed on 2 cycles : num %ld\n" , num);
	else
	
		printf("test failed on on 2 cycles : num %ld\n" , num);
	
}
	
void TestBitArrayCountBitsOn(void)
{
	bit_arr_ty num = 59; /*111011*/

	
	if( BitArrayCountBitsOn(&num) == 5)
	{
		printf("test successed \n");
	}
	else
	{
		printf("test failed ");
	}	
}

void TestBitArrayCountBitsOff(void)
{
	bit_arr_ty num = 59; /*111011*/

	
	if( BitArrayCountBitsOff(&num) == 59)
	{
		printf("test successed \n");
	}
	else
	{
		printf("test failed ");
	}	
}


void TestBitArraySetAllOn(void)
{
	bit_arr_ty num = 59; /*111011*/
	
	BitArraySetAllOn(&num);
	if( num == 18446744073709551615)
	{
		printf("test successed \n");
	}
	else
	{
		printf("test failed %d\n ", num);
	}	
}

void TestBitArraySetAllOff(void)
{
	bit_arr_ty num = 59; /*111011*/
	BitArraySetAllOff(&num);
	
	if( num == 0)
	{
		printf("test successed \n");
	}
	else
	{
		printf("test failed num %d \n", num);
	}	
}


void TestBitArrayMirror(void)
{
	bit_arr_ty num = 1; /*111011*/
	BitArrayMirror(&num);
	
	if( num == 9223372036854775808)
	{
		printf("test successed  num %ld \n", num);
	}
	else
	{
		printf("test failed num %ld \n", num);
	}	
}

void TestBitArrayString(void)
{
	bit_arr_ty num = 59; /*111011*/
	char buf[64];
	BitArrayString(&num, buf);
	
	if( strcmp(buf,"0000000000000000000000000000000000000000000000000000000000111011") == 0)
	{
		printf("test successed  buf %s \n", buf);
	}
	else
	{
		printf("test failed  buf %s \n", buf);
	}

}




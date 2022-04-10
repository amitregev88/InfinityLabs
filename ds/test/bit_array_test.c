#include<stdio.h>
#include<bit_array.h>

int testBitArrayGetVal();


int main()
{
	


}


void TestBitArrayGetVal(void)
{
	bit_arr_ty num = 7; /* 0000 0111    from right to left*/
	
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
	result = BitArrayGetVal(&num, 64); /*???????????????????????????*/

}

int BitArraySetOn(bit_arr_ty *bptr,  unsigned char index);

void TestBitArraySetOn(void)

	bit_arr_ty num = 546;
	unsigend char index = 4
	int i = 0;
	int tmp= 0;
	
	for (; i < 64;++i)
	{
		num[i] | 1 
	
	tmp |= ((n>>j)&1)<< i;
	
{
	int 
	lut

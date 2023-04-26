#include<stdio.h> /*printf*/


unsigned int CountSetBits(unsigned int number);
unsigned int SetBit17(unsigned int number);
unsigned int ClearBit26(unsigned int number);
unsigned int CountSetBitsNaive(unsigned int number);
unsigned int CountSetBits(unsigned int number);
unsigned int CountSetBitsHW(unsigned int number);
unsigned int CountSetBitsLUT(unsigned int number);


int main(void)
{
    unsigned int number = 85;   /*1010101*/
    unsigned int number2 = 33554433; /*10000000000000000000000001*/


    
    printf("number 85 input to function SetBit17. output: %d\n", SetBit17(number));
    
    printf("number 33554433 input to function ClearBit26. output: %d\n", ClearBit26(number2));
    
    printf("number 85 input to function CountSetBitsNaive. output: %d\n", CountSetBitsNaive(number));

    printf("number 85 input to function CountSetBits. output: %d\n", CountSetBits(number));

    printf("number 85 input to function CountSetBitsHW. output: %d\n", CountSetBitsHW(number));
    
    printf("number 85 input to function CountSetBitsLUT. output: %d\n", CountSetBitsLUT(number));
    

    return 0;
}


unsigned int SetBit17(unsigned int number)
{  
    return (number | (1 << 16));
}

unsigned int ClearBit26(unsigned int number)
{ 
    return number &= ~(1 << 25);
}


 /* the algorithm pass bit step by step and count number of bits on. time complexity time O(n)  in worst case senario*/

unsigned int CountSetBitsNaive(unsigned int number)
{
    unsigned int count = 0;
    while(number)
    {
        count += number & 1;
        number >>= 1;
    }

    return count;
}



/*The algorithm turns off one bit in each iteration until the number equals zero. It will run as the number of bits on. (time complexicity in worst case senario  O(n)*/

unsigned int CountSetBits(unsigned int number) 
{
    unsigned int count = 0;
    while (number)
    {
        number &= (number - 1);
        count++;
    }
    return count;
}

/* hamming weights algorithm time complexity  O(log n)*/
unsigned int CountSetBitsHW(unsigned int number) 
{
    
    number = (number & 0x55555555 ) + ((number >>  1)  & 0x55555555 ); 
    number = (number & 0x33333333 ) + ((number >>  2)  & 0x33333333 ); 
    number = (number & 0x0F0F0F0F ) + ((number >>  4)  & 0x0F0F0F0F ); 
    number = (number & 0x00FF00FF ) + ((number >>  8)  & 0x00FF00FF ); 
    number = (number & 0x0000FFFF ) + ((number >> 16)  & 0x0000FFFF ); 
       
   return number;

}


 /* The algorithm uses in  Lookup table. it stroe the  number of bits on for each number in range of the chunck - 8 bits 0-255  and checks the input number for each chunck - time complexity O(1) */
unsigned int CountSetBitsLUT(unsigned int number)
{
	int table[256] = {0}; /* lookup table for 8 bits - chunck */
	int i = 0;
   	unsigned int count = 0; 
	
	for (i = 0; i < 256; i++)
	{
   		table[i] = table[i/2] + (i & 1);
	}
	
   	count = table[number & 0xff] + table[(number >> 8) & 0xff] + table[(number >> 16) & 0xff] + table[(number >> 24) & 0xff];
   	
    return count;
}









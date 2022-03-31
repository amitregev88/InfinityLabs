/************************************************************
*Author: Amit Regev
*Reviewer: 
*Description:  Bitwise Operation.
*Infinity Labs: OL124	
***************************************************************/

/*calculate x*(2^y) by bit operation*/
/*
#include <stdio.h>
long Pow2(unsigned int x, unsigned int y)
{
	return x<<y;
	
}

int main()
{
	unsigned int x = 5, y = 3;
	long res;  
	
	res = Pow2(x,y);
	printf("the result is: %ld\n", res);
	
	return 0;
}
*/
/***************** the function checks if n is power of 2 (with loop)*********************/
/*
#include <stdio.h>
int nPow2(unsigned int n)
{
	unsigned int num = 1;
	while (num <= n)
	{
		if (n == num)
			return 1;
			
		num = num<<1;
	}
		
	return 0;
	
}
*/
/*** the  function checks if n is power of 2 (without loop)****/ 


/*
#include <stdio.h>
int nPow2(unsigned int n)
{
	
	if ((n&(n - 1)) == 0) /*A result of a power of 2 is represented by 1 and then zeros in a binary number and  							therefore n&(n-1) should be 0
		return 1;
	else
		return 0;
}
	
		
int main()
{
	unsigned int x = 9;
	int res;  
	
	res = nPow2(x);
	printf("result: %d\n", res);
	
	return 0;
}

*/

/*** function add 1 to given number without using arithmetic operation****/

/*
#include <stdio.h> 
/*
unsigned int Add1(unsigned int n)
{
    unsigned int place_check = 1;

    while (n & place_check) /*only odd numbers will inside to the loop */
/*    {
/*    
        n = n ^ place_check; /* flip to zero  */
/*      place_check <<= 1;  /* go for next bit */ 
/*   }
/*     n = n ^ place_check; /* flip the first one to zero */
     
     
/*
   return n;
}
/*

int main()
{
    int num = 5;

    d = Add1(num);

    printf ("%d\n", d);


return 0;
}
*/
/*******************the function prints numbers with exacly 3 bits***********************/ 

/*void Print_numbers_w_3bits(unsigned int arr[])
{
    int i = 0, counter = 0;
    unsigned int temparr[10]; 

    for(i = 0 ; i < 10 ; ++i)
    {
        counter = 0;
        temparr[i] = arr[i];

        while (temparr[i])
        {
            counter += temparr[i] & 1;
            temparr[i] >>= 1;
        }

        if(counter == 3)
            printf("%d is num with exactly 3 bit\n",arr[i]);
    }
}
/*
int main()
{
    unsigned int arr[10] = {10,11,12,13,14,15,16,17,18,19};
    
    Print_numbers_w_3bits(arr);

    return 0;
}
*/
/*
/*********************Mirror Byte By Loop**************************************/
/*
#include <stdio.h> 

 unsigned char Mirror_Byte(unsigned char n)
{
	int i = 7, j = 0, tmp = 0;  
	
	while  (i >= 0) /* unsigned char is 8 bits*/
/*
	{
		tmp |= ((n>>j)&1)<< i;
		j++;
		i--;
	}
	return tmp;
	
}
	 
int main()
{
	unsigned char number = 11;
	unsigned char mirror = 0;
	
	mirror = Mirror_Byte(number);
	
	printf("The number is %d after mirror: %d\n", number, mirror);
	return 0;
} 
/*******************************************Mirror_Byte_By_LUT*************/
/*
unsigned char ByteMirrorLut(unsigned char num)
{
    
    unsigned char lut_mirror[256] = {0};
    int i = 0;
    
    lut_mirror[0] = 0;
    lut_mirror[255] = 255;
    
    for (i = 1; i < 255; ++i)
    {      
    
           if (lut_mirror[i] == 0)
           {
               lut_mirror[i] = Mirror_Byte((unsigned char)i);
               lut_mirror[lut_mirror[i]] = i;
           }
    }
    return  lut_mirror[num];
}

int main()
{   
    
     unsigned char num = 200;  
       
     printf("The number is %u after mirror: %u\n", num, ByteMirrorLut(num));
}
            

return 0;
	
/******************the function checks if bit 2 and 6 are on***************************/	
/*
int Is2and6bitson (unsigned char n)
{
	int flag = 2;
	
	flag = ((n>>1)&1)& ((n>>5)&1);
	
	return flag;
}

int main()
{

	int num = 182;  /*182 = 10110110 binary*/
	
/*	printf("%d", Is2and6bitson(num));
	
	return 0;
}

/******************the function checks if bit 2 or 6 are on***************************/	
/*
int Is2and6bitson (unsigned char n)
{
	int flag = 2;
	
	flag = ((n>>1)&1) | ((n>>5)&1);
	
	return flag;
}

int main()
{

	int num = 180;  /*182 = 10110100 binary*/
	
/*	printf("%d", Is2and6bitson(num));
	
	return 0;
}
*/
/******************the function swap between 3nd and 5th bits*******************/
/*
int Isswap (unsigned char n)
{
	int swapn = 0;
	
	swapn = n^(((n >> 2) & 1 ^ (n >> 4) & 1)<<4 | ((n >> 2) & 1 ^ (n >> 4) & 1)<<2);
	
	return swapn;
}

int main()
{

	int num = 167;  /*167 = 10100111 binary*/
	
/*	printf("%d", Isswap(num));
	
	return 0;

}

/*********the func calculate the closest number (smaller) devided in 16 ************************/
/*
int Remainder16(unsigned int number)
{
    number >>= 4;
    return number <<= 4;
}


int main() 
{


	printf("The closest number to %d devided in 16 is %d\n", 100, Remainder16(100));

	return 0;

}

/*
/******************the function swap between 2 value of variable without using third variable***********/
/*
void swap(int &x, int &y)
{
    if (x != y)
    {
        x = x ^ y;
        y = x ^ y;
        x = x ^ y;
    }
}
/*************function counts set bits in an integer with using a loop**************

unsigned int CountSetBits(unsigned int n)
{
    unsigned int count = 0;
    while (n) {
        count += n & 1;
        n >>= 1;
    }
    return count;
}
 

/*
int main()
{
    int i = 9;
    printf("%d", CountSetBits(i));
    return 0;
}
/************function counts set bits in an integer without using a loop********/
/*

CountSetBits
{
    /* hamming weights */
    
/*    num = (num & 0x55555555 ) + ((num >>  1)  & 0x55555555 ); /*put count of each  2 bits into those  2 bits */
/*   num = (num & 0x33333333 ) + ((num >>  2)  & 0x33333333 ); /*put count of each  4 bits into those  4 bits */
/*   num = (num & 0x0F0F0F0F ) + ((num >>  4)  & 0x0F0F0F0F ); /*put count of each  8 bits into those  8 bits */
/*   num = (num & 0x00FF00FF ) + ((num >>  8)  & 0x00FF00FF ); /*put count of each 16 bits into those 16 bits */
/*    num = (num & 0x0000FFFF )  +((num >> 16)  & 0x0000FFFF ); /*put count of each 32 bits into those 32 bits */
       
 /*   return num;
}

int main()
{   
    int  num = 13;  
      
     printf("number of bits in %d is: %d\n",num, CountSetBits(num));
     
           
return 0;
}

/*******************************************************************************/

void print_float_binary(float f)
{
 unsigned int *float_int = (unsigned int )&f;
 int i;

 for (i=0; i<64; i++)
   {
    if (i==1)
      printf(" "); / Space after sign field/
    if (i==12)
      printf("\t"); / tab after exponent field/

    if ((float_int >> (63-i)) & 1)
      printf("1");
    else
      printf("0");
   }
 printf("\n");
}

a
10100111	/original num
00101001	/>>2
00000001	/&1
-----------------------------------

10100111	/original num
00001010	/>>4
00000001	/&1

b

a ^ b | ----> 1 ^ 0 = 1

10



					10100111 original
					
xor					10110111 /after xor

					00010000 / xor with original
					
					
					
0	0	0			

0	1	1

1	1	0


n^(((n >> 2) & 1 ^ (n >> 4) & 1)<<4 | ((n >> 2) & 1 ^ (n >> 4) & 1)<<2)

((n >> 2) & 1 ^ (n >> 4) & 1)



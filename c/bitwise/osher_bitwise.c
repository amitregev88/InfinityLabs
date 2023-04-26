/******************************************************************************/
/*	Project:	BITWISE API    										    	  */
/*	File:		bitwise.hpp		    										  */
/*	Date: 		26/12/2022													  */
/*	Name: 		ILRD25      												  */
/*	Reviewer:	        													  */
/*	Version: 	1.00														  */
/******************************************************************************/

#include <stdio.h> /* printf lo alino */
#include <stdlib.h> /* for size_t */

long Pow2YNMultiX(unsigned int x, unsigned int y)
{
    return x << y;
}

int IsPowOf2(unsigned int num)
{
    size_t counter = 0;
    
    while(num)
    {
        if(num & 1)
        {
            ++counter;
        }

        num = num >> 1;
    }

    if(counter == 1)
    {
        return 1;
    }

    return 0;
}

int IsPowOf2NoLoop(unsigned int num)
{
    return (num && (0 == (num & (num -1))));

}

int AddOne(unsigned int num)
{
    unsigned int mask = 1;
    unsigned int mask2 = 0;


    if((num & mask) == 0)
    {

        return num ^ mask;
    }

    while(num & mask)
    {
        mask2 ^= 1;
        mask2 <<= 1;
        mask <<= 1;
    }

        mask = mask2 ^ 1;
    
    return num ^ mask;
}

int IsThreeOnImp(unsigned int num)
{
    unsigned int counter = 0;

    while(num)
    {
        if(num & 1)
        {
            ++counter;
        }

        num >>= 1;
    }

    if(counter == 3)
    {
        return 1;
    }

    return 0;
}

void Print3On(unsigned int* nums, size_t nums_size)
{
    size_t i = 0;

    for(i = 0; i < nums_size; ++i)
    {
        if(IsThreeOnImp(nums[i]))
        {
            printf("%d\n",nums[i]);
        }
    }    
}

unsigned int ByteMirror(unsigned int num)
{
    unsigned int ret = 0;
    
    size_t j = sizeof(unsigned int) * 8 - 1;

    while(num)
    {
        ret |= (num & 1) << j;
        --j;
        num >>= 1;
    }

    return ret;
}

unsigned int ByteMirrorNoLoop(unsigned int num)
{
    num =((num & 0x55555555) << 1) | ((num & 0xAAAAAAAA) >> 1);
    num = ((num & 0x03030303) << 2) | ((num & 0xCCCCCCCC) >> 2);
    num = ((num & 0x0F0F0F0F) << 4) | ((num & 0xF0F0F0F0) >> 4);
    num = ((num & 0x00FF00FF) << 8) | ((num & 0xFF00FF00) >> 8);
    num = ((num & 0x0000FFFF) << 16) | ((num & 0xFFFF0000) >> 16);

    return num;
}

unsigned int Is2N6On(unsigned int num)
{
    unsigned int mask = 34;

    if((num | mask) == num)
    {
        return 1;
    }

    return 0;
}

unsigned int Is2Or6On(unsigned int num)
{
    return (num & 2) || (num & 32);
}

unsigned int Replace3N5(unsigned int num)
{
    unsigned int third_bit = (num & 4);
    unsigned int fifth_bit = (num & 16);

    num ^= third_bit;
    num ^= fifth_bit;

    num |= third_bit << 2;
    num |= fifth_bit >> 2;

    return num;
}

unsigned int ToDiviserOf16(unsigned int num)
{
    num >>= 4;
    num <<= 4;

    return num;    
}

void Swap(unsigned int *num1, unsigned int *num2)
{
    *num1 ^= *num2;
    *num2 ^= *num1;
    *num1 ^= *num2;
}

unsigned int CountBitsLoop(unsigned int num)
{
    size_t i = 0;
    unsigned int count = 0;

    for(i = 0 ; (i < sizeof(unsigned int) * 8); ++i)
    {
        if((num >> i) & 1)
        {
            ++count;
        }
    }

    return count;
}

unsigned int CountBits(unsigned int num)
{
    num = ((num & 0X55555555) + (num >> 1 & 0X55555555));
    num = ((num & 0X33333333) + (num >> 2 & 0X33333333));
    num = ((num & 0X0f0f0f0f) + (num >> 4 & 0X0f0f0f0f));
    num = ((num & 0X00ff00ff) + (num >> 8 & 0X00ff00ff));
    num = ((num & 0X0000ffff) + (num >> 16 & 0X0000ffff));

    return num;
}

int main()
{
    unsigned int nums[7] = {0,3,5,7,9,11,5};
    unsigned int to_swap1 = 3;
    unsigned int to_swap2 = 9;



    printf("%d\n", IsPowOf2(2));
    printf("%d\n", IsPowOf2(4));
    printf("%d\n", IsPowOf2(5));
    printf("%d\n\n", IsPowOf2(0));

    printf("%d\n", IsPowOf2NoLoop(2));
    printf("%d\n", IsPowOf2NoLoop(4));
    printf("%d\n", IsPowOf2NoLoop(5));
    printf("%d\n\n", IsPowOf2NoLoop(0));

    printf("%d\n", AddOne(100));
    printf("%d\n", AddOne(4));
    printf("%d\n", AddOne(819241));
    printf("%d\n\n", AddOne(0));

    Print3On(nums,7);

    printf("\n%u\n", ByteMirror(1u));
    printf("%u\n", ByteMirror(2147483648));

    printf("%u\n", ByteMirror(3));

    printf("%u\n", ByteMirror(3221225472));

    printf("\n%u\n", ByteMirrorNoLoop(1u));
    printf("%u\n", ByteMirrorNoLoop(2147483648));

    printf("%u\n", ByteMirrorNoLoop(3));

    printf("%u\n", ByteMirrorNoLoop(3221225472));

    printf("\n%u\n", Is2N6On(~0));
    printf("%u\n", Is2N6On(0));
    printf("%u\n", Is2N6On(1));
    printf("%u\n", Is2N6On(2));
    printf("%u\n", Is2N6On(35));


    printf("\n%u\n", Is2Or6On(~0));
    printf("%u\n", Is2Or6On(0));
    printf("%u\n", Is2Or6On(1));
    printf("%u\n", Is2Or6On(2));
    printf("%u\n", Is2Or6On(35));

    printf("\n%u\n", Replace3N5(4));
    printf("%u\n", Replace3N5(16));
 


    printf("\n%u\n",  ToDiviserOf16(16));
    printf("%u\n",  ToDiviserOf16(17));
    printf("%u\n",  ToDiviserOf16(33));
    printf("%u\n",  ToDiviserOf16(109));

    Swap(&to_swap1,&to_swap2);

    printf("\n%u\n",  to_swap1);
    printf("%u\n", to_swap2);

    printf("\n%u\n",  CountBitsLoop(109));
    printf("%u\n",  CountBitsLoop(10));
    printf("%u\n",  CountBitsLoop(1));
    printf("%u\n",  CountBitsLoop(4));
    printf("%u\n",  CountBitsLoop(3));


    printf("\n%u\n",  CountBits(109));
    printf("%u\n",  CountBits(10));
    printf("%u\n",  CountBits(1));
    printf("%u\n",  CountBits(4));
    printf("%u\n",  CountBits(3));

    return 0;

}
/*************************************************************************************
 * OL124 BitArray Project
 * 
 *  functions with return value : 0 for success . -1 for failure. 
 * 
 * 
 *   
 * ************************************************************************************/

#ifndef OL124_BIT_ARRAY_H
#define OL124_BIT_ARRAY_H

typedef unsigned long bit_arr_ty;

#ifdef ARM
typedef bit_arr_ty unsigned long long ;
#endif

/*  0 - 63 is the range of bit index */
/* bit index -> unsigned char type */
/*in case */



/*the function receives a number and position of a bit and return 0 or 1 or  -1 (error) */
int BitArrayGetVal(const bit_arr_ty *bptr, unsigned char index);
 
/*the function receives a number and postion bit and turn on specified bit . return 0 for success or 1 for failure */
int BitArraySetOn(bit_arr_ty *bptr,  unsigned char index);
 
 
/*the function receives a number and postion bit and turn off specified bit. return 0 for success or 1 for failure */
int BitArraySetOff(bit_arr_ty *bptr,  unsigned char index);


/*the function receives a number and  and parameter - position bit,  and does some operation. return  0, -1  for failure */
int BitArraySetBit(bit_arr_ty *bptr, unsigned char index, unsigned char option);


/*the function receives a number and flip the specified bit . return the flip number 0 for success and -1 for failure*/

int BitArrayFlip(bit_arr_ty *bptr, unsigned char index);

/*the function rotate  n time left  bit to number. return left rorate  number  or -1 for failure*/

void BitArrayRotateLeft(bit_arr_ty *bptr, unsigned int steps);

/*the function rotate  n time right  bit to number. return 0 for sucsses  or -1 for failure*/

void BitArrayRotateRight(bit_arr_ty *bptr, unsigned int steps);

/*the function receives a number and counts bits on. return 0 for sucsses  or -1 for failure*/
int BitArrayCountBitsOn(const bit_arr_ty *bptr);

/*the function receives a number and counts bits off. return the value of bit on or -1 for failure*/
int BitArrayCountBitsOff(const bit_arr_ty *bptr);

/*the function receives a number and turn on all the bits. return 0 for success or -1 for failure */
void BitArraySetAllOn( bit_arr_ty *bptr);
 
 
/*the function receives a number and turn off all the bits. return 0 for success or -1 for failure */
void BitArraySetAllOff( bit_arr_ty *bptr);

/*the function receives a number and return string of bit*/
void BitArrayString(const bit_arr_ty *bptr, char *_dest);

/*the function receives a number and return mirror bits or -1 for failure */
void BitArrayMirror(bit_arr_ty *bptr);

#endif /* OL124_BIT_ARRAY_H */



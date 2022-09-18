/****************************************************************************/
/*	Project:	C++ Intro													*/
/*	Date: 		08/09/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:	            												*/
/*	Version: 	1.00														*/
/****************************************************************************/


enum E {AA, BB, CC, DD}; /*ok*/
enum E2 {TT, KK}; /* ok */
//enum E e = 2;   /* not ok  - invalid conversion from ‘int’ to ‘E’*/
//enum E2 e2 = AA;    /* not ok - cannot convert ‘E’ to ‘E2’ in initialization */

// assingment to enum only to same 
 

int main()
{
    //int i = e;
    //++e; /* NOT OK */
    
    return 0;
}
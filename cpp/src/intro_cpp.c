/****************************************************************************/
/*	Project:	C++ Intro													*/
/*	Date: 		08/09/2022													*/
/*	Name: 		Amit Regev													*/
/*	Reviewer:	            												*/
/*	Version: 	1.00														*/
/****************************************************************************/


enum E {AA, BB, CC, DD}; /*ok*/
enum E2 {TT, KK}; /* ok */
enum E e = 2;   /* ok */
enum E2 e2 = AA;    /* ok */

// E2 e22 = KK; /* C++ style comments are not allowed in ISO C90 */
 
    /*int i = e;*/  /* not ok - initializer element is not constant. only literal for static and global variable */

int main()
{
    ++e;    /* ok */
    
    return 0;
}
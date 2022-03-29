/* ***********************************************************
*Author: Amit Regev
*Reviewer: Alexander Bor
*Description:  Allow to user to see on the screen when pressed: A or T . Esc for close the program.

*Infinity Labs OL124	
***************************************************************/

#include <stdlib.h> /* system */
#include <stdio.h> /* printf , scanf */

typedef void (*ptr_func)();  

    void A_Passed()
    {
        printf(" 'A-pressed' \n");
    }
    
    void T_Passed()
    {
        printf(" 'T-pressed' \n");
    }
    
    void Exit()
    {
        system("stty icanon echo");
		exit(0);
    }

    void Default()
    {
           /* empty  */
    } 

int main()
{
    ptr_func p_arr[128]; 
    int i = 0;
    char result = 0; 	

  /*  typedef char (*ptr_def)(); */
    
    ptr_func pt_A = &(A_Passed);
    ptr_func  pt_T= &(T_Passed);
    ptr_func pt_E = &(Exit);
    ptr_func ptr_Def = &(Default);
    
 
    /* initilize the LUT */
    for (i = 0; i < 128; ++i)
    {
        if ((i==65) || (i==84) || (i==27)) 
        {
            if (i==65)
            p_arr[i] = pt_A;
            
            if (i==84)
            p_arr[i] = pt_T;
            
            if (i==27)
            p_arr[i] = pt_E;
        }   
        else
           
            p_arr[i] = ptr_Def;
        
    }    

    system("stty -icanon -echo");
    printf(" 'press A or T or Esc' \n");
    while (1)
    {
    	scanf("%c", &result);
        (*(p_arr[(int)result]))(); 
    }    
    
return 0;

}

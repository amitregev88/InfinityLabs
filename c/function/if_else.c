/* ***********************************************************
*Author: Amit Regev
*Reviewer: Alexander Bor
*Description:  show on the screen A or T . Esc close the program.
*Infinity Labs: OL124	
*************************************************************** */

#include <stdlib.h> /* function system */
#include <stdio.h> 

int main()
{
    char key = 0;
    system("stty -icanon -echo");
    
    printf(" 'presse A or T or Esc' \n");
    while (0 < 1)
    {
		if ((key == 'A') || (key == 'T') || (key == 27) )
        {
			if (key == 'A')
			{
		    	printf(" A-pressed\n");
		    	scanf("%c", &key);
		    }
     
         
		 	if (key == 'T')
		 	{
		    	printf(" 'T-pressed' \n");
		    	scanf("%c", &key);
			} 

	  	 	if (key == 27)
		 	{
		    	system("stty icanon echo");
		    	exit(0);
		 	}
        }  
        else
        {
             scanf("%c", &key);
        }
    }     

	return 0;

}


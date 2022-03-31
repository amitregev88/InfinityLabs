/* ***********************************************************
*Author: Amit Regev
*Reviewer: Alexander Bor
*Description:  show on the screen A or T . Esc close the program.
*Infinity Labs: OL124	
****************************************************************/

#include <stdlib.h> /* system */
#include <stdio.h> 

int main()
{
    char key = 0;
    system("stty -icanon -echo");
    
    printf("press A or T. Esc to exit\n");
    while (0 < 1)
    {
        switch (key)
		{
	    	case 'A':
                printf("A-pressed\n");
                scanf("%c", &key);
			break;
		          
	      	case 'T':
		  	printf("T-pressed\n");
		  	scanf("%c", &key);
		  	break;   
		 
			case 27:
			system("stty icanon echo");
		  	exit(0);
		  	
		  	default:
		  	scanf("%c", &key);
		  	
		}   

    }    

	return 0;

}

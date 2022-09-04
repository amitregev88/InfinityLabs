
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h> /*sleep*/
#include "wd.h"


int main(int argc, char *argv[], char *envp[])
{  
    MMI(2, 7, argv);

    while(1)
    {

        sleep(100);

    }    
    
    

    DNR();

    return 0;

}





#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "watchdog.h"


int main(int argc, char *argv[], char *envp[])
{
    int status;
   
    status = MMI(size_t interval, size_t max_of_failures, char *exec_client_path);
    if (status != 0)
    {
        return -1;

    }

    /*
        code of the client app
    
    
    */

    DNR();

    return 0;

}




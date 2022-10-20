#include <stdio.h> /*printf*/
#include <sys/msg.h> /*msgget, key_t, msgrcv*/
#include "../include/utility.h"

#define PERMS 0644

typedef struct
{
    long mtype;
    char mtext[200];
}msg_package;

int main(void) 
{
   msg_package buf;
   int msqid;
   int ret;
   int count = 5;
   key_t key;
   
    key = ftok("msgq.txt", 'B');
    ReturnErnoIfFail(key != -1, "ftok failed", -1);

   
    msqid = msgget(key, PERMS); /* connect to the queue */
    ReturnErnoIfFail(msqid != -1, "msqid failed", -1);

   printf("message queue: ready to receive messages.\n");
   
   while (count)
   {
        --count;
        ret = msgrcv(msqid, &buf, sizeof(buf.mtext), 1, 0);
        ReturnErnoIfFail(ret != -1, "msgrcv failed", -1);

        printf("recived: \"%s\"\n", buf.mtext);            
   }

   printf("message queue: done receiving messages.\n");
   system("rm msgq.txt");

   return 0;
}

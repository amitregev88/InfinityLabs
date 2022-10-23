#include <stdio.h>/*printf*/
#include <sys/msg.h>/*msgsnd*/
#include <string.h>/*strlen*/

#include "../include/utility.h"

#define PERMS 0644

typedef struct
{
    long mtype;
    char mtext[200];
} msg_package;

int main(void)
{
    msg_package buf;
    int msqid;
    int len;
    key_t key;
    int ret;
    char *buff_msg = "Ping Pong";
    int count = 5;

    memcpy(buf.mtext, buff_msg, strlen(buff_msg));

    system("touch msgq.txt");

    key = ftok("msgq.txt", 'B');
    ReturnErnoIfFail(key != -1, "ftok failed", -1);

    msqid = msgget(key, PERMS | IPC_CREAT);
    ReturnErnoIfFail(msqid != -1, "msgget failed", -1);

    printf("message queue: ready to send messages.\n");
    
    buf.mtype = 1; /* we don't really care in this case */

    /*while (fgets(buf.mtext, sizeof buf.mtext, stdin) != NULL)*/
    while(count)
    {
        len = strlen(buf.mtext);
        /* remove newline at end, if it exists */
        if (buf.mtext[len - 1] == '\n')
        {
            buf.mtext[len - 1] = '\0';
        }
        
        ret = msgsnd(msqid, &buf, len + 1, 0);  /* +1 for '\0' */
        ReturnErnoIfFail(ret != -1, "msgsnd failed", -1);
        --count;        
    }
    
    printf("message queue: done sending messages.\n");
    return 0;
}
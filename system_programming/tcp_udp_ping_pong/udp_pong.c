#include <stdio.h>      /*printf*/
#include <unistd.h>     /*close*/
#include <string.h>     /*memset, strlen*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*sockaddr_in*/

#include "../include/utility.h"

#define PORT 55555
#define BUFFER_SIZE 20

/*Client side implementation of UDP client-server model */
int main()
{
    int fd;
    char buffer[BUFFER_SIZE];
    const char *msg = "pong";
    struct sockaddr_in server_addr;
    int n_bytes_recived;
    int n_bytes_sent;
    int i = 0;
    int count = 5;

    int len;

    /*Creating socket file descriptor*/
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ReturnErnoIfFail(fd != -1, "socket() failed", -1);

    memset(&server_addr, 0, sizeof(server_addr));

    /*Filling server information */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = INADDR_ANY;

  
    
    for (i = 0; i < count; ++i)
    {
        n_bytes_sent = sendto(fd, msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *)&server_addr, sizeof(server_addr));
        ReturnErnoIfFail(n_bytes_sent != -1, "sendto() failed", -1);

        printf("client message sent.\n");

        n_bytes_recived = recvfrom(fd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, (socklen_t *)&len);
        ReturnErnoIfFail(n_bytes_recived != -1, "recvfrom() failed", -1);

        buffer[n_bytes_recived] = '\0';

        printf("recived from Server : %s\n", buffer);
    }

    close(fd);

    return 0;
}
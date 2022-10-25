/*client impliment*/

#include <stdio.h>      /*printf*/
#include <unistd.h>     /*close*/
#include <string.h>     /*memset, strlen*/
#include <sys/socket.h> /*socket*/
#include <netinet/in.h> /*sockaddr_in*/
#include <arpa/inet.h> /* inet_addr */

#include "../include/utility.h"

#define SERVER_PORT 55555
#define CLIENT_PORT 55556

#define BUFFER_SIZE 20

/*Client side implementation of UDP client-server model */
int main()
{
    int fd;
    char buffer[BUFFER_SIZE];
    const char *msg = "pong";
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};

    int n_bytes_recived;
    int n_bytes_sent;
    int i = 0;
    int count = 5;
    
    int ret;

    int len;



    /*Creating socket file descriptor*/
    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ReturnErnoIfFail(fd != -1, "socket() failed", -1);

    memset(&server_addr, 0, sizeof(server_addr));

    /*Filling server information */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 

    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(CLIENT_PORT);
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); /*to myself*/

    ret = bind(fd, (const struct sockaddr *)&client_addr, sizeof(client_addr));
    ReturnErnoIfFail(ret != -1, "bind failed", -1);
  
    
    for (i = 0; i < count; ++i)
    {
        n_bytes_sent = sendto(fd, msg, strlen(msg), 0, (const struct sockaddr *)&server_addr, sizeof(server_addr));
        ReturnErnoIfFail(n_bytes_sent != -1, "sendto() failed", -1);

        printf("client message sent.\n");

        n_bytes_recived = recvfrom(fd, (char *)buffer, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, (socklen_t *)&len);
        ReturnErnoIfFail(n_bytes_recived != -1, "recvfrom() failed", -1);

        buffer[n_bytes_recived] = '\0';

        printf("recieved from Server : %s\n", buffer);
    }

    close(fd);

    return 0;
}
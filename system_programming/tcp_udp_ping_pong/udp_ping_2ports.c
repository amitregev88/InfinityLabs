/****************************************************************************
 *	Project:	TCP / UDP Ping-Pong                             			*												*
 *	Date: 		23/10/2022													*
 *	Name: 		Amit Regev													*
 *	Reviewer:												                *
 *	Version: 	1.00														*
 ****************************************************************************/
/*server impliment*/
#include <stdio.h>      /*printf*/
#include <string.h>     /*memcpy , strlen*/
#include <sys/socket.h> /*socket, bind*/
#include <netinet/in.h> /*sockaddr_in*/

#include "../include/utility.h"

#define BUFFER_SIZE 20
#define SERVER_PORT 55555
#define CLIENT_PORT 55556

/*UDP Server*/
/* Server side implementation of UDP client-server model */
int main(void)
{
    int fd;
    char buff[BUFFER_SIZE];
    const char *msg = "ping";
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr =  {0};
    int ret;
    int len;
    int n_bytes_recieved;
    int n_bytes_sent;
    int i = 0;
    int count = 5;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ReturnErnoIfFail(fd != -1, "socket failed", -1);

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    /*Filling server information */

    server_addr.sin_family = AF_INET; /*IPv4*/
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
    server_addr.sin_port = htons(SERVER_PORT);


    client_addr.sin_family = AF_INET;
    client_addr.sin_port = htons(CLIENT_PORT);
    client_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); /*to myself*/


    ret = bind(fd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    ReturnErnoIfFail(ret != -1, "bind failed", -1);

    len = sizeof(client_addr); /*len is value/result */

    for (i = 0; i < count; ++i)
    {
        n_bytes_recieved = recvfrom(fd, &buff, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&server_addr, (socklen_t *)&len);
        ReturnErnoIfFail(n_bytes_recieved != -1, "recvfrom", -1);

        buff[n_bytes_recieved] = '\0';

        printf("recieved from Client  : %s\n", buff);

        n_bytes_sent = sendto(fd, msg, strlen(msg), 0, (const struct sockaddr *)&client_addr, len);
        ReturnErnoIfFail(n_bytes_sent != -1, "sendto failed", -1);

        printf("Server message sent.\n");
    }

    return 0;
}

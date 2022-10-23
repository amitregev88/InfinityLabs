/****************************************************************************
 *	Project:	TCP / UDP Ping-Pong                             			*												*
 *	Date: 		23/10/2022													*
 *	Name: 		Amit Regev													*
 *	Reviewer:												                *
 *	Version: 	1.00														*
 ****************************************************************************/

#include <stdio.h>  /*printf*/
#include <string.h> /*memcpy , strlen*/
/*#include <stdlib.h> */
/*#include <unistd.h> */

/*#include <sys/types.h> */
#include <sys/socket.h> /*socket, bind*/
/*#include <arpa/inet.h> */
#include <netinet/in.h> /*sockaddr_in*/

#include "../include/utility.h"

#define BUFFER_SIZE 20
#define PORT 55555

/*UDP Server*/
/* Server side implementation of UDP client-server model */
int main(void)
{
    int fd;
    char buff[BUFFER_SIZE];
    const char *msg = "ping";
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;
    int ret;
    int len;
    int n_bytes_recieved;
    int n_bytes_sent;
    int count = 0;
    int i = 0;

    fd = socket(AF_INET, SOCK_DGRAM, 0);
    ReturnErnoIfFail(fd != -1, "socket failed", -1);

    memset(&server_addr, 0, sizeof(server_addr));
    memset(&client_addr, 0, sizeof(client_addr));

    /*Filling server information */

    server_addr.sin_family = AF_INET; /*IPv4*/
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    ret = bind(fd, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    ReturnErnoIfFail(ret != -1, "socket failed", -1);

    len = sizeof(client_addr); /*len is value/result */
    for (i = 0; i < count; ++i)
    {
        n_bytes_recieved = recvfrom(fd, &buff, BUFFER_SIZE, MSG_WAITALL, (struct sockaddr *)&client_addr, (socklen_t *)&len);
        ReturnErnoIfFail(n_bytes_recieved != -1, "recvfrom", -1);

        buff[n_bytes_recieved] = '\0';

        printf("recieved from Client  : %s\n", buff);

        n_bytes_sent = sendto(fd, msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *)&client_addr, len);
        ReturnErnoIfFail(n_bytes_sent != -1, "sendto failed", -1);

        printf("Server message sent.\n");

        ++count;
    }

    return 0;
}

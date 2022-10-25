/****************************************************************************
 *	Project:	TCP / UDP Ping-Pong                             			*												*
 *	Date: 		23/10/2022													*
 *	Name: 		Amit Regev													*
 *	Reviewer:												                *
 *	Version: 	1.00														*
 ****************************************************************************/
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h> /*fd_set, select*/
#include <arpa/inet.h> /*htons, htonl */

#include "../include/utility.h"

#define MSG "Amit"
#define IP_FOUND_ACK "IP_FOUND_ACK"
#define PORT 55555

int main()
{
    int socket_desc;
    int yes = 1;
    struct sockaddr_in broadcast_addr;
    int addr_len;
    int count;
    int ret;
    fd_set readfd;
    char buffer[1024];
    int i;

    socket_desc = socket(AF_INET, SOCK_DGRAM, 0);
    ReturnErnoIfFail(socket_desc != -1, "socket failed", -1);

    ret = setsockopt(socket_desc, SOL_SOCKET, SO_BROADCAST, (char *)&yes, sizeof(yes));
    ReturnErnoIfFail(ret != -1, "setsockopt failed", -1);

    addr_len = sizeof(struct sockaddr_in);

    memset((void *)&broadcast_addr, 0, addr_len);
    broadcast_addr.sin_family = AF_INET;
    broadcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    broadcast_addr.sin_port = htons(PORT);

    for (i = 0; i < 3; i++)
    {
        ret = sendto(socket_desc, MSG, strlen(MSG), 0, (struct sockaddr *)&broadcast_addr, addr_len);
        ReturnErnoIfFail(ret != -1, "sendto failed", -1);

        FD_ZERO(&readfd);
        FD_SET(socket_desc, &readfd);

        ret = select(socket_desc + 1, &readfd, NULL, NULL, NULL);
        ReturnErnoIfFail(ret != -1, "select failed", -1);
        
    }
    return 0;
}

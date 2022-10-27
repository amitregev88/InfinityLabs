/****************************************************************************
 *	Project:	TCP / UDP Ping-Pong                             			*												*
 *	Date: 		24/10/2022													*
 *	Name: 		Amit Regev													*
 *	Reviewer:	Amir Shachar										        *
 *	Version: 	1.00														*
 ****************************************************************************/
#include <stdio.h>
#include <string.h> /*atoi*/
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> /*close*/

#include "../include/utility.h"

#define PORT 55555
#define MAX(a,b) (a > b) ? a: b

static int InitNBind(int protocol_type);



int main(void)
{
    int socket_tcp;
    int socket_udp;
    fd_set master_set;    /* master file descriptor list*/
    fd_set read_fds; 
    
    int n_bytes_recieved;
    int n_bytes_sent;
    char buff[100];
    char *msg = "ping";
    struct sockaddr client_addr;
    int len = sizeof(client_addr);

    socket_udp = InitNBind(SOCK_DGRAM);
    ExitIfFail(socket_udp != -1, "InitNBind udp failed\n", -1);

    printf("main socketfd is: %d\n", socket_udp);

    socket_tcp = InitNBind(SOCK_STREAM);
    ExitIfFail(socket_tcp != -1, "InitNBind tcp failed\n", -1);

    FD_ZERO(&master_set);
    FD_SET(socket_udp, &master_set);
    FD_SET(socket_tcp, &master_set);
    FD_SET(STDIN_FILENO, &master_set);



    while()
    {
        






    }


    /*********************************************************************************/

    n_bytes_recieved = recvfrom(socket_udp, &buff, 100, 0, (struct sockaddr *)&client_addr, (socklen_t *)&len);
    printf("n bytes revieved: %d\n", n_bytes_recieved);
    ExitIfFail(n_bytes_recieved != -1, "recvfrom failed\n", -1);

    buff[n_bytes_recieved] = '\0';

    printf("recieved from Client: %s\n", buff);

    n_bytes_sent = sendto(socket_udp, msg, strlen(msg), 0, (const struct sockaddr *)&client_addr, len);
    ExitIfFail(n_bytes_sent != -1, "sendto failed\ns", -1);

    printf("Server message sent.\n");







    
    /*FD_SET()*/
    
    return 0;

}


static int InitNBind(int protocol_type)
{

    int sockfd;
    int status;
    struct sockaddr_in server = {0};

    sockfd  = socket(AF_INET, protocol_type | SOCK_NONBLOCK, 0);
    ReturnErnoIfFail(sockfd != -1, "socket failed", -1);

    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = htonl(INADDR_ANY);

    status = bind(sockfd, (const struct sockaddr *)&server, sizeof(server));
    ReturnErnoIfFail(status != -1, "bind failed", -1);

    printf("InitNBind socketfd is: %d\n", sockfd);
    return sockfd;

}
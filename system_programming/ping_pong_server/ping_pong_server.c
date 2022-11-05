/****************************************************************************/
/*	Project:    Ping Pong            								        */
/*	File:	    ping_pong_server.c	        		       	            	*/
/*	Date: 		23/10/2022					    							*/
/*	Name: 		Amit						    							*/
/*	Reviewer:						    	    							*/
/*	Version: 	1.00						    							*/
/****************************************************************************/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/types.h>    
#include <sys/socket.h>

#include "utility.h"

typedef struct 
{
    int lfd;
    struct sockaddr_in* tcp_addr;
}tcp_ty;

typedef struct 
{
    int udp_fd;
    struct sockaddr_in* udp_addr;
}udp_ty;

typedef struct
{
    tcp_ty* tcp_server;
    udp_ty* udp_server;

}server_data_ty;


#define MAX(x,y) ((x) > (y) ? (x) : (y))

#define PORT_NUM 55555
enum{MAX_LEN = 500};
enum{ERROR = 1, EXIT = 2};

static void InitAddrNPort(struct sockaddr_in* addr);
static int Server(server_data_ty *s_d);
static int CommunicStdin(void);
static int TCPGetFd(tcp_ty* tcp_data);


int main()
{
    int ret_stat = 0;
    int listen_fd = 0;

    struct sockaddr_in udp_server = {0};
    struct sockaddr_in tcp_server = {0};

    udp_ty udp_data = {0};
    tcp_ty tcp_data = {0};
    server_data_ty server_data = {0};

    /* create socket for udp+tcp int SocketCreate() */
    int udp_fd = socket(AF_INET, SOCK_DGRAM | SOCK_NONBLOCK, 0);
    ReturnErnoIfFail(-1 != udp_fd, "socket udp failure", 1);

    listen_fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    ReturnErnoIfFail(-1 != listen_fd, "socket tcp failure", 1);

    /* InitAddrStruct for both udp+tcp */
    InitAddrNPort(&udp_server);
    InitAddrNPort(&tcp_server);

    /* bind udp: */
    ret_stat = bind(udp_fd, (struct sockaddr*)&udp_server, sizeof(struct sockaddr_in));
    ReturnErnoIfFail(ret_stat == 0, "bind udp failure", 1);

    /* bind tcp: */
    ret_stat = bind(listen_fd, (struct sockaddr*)&tcp_server, sizeof(struct sockaddr_in));
    ReturnErnoIfFail(ret_stat == 0, "bind tcp failure", 1);

    /* listen */
    ReturnErnoIfFail(listen(listen_fd, 1) == 0, "listen failure", 1);

    tcp_data.lfd = listen_fd;
    tcp_data.tcp_addr = &tcp_server;
    udp_data.udp_fd = udp_fd;
    udp_data.udp_addr = &udp_server;
    server_data.tcp_server = &tcp_data;
    server_data.udp_server = &udp_data;

    return Server(&server_data);
    /* return if bad server ? || (exit) */    

}
/******************************************************************************/

static void InitAddrNPort(struct sockaddr_in* addr)
{
    addr->sin_family = AF_INET;
    addr->sin_port = htons(PORT_NUM);
    addr->sin_addr.s_addr = htonl(INADDR_ANY); 
}
/******************************************************************************/

static int TCPGetFd(tcp_ty* tcp_data)
{
    unsigned int len = 0;
    int socket_fd = 0;

    assert(tcp_data);

    socket_fd = accept(tcp_data->lfd, (struct sockaddr*)tcp_data->tcp_addr, &len);
    ReturnErnoIfFail(socket_fd != -1, "accept failure", 1);

    return socket_fd;
}
/******************************************************************************/

static int Communicate(int fd)
{
    char buff[MAX_LEN];
    int ret_stat = 0;
    int bytes_num = 0;
    char* msg = "LOROTSA!\n";
    size_t msg_len = strlen(msg) + 1;

    struct sockaddr_in client = {0};
    unsigned int len = sizeof(client);

    /* recvfrom */
    bytes_num = recvfrom(fd, buff, MAX_LEN, 0, (struct sockaddr*)&client, &len);

   /* if (bytes_num <= -1 && errno == EWOULDBLOCK )
    {
        printf("recvfrom return mashu\n");
        return bytes_num;
    }*/

    if(bytes_num <= 0)
    {
        return bytes_num;
    }


    /* check msg */

    /* print msg */
    printf("%s\n", buff);
    fflush(stdout);

    /* send back  */
    ret_stat = sendto(fd, msg, msg_len, 0, (struct sockaddr*)&client, 
                                                     sizeof(struct sockaddr_in));
    ReturnErnoIfFail(ret_stat != -1, "sendto failure", 1);

    return bytes_num;
}
/******************************************************************************/

/******************************************************************************/

static int Server(server_data_ty *s_d)
{
    int fd = 0;
    int event_status = 0;
    int ret_stat = 0;
    int ret_select = 0;
    int bytes_num = 0;
    int socket_fd = 0;
    int stdin_fd = 0;
    int max_fd = 0;
    fd_set read_fds = {0};
    fd_set keep_set = {0};
    struct timeval timer = {7, 0};

    assert(s_d);
    
    max_fd = MAX(s_d->udp_server->udp_fd, s_d->tcp_server->lfd);
    
    /* zero set */
    FD_ZERO(&read_fds);

    /* add to set */
    FD_SET(stdin_fd, &read_fds);
    FD_SET(s_d->udp_server->udp_fd, &read_fds);
    FD_SET(s_d->tcp_server->lfd, &read_fds);

    keep_set = read_fds;

    /* while 1: */
    while(event_status != EXIT)
    {
        /* select */
        ret_select = select(max_fd + 1, &read_fds, NULL, NULL, &timer);
        ReturnErnoIfFail(ret_select != -1, "select failure", 1);

        /* if timeout */
        if (!ret_select)
        {          
            printf("no client for 7 sec`\n");
        }

        /* for loop */
        for(fd = 0; fd <= max_fd; ++fd)
        {
            /* check if fd is set */
            if (FD_ISSET(fd, &read_fds))
            {
                /* if (fd == s_d->tcp_server->lfd) */
                if(s_d->tcp_server->lfd == fd)
                {
                    /* tcp */
                    socket_fd = TCPGetFd(s_d->tcp_server);
                    ReturnErnoIfFail(1 != socket_fd, "TCPGetFd", 1);
                    
                    /* add to set update max */
                    FD_SET(socket_fd, &keep_set);
                    max_fd = MAX(max_fd, socket_fd);
                }

                else if(s_d->udp_server->udp_fd == fd)
                {
                    ret_stat = Communicate(s_d->udp_server->udp_fd);
                    ReturnErnoIfFail(ret_stat != -1, "recvfrom failure", 1);
                }

                else if(stdin_fd == fd)
                {
                    /* read from stdin */
                    event_status = CommunicStdin();
                }
                else     /* other tcp fd */
                {
                    bytes_num = Communicate(fd);
                    /* if num of bytes  0:  */
                    if(bytes_num <= 0)
                    {
                        /* close fd */
                        ret_stat = close(fd);
                        /* log problem if bad */
                        ReturnErnoIfFail(-1 != ret_stat, "close fd failure\n",-1);

                        /* update set */
                        FD_CLR(fd, &keep_set);
                        /* updae max */
                        if (max_fd == fd)     
                        {
                            while ( !FD_ISSET(max_fd, &keep_set) )
                            {
                                --max_fd;
                            }
                        }
                    }
                }
            }
        }

        /* update timer */
        timer.tv_sec = 7;
        timer.tv_usec = 0;

        read_fds = keep_set;
    }

    /* close */
    for(fd = 1; fd <= max_fd; ++fd)
    {
        if(FD_ISSET(fd, &read_fds))
        {
            close(fd);
            ReturnErnoIfFail(-1 != ret_stat, "close fd failure\n",-1);
        }
    }

    return 0;

}
/******************************************************************************/
static int CommunicStdin(void)
{
    char* msg[] = {"ping", "quit"};
    char buff[MAX_LEN];
    int ret_stat = read(0, buff, 4);
    ReturnErnoIfFail(ret_stat != -1, "recvfrom failure", 1);

    buff[4] = '\0';

    if(0 == strcmp(buff, msg[0]))
    {
        printf("pong\n");
        return 0;
    }

    else if (0 == strcmp(buff, msg[1]))
    {
        return EXIT;
    }

    return 0;
}

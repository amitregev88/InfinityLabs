#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h> /*close*/

#include "../include/utility.h"

#define PORT 55555
int main(void)
{
    int socket_desc;
    int client_sock;
    int client_size;
    struct sockaddr_in server_addr = {0};
    struct sockaddr_in client_addr = {0};
    char server_message[] = "pong";
    char client_message[2000] = {0};
    int ret;
    size_t i = 0;
    size_t count = 5;

    /*Create socket:*/
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    ReturnErnoIfFail(socket_desc != -1, "socket failed", -1);

    /* Set port and IP */
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Bind to the set port and IP */
    ret = bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ReturnErnoIfFail(socket_desc != -1, "bind failed", -1);

    /* Listen for clients */
    ret = listen(socket_desc, 1);
    ReturnErnoIfFail(ret != -1, "listen failed", -1);

    /*Accept an incoming connection*/
    client_size = sizeof(client_addr);
    client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, (socklen_t *)&client_size);
    ReturnErnoIfFail(client_sock != -1, "accept failed", -1);

    printf("Client connected at IP: %s and port: %i\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

    for (; i < count; ++i)
    {

        /* Receive client's message: */
        ret = recv(client_sock, client_message, sizeof(client_message), 0);
        ReturnErnoIfFail(ret != -1, "recv failed - ping", -1);

        printf("Message from client: %s\n", client_message);

        ret = send(client_sock, server_message, strlen(server_message), 0);
        ReturnErnoIfFail(ret != -1, "send failed", -1);
    }
    /*Closing the socket:*/
    close(client_sock);
    close(socket_desc);

    return 0;
}

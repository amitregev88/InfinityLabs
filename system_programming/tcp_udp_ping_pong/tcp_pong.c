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
    struct sockaddr_in server_addr = {0};
    char server_message[2000] = {0};
    char client_message[] = "ping";
    int ret;
    size_t i = 0;
    size_t count = 5;

    /* Create socket*/
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    ReturnErnoIfFail(socket_desc != -1, "socket failed", -1);

    /* Set port and IP the same as server-side*/
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    /* Send connection request to server*/
    ret = connect(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr));
    ReturnErnoIfFail(ret != -1, "connect failed", -1);

    for (; i < count; ++i)
    {

        /* Send the message to server*/
        ret = send(socket_desc, client_message, strlen(client_message), 0);
        ReturnErnoIfFail(ret != sizeof(client_message), "send failed", -1);

        /* Receive the server's response*/
        ret = recv(socket_desc, server_message, sizeof(server_message), 0);
        ReturnErnoIfFail(ret != -1, "recv failed - pong", -1);

        printf("Server's response: %s\n", server_message);
    }

    /*Close the socket*/
    close(socket_desc);

    return 0;
}

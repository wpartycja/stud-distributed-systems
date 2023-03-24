#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "mensajes.h"
#include "claves.h"

#define BUF_SIZE    276
#define PORT        2137


int init(){
    // create needed structures
    char buf[BUF_SIZE];
    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(0)
    };
    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr("127.0.0.1"),
            .sin_port = htons(PORT)
    };

    // create socket
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // bind socket to local address
    int bind_result = bind(socket_fd, (const struct sockaddr *) &client_address, sizeof(client_address));
    if (bind_result < 0) {
        perror("error binding socket");
        return 1;
    }

    // connect to server
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // create request
    struct request req;
    req.operation_id = 0;

    // copy data to buffer
    memcpy(buf, &req, sizeof(req));


    int bytes_sent = (int) send(socket_fd, buf, sizeof(buf), 0);
    if (bytes_sent < 0) {
        perror("error sending data");
        return 1;
    }

    printf("sent %d bytes to server\n", bytes_sent);

    return 0;
}
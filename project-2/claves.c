#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#include "mensajes.h"
#include "claves.h"

#define BUF_SIZE    277
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

    printf("Operation id: %d: sent %d bytes to server\n", req.operation_id, bytes_sent);

    return 0;
}

int set_value(int key, char *value1, int value2, double value3) {
    int n = strlen(value1)+1;
    if(n > 256){
 	    perror("Error: value1 is greater than 256 bytes.");
            return -1; // If size if bigger.
    }

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
    req.operation_id = 1;
    req.key = key;
    strcpy(req.value1, value1);
    req.value2 = value2;
    req.value3 = value3;

    // copy data to buffer
    memcpy(buf, &req, sizeof(req));


    int bytes_sent = (int) send(socket_fd, buf, sizeof(buf), 0);
    if (bytes_sent < 0) {
        perror("error sending data");
        return 1;
    }

    printf("Operation id: %d: sent %d bytes to server\n", req.operation_id, bytes_sent);

    return 0;
}

int get_value(int key, char *value1, int *value2, double *value3) {
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
    req.operation_id = 2;
    req.key = key; 
    strcpy(req.value1, value1); 
    req.value2 = *value2; 
    req.value3 = *value3;

    // copy data to buffer
    memcpy(buf, &req, sizeof(req));


    int bytes_sent = (int) send(socket_fd, buf, sizeof(buf), 0);
    if (bytes_sent < 0) {
        perror("error sending data");
        return 1;
    }

    printf("Operation id: %d: sent %d bytes to server\n", req.operation_id, bytes_sent);

    return 0;
}

int modify_value(int key, char *value1, int value2, double value3) {
    int n = strlen(value1)+1;
    if(n > 256){
 	    perror("Error: value1 is greater than 256 bytes.");
            return -1; // If size if bigger.
    }

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
    req.operation_id = 3;
    req.key = key;
    strcpy(req.value1, value1);
    req.value2 = value2;
    req.value3 = value3;

    // copy data to buffer
    memcpy(buf, &req, sizeof(req));


    int bytes_sent = (int) send(socket_fd, buf, sizeof(buf), 0);
    if (bytes_sent < 0) {
        perror("error sending data");
        return 1;
    }

    printf("Operation id: %d: sent %d bytes to server\n", req.operation_id, bytes_sent);

    return 0;

}

int delete_key(int key) {
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
    req.operation_id = 4;
    req.key = key; 

    // copy data to buffer
    memcpy(buf, &req, sizeof(req));


    int bytes_sent = (int) send(socket_fd, buf, sizeof(buf), 0);
    if (bytes_sent < 0) {
        perror("error sending data");
        return 1;
    }

    printf("Operation id: %d: sent %d bytes to server\n", req.operation_id, bytes_sent);

    return 0;
}


int exist(int key) {
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
    req.operation_id = 5;
    req.key = key; 

    // copy data to buffer
    memcpy(buf, &req, sizeof(req));


    int bytes_sent = (int) send(socket_fd, buf, sizeof(buf), 0);
    if (bytes_sent < 0) {
        perror("error sending data");
        return 1;
    }

    printf("Operation id: %d: sent %d bytes to server\n", req.operation_id, bytes_sent);

    return 0;
}

// int copy_key(int key1, int key2) {
//     // create needed structures
//     char buf[BUF_SIZE];
//     struct sockaddr_in client_address = {
//             .sin_family = AF_INET,
//             .sin_addr.s_addr = htonl(INADDR_ANY),
//             .sin_port = htons(0)
//     };
//     struct sockaddr_in server_address = {
//             .sin_family = AF_INET,
//             .sin_addr.s_addr = inet_addr("127.0.0.1"),
//             .sin_port = htons(PORT)
//     };

//     // create socket
//     int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
//     if (socket_fd < 0) {
//         perror("error creating socket");
//         return 1;
//     }

//     // bind socket to local address
//     int bind_result = bind(socket_fd, (const struct sockaddr *) &client_address, sizeof(client_address));
//     if (bind_result < 0) {
//         perror("error binding socket");
//         return 1;
//     }

//     // connect to server
//     int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
//     if (connect_result < 0) {
//         perror("error connecting to server");
//     }

//     mqd_t server_queue; 
//     mqd_t client_queue; 
//     struct request req;
//     struct response res;
//     struct mq_attr attr; 

//     char queue_name[MAXSIZE];

//     attr.mq_maxmsg = 1; 
//     attr.mq_msgsize = sizeof(res);
//     sprintf(queue_name, "/Queue-%d", getpid());
    
//     // Verify communication errors (client).
//     if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
// 	    perror("set_value: error with client queue - mq_open");
// 	    return -1;
//     }

//     // Verify communication errors (server).
//     if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
// 	    perror("set_value: error with server queue - mq_open");
// 	    mq_close(client_queue);
// 	    mq_unlink(queue_name);
	    
// 	    return -1;
//     }

//      // Fill request.
//     req.operation_id = 6;
//     strcpy(req.queue_name, queue_name);
//     req.key = key1;
//     req.value2 = key2;

//     if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
// 	    perror("set_value: error while filling request - mq_send");
// 	    mq_close(server_queue);
// 	    mq_close(client_queue);
// 	    mq_unlink(queue_name);
	    
// 	    return -1;
//     }

//     if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
// 	    perror("set_value: error while filling request - mq_receive");
// 	    mq_close(server_queue);
// 	    mq_close(client_queue);
// 	    mq_unlink(queue_name);

// 	    return -1;
//     }
    
//     mq_close(server_queue); 
//     mq_close(client_queue); 
//     mq_unlink(queue_name);

//     return res.result;
// }

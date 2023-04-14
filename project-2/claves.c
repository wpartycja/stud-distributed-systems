#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <netdb.h>


#include "mensajes.h"
#include "claves.h"

#define BUF_SIZE    276
#define PORT        2137
#define MAX_SIZE    256


int init(){
    // create needed structures
    char buf[BUF_SIZE];

    char *ip_as_string   = getenv("IP_TUPLAS");
    if (NULL == ip_as_string) {
        perror("Error: No está establecida la variable de entorno IP_TUPLAS.");
        return -1;
    }

    struct hostent *host =  gethostbyname(ip_as_string) ;
    if (NULL == host) {
        perror("Error");
        return -1;
    }
    char * ip_as_addr = inet_ntoa (*(structin_addr*)host->h_addr) ;
    //address.sin_addr.s_addr = *((unsigned long *)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string) ;

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY), // INADDR_ANY (serv)
            .sin_port = htons(0)                  // <- TODO: 0 es el valor pasado por atoi(argv[1]) (serv)
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = ip_as_addr,  // var de entorno
            .sin_port = htons(port_as_int)  // var de entorno
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
    	// Verify if value1 is the right size.
	if(strlen(value1) >= MAX_SIZE){
		printf("Error set_value(): size of value1 in file %d is bigger than 256 bytes.\n", key);
		printf("----------------------------------------\n");

		return -1;
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

int copy_key(int key1, int key2) {
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
    req.operation_id = 6;
    req.key = key1;
    req.value2 = key2;

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
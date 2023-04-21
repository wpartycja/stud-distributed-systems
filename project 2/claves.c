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
#include "lines.h"

#define BUF_SIZE    276
#define MAX_SIZE    256

int init(){
    // Create needed structures.
    char buf[MAX_SIZE];

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
    char * ip_as_addr = inet_ntoa (*(struct in_addr*)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string);

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY), 
            .sin_port = htons(0)
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr(ip_as_addr),  
            .sin_port = htons(port_as_int)  
    };

    // Create socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // Connect to server.
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // Create request.
    char req = 0;
    sendMessage(socket_fd, (char *)&req, 1);

    // Response from the server.
    if (readLine(socket_fd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while waiting for response from the server.\n");
        return -1;
    }

    // Closing the connection.
    close(socket_fd);

    // Result of the operation.
    return atoi(buf);
}

int set_value(int key, char *value1, int value2, double value3) {
    // Verify if value1 is the right size.
	if(strlen(value1) >= MAX_SIZE){
		printf("Error set_value(): size of value1 in file %d is bigger than 256 bytes.\n", key);
		printf("----------------------------------------\n");

		return -1;
	}

    // Buffer to receive messages.
    char buf[MAX_SIZE];

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
    char * ip_as_addr = inet_ntoa (*(struct in_addr*)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string);

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY), 
            .sin_port = htons(0)                  
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr(ip_as_addr),  
            .sin_port = htons(port_as_int) 
    };

    // Create socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // Connect to server.
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // Create the request. 
    char req = 1;
    sendMessage(socket_fd, (char *)&req, 1);

    // Send key.
    sprintf(buf, "%d", key);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Send values. 
    sendMessage(socket_fd, value1, strlen(value1) + 1);
    sprintf(buf, "%d", value2);
    sendMessage(socket_fd, buf, strlen(buf) + 1);
    sprintf(buf, "%f", value3);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Response from the server.
    if (readLine(socket_fd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while waiting for response from the server.\n");
        return -1;
    }

    // Closing the connection.
    close(socket_fd);

    // Result of the operation.
    return atoi(buf);
}

int get_value(int key, char *value1, int *value2, double *value3) {
    // Buffer to receive messages.
    char buf[MAX_SIZE];

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
    char * ip_as_addr = inet_ntoa (*(struct in_addr*)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string);

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(0)
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr(ip_as_addr),
            .sin_port = htons(port_as_int)
    };

    // Create socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // Connect to server.
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // Create the request. 
    char req = 2;
    sendMessage(socket_fd, (char *)&req, 1);

    // Send key to server.
    sprintf(buf, "%d", key);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    if (readLine(socket_fd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while waiting for response from the server.\n");
        return -1;
    }

    // Get value1.
    if (readLine(sd, value1, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while receiving value1.\n");
        close(socket_fd);
        return -1;
    }

    // Get value2.
    if (readLine(sd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while receiving value2.\n");
        close(socket_fd);
        return -1;
    }
    *value2 = atoi(buf);

    // Get value3.
    if (readLine(sd, buf, MAX_LINE) < 0) {
        fprintf(stderr, "Error: Problem while receiving value3.\n");
        close(socket_fd);
        return -1;
    }
    *value3 = atof(buf);

    // Close the connection.
    close(socket_fd);

    return 0;
}

int modify_value(int key, char *value1, int value2, double value3) {
    int n = strlen(value1)+1;
    if(n > 256){
 	    perror("Error: value1 is greater than 256 bytes.");
            return -1; // If size if bigger.
    }

    // Create needed structures.
    char buf[MAX_SIZE];

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
    char * ip_as_addr = inet_ntoa (*(struct in_addr*)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string);

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(0)
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr(ip_as_addr),
            .sin_port = htons(port_as_int)
    };

    // Create socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // Connect to server.
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // Create request.
    char req = 3;
    sendMessage(socket_fd, (char *)&req, 1);

    // Send key.
    sprintf(buf, "%d", key);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Send value1.
    sendMessage(socket_fd, value1, strlen(value1) + 1);

    // Send value2.
    sprintf(buf, "%d", value2);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Send value3.
    sprintf(buf, "%f", value3);
    sendMessage(socket_fd, buf, strlen(buf) + 1)

    // Response from the server.
    if (readLine(socket_fd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while waiting for response from the server.\n");
        return -1;
    }

    // Closing the connection.
    close(socket_fd);

    // Result of the operation.
    return atoi(buf);
}

int delete_key(int key) {
    // Create needed structures.
    char buf[MAX_SIZE];

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
    char * ip_as_addr = inet_ntoa (*(struct in_addr*)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string);

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(0)
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr(ip_as_addr),
            .sin_port = htons(port_as_int)
    };

    // Create socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // Connect to server.
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // Create request.
    char req = 4;
    sendMessage(socket_fd, (char *)&req, 1);

    // Send key.
    sprintf(buf, "%d", key);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Response from the server.
    if (readLine(socket_fd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while waiting for response from the server.\n");
        return -1;
    }

    // Closing the connection.
    close(socket_fd);

    // Result of the operation.
    return atoi(buf);
}

int exist(int key) {
    // Create needed structures.
    char buf[MAX_SIZE];

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
    char * ip_as_addr = inet_ntoa (*(struct in_addr*)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string);

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(0)
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr(ip_as_addr),
            .sin_port = htons(port_as_int)
    };

    // Create socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // Connect to server.
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // Create request.
    char req = 5;
    sendMessage(socket_fd, (char *)&req, 1);

    // Send key.
    sprintf(buf, "%d", key);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Response from the server.
    if (readLine(socket_fd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while waiting for response from the server.\n");
        return -1;
    }

    // Closing the connection.
    close(socket_fd);

    // Result of the operation.
    return atoi(buf);
}

int copy_key(int key1, int key2) {
    // Create needed structures.
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
    char * ip_as_addr = inet_ntoa (*(struct in_addr*)host->h_addr);

    char *port_as_string = getenv("PORT_TUPLAS");
    if (NULL == port_as_string) {
        perror("Error: No está establecida la variable de entorno puerto.");
        return -1;
    }

    int port_as_int = atoi(port_as_string);

    struct sockaddr_in client_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(0)
    };

    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = inet_addr(ip_as_addr), 
            .sin_port = htons(port_as_int) 
    };

    // Create socket.
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // Connect to server.
    int connect_result = connect(socket_fd, (const struct sockaddr *) &server_address, sizeof(server_address));
    if (connect_result < 0) {
        perror("error connecting to server");
    }

    // Create request.
    char req = 6;
    sendMessage(socket_fd, (char *)&req, 1);

    // Send key1.
    sprintf(buf, "%d", key1);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Send key2.
    sprintf(buf, "%d", key2);
    sendMessage(socket_fd, buf, strlen(buf) + 1);

    // Response from the server.
    if (readLine(socket_fd, buf, MAX_SIZE) < 0) {
        fprintf(stderr, "Error: Problem while waiting for response from the server.\n");
        return -1;
    }

    // Closing the connection.
    close(socket_fd);

    // Result of the operation.
    return atoi(buf);
}
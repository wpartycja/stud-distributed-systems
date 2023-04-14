#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

#include "servicios.h" 
#include "mensajes.h"

#define BUF_SIZE    276 // 256 + 4 + 4 + 8 + 4
#define SLEEP_TIME  4

// mutex & conditions to protect message copy
pthread_mutex_t mutex_message = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_server = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_message = PTHREAD_COND_INITIALIZER;

int message_not_copied = true;          

void deal_with_message(struct request *mess){

    struct request message; 

    // copy message to local variable 
    pthread_mutex_lock(&mutex_message);
    message = (*(struct request *) mess);
    message_not_copied = false;
    pthread_cond_signal(&cond_message); 
    pthread_mutex_unlock(&mutex_message);

    // deal with client request and make a response
    // struct response server_response;

    switch(message.operation_id){
	    
	    case 0:
		    pthread_mutex_lock(&mutex_server);
		    init();
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 1:
		    pthread_mutex_lock(&mutex_server);
		    set_value(message.key, message.value1, message.value2, message.value3);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 2:
		    pthread_mutex_lock(&mutex_server);
		    get_value(message.key, message.value1, &message.value2, &message.value3);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 3:
		    pthread_mutex_lock(&mutex_server);
		    modify_value(message.key, message.value1, message.value2, message.value3);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 4:
		    pthread_mutex_lock(&mutex_server);
		    delete_key(message.key);
		    pthread_mutex_unlock(&mutex_server);
		    break;

          case 5:
		    pthread_mutex_lock(&mutex_server);
		    exist(message.key);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 6:
		    pthread_mutex_lock(&mutex_server);
		    copy_key(message.key, message.value2);
		    pthread_mutex_unlock(&mutex_server);
		    break;
		    
        default:
            break;

    }     

    pthread_exit(0); 
}

int main(int argc, char *argv[]) {
    pthread_attr_t thread_attr; // threads attributes
    pthread_t thid; 
    
    if (argc != 2){
        printf("Wrong number of arguments, system requires port number!\n");
        return 1;
    }

    int port = atoi(argv[1]);

    // create needed structures
    char buf[BUF_SIZE];
    struct sockaddr_in server_address = {
            .sin_family = AF_INET,
            .sin_addr.s_addr = htonl(INADDR_ANY),
            .sin_port = htons(port)
    };
    struct sockaddr_in client_address;
    socklen_t client_address_len = sizeof(client_address);


    // create socket
    int socket_fd = socket(
            AF_INET,
            SOCK_STREAM,
            0
    );
    if (socket_fd < 0) {
        perror("error creating socket");
        return 1;
    }

    // bind socket to address
    int bind_result = bind(
            socket_fd,
            (const struct sockaddr *) &server_address,
            sizeof(server_address)
    );
    if (bind_result < 0) {
        perror("error binding socket");
        return 1;
    }

    // put socket in listening mode
    int listen_result = listen(socket_fd, 1);
    if (listen_result < 0) {
        perror("error putting socket in listening mode");
        return 1;
    }

    pthread_mutex_init(&mutex_message, NULL); 
    pthread_cond_init(&cond_message, NULL); 
    pthread_attr_init(&thread_attr);
    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED); // independent threads

    struct request mess;


    // listen for connections
    while (1) {
        int conn_fd = accept(socket_fd, (struct sockaddr*) &client_address, &client_address_len);
        if (conn_fd < 0) {
            perror("error accepting connection");
            return 1;
        }
        
        int bytes_received = (int) recv(conn_fd, buf, sizeof(buf), 0);
        if (bytes_received < 0) {
            perror("error receiving data");
            return 1;
        }
        if (bytes_received == 0) {
            break;
        }
        printf(
            "Received %d bytes from %s:\n%.*s\n\n",
            bytes_received, inet_ntoa(client_address.sin_addr), bytes_received, buf
        );

        memcpy(&mess, buf, sizeof(buf));

        if (bytes_received > 0){
            if (pthread_create(&thid, &thread_attr, (void *) deal_with_message, &mess)== 0) {

                // wait until thread copy message
                pthread_mutex_lock(&mutex_message);
                while (message_not_copied)
                    pthread_cond_wait(&cond_message, &mutex_message); 
                message_not_copied = true;
                pthread_mutex_unlock(&mutex_message);

                // to nice console view
                sleep(SLEEP_TIME);
            }
        }
        
        close(conn_fd);
    } 
} 


#include "mensajes.h"
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
#include <pthread.h> 
#include <stdio.h>
#include "claves.h"

int init(void) {
    mqd_t server_queue; 
    mqd_t client_queue; 

    struct request req;
    struct response res;
    struct mq_attr attr; 
    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());

    // Verify communication errors (client).
    if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
	    perror("init: error with client queue - mq_open");
	    return -1;
    }

    // Verify communication errors (server).
    if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
	    perror("init: error with server queue - mq_open");
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    // Fill request.
    req.operation_id = 0;
    strcpy(req.queue_name, queue_name); 
    
    if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
	    perror("init: error while filling request - mq_send");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
	    perror("init: error while filling request - mq_receive");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);

	    return -1;
    }
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int set_value(int key, char *value1, int value2, double value3) {
    mqd_t server_queue; 
    mqd_t client_queue; 

    struct request req;
    struct response res;
    struct mq_attr attr; 
    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());

    // Verify communication errors (client).
    if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
	    perror("set_value: error with client queue - mq_open");
	    return -1;
    }

    // Verify communication errors (server).
    if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
	    perror("set_value: error with server queue - mq_open");
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    // Fill request.
    req.operation_id = 1;
    strcpy(req.queue_name, queue_name);
    req.key = key;
    strcpy(req.value1, value1);
    req.value2 = value2;
    req.value3 = value3;

    if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
	    perror("set_value: error while filling request - mq_send");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
	    perror("set_value: error while filling request - mq_receive");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);

	    return -1;
    }
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int get_value(int key, char *value1, int *value2, double *value3) {
    mqd_t server_queue; 
    mqd_t client_queue; 

    struct request req;
    struct response res;
    struct mq_attr attr; 
    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());

    // Verify communication errors (client).
    if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
	    perror("set_value: error with client queue - mq_open");
	    return -1;
    }

    // Verify communication errors (server).
    if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
	    perror("set_value: error with server queue - mq_open");
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    // Fill request
    req.operation_id = 2;
    strcpy(req.queue_name, queue_name);
    req.key = key; 

    // Saving response values.
    strcpy(req.value1, value1); 
    req.value2 = *value2; 
    req.value3 = *value3;

    if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
	    perror("set_value: error while filling request - mq_send");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
	    perror("set_value: error while filling request - mq_receive");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);

	    return -1;
    }
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int modify_value(int key, char *value1, int value2, double value3) {
    mqd_t server_queue; 
    mqd_t client_queue; 
    struct request req; 
    struct response res; 
    struct mq_attr attr; 

    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());

    // Verify communication errors (client).
    if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
	    perror("set_value: error with client queue - mq_open");
	    return -1;
    }

    // Verify communication errors (server).
    if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
	    perror("set_value: error with server queue - mq_open");
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    // Fill request.
    req.operation_id = 3;
    strcpy(req.queue_name, queue_name); 
    req.key = key;
    strcpy(req.value1, value1);
    req.value2 = value2;
    req.value3 = value3;

    if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
	    perror("set_value: error while filling request - mq_send");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
	    perror("set_value: error while filling request - mq_receive");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);

	    return -1;
    }

    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int delete_key(int key) {
    mqd_t server_queue; 
    mqd_t client_queue; 
    struct request req;
    struct response res;
    struct mq_attr attr; 

    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());

    // Verify communication errors (client).
    if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
	    perror("set_value: error with client queue - mq_open");
	    return -1;
    }

    // Verify communication errors (server).
    if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
	    perror("set_value: error with server queue - mq_open");
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    // Fill request.
    req.operation_id = 4;
    strcpy(req.queue_name, queue_name);
    req.key = key;

    if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
	    perror("set_value: error while filling request - mq_send");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
	    perror("set_value: error while filling request - mq_receive");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);

	    return -1;
    }
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int exist(int key) {
    mqd_t server_queue; 
    mqd_t client_queue; 
    struct request req;
    struct response res;
    struct mq_attr attr; 

    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());

    // Verify communication errors (client).
    if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
	    perror("set_value: error with client queue - mq_open");
	    return -1;
    }

    // Verify communication errors (server).
    if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
	    perror("set_value: error with server queue - mq_open");
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

     // Fill request.
    req.operation_id = 5;
    strcpy(req.queue_name, queue_name);
    req.key = key;
    
    if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
	    perror("set_value: error while filling request - mq_send");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
	    perror("set_value: error while filling request - mq_receive");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);

	    return -1;
    }
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int copy_key(int key1, int key2) {
    mqd_t server_queue; 
    mqd_t client_queue; 
    struct request req;
    struct response res;
    struct mq_attr attr; 

    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());
    
    // Verify communication errors (client).
    if((client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr)) == -1){
	    perror("set_value: error with client queue - mq_open");
	    return -1;
    }

    // Verify communication errors (server).
    if((server_queue = mq_open("/SERVER", O_WRONLY)) == -1){
	    perror("set_value: error with server queue - mq_open");
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

     // Fill request.
    req.operation_id = 6;
    strcpy(req.queue_name, queue_name);
    req.key = key1;
    req.value2 = key2;

    if((mq_send(server_queue, (const char *) &req, sizeof(req), 0)) == -1){
	    perror("set_value: error while filling request - mq_send");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);
	    
	    return -1;
    }

    if((mq_receive(client_queue, (char*) &res, sizeof(res), 0)) == -1){
	    perror("set_value: error while filling request - mq_receive");
	    mq_close(server_queue);
	    mq_close(client_queue);
	    mq_unlink(queue_name);

	    return -1;
    }
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

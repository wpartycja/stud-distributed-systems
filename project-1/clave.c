#include "mensajes.h"
#include <string.h>
#include <unistd.h>
#include <mqueue.h>
#include <pthread.h> 
#include <stdio.h>
#include "clave.h"

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
    client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr);

    server_queue = mq_open("/SERVER", O_WRONLY); 

    // fill request
    req.operation_id = 0;
    strcpy(req.queue_name, queue_name); 
    mq_send(server_queue, (const char *) &req, sizeof(req), 0);
    mq_receive(client_queue, (char*) &res, sizeof(res), 0);
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

// int set_value(int key, char *value1, int value2, double value3) {
//     mqd_t q_servidor; /* cola de mensajes del proceso servidor */
//     mqd_t q_cliente; /* cola de mensajes para el proceso cliente */ 
//     struct peticion pet; struct respuesta res; struct mq_attr attr; 
//     char queuename[MAXSIZE];

//     attr.mq_maxmsg = 1; 
//     attr.mq_msgsize = sizeof(res);
//     sprintf(queuename, "/Cola-%d", getpid());
//     q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);

//     q_servidor = mq_open("/SERVIDOR", O_WRONLY); 

//     /* se rellena la petición */ //EDITAR
//     pet.codigo_ope = 1; strcpy(pet.q_name, queuename); pet.key = key; strcpy(pet.value1 = value1); pet.value2 = value2; pet.value3 = value3;
//     mq_send(q_servidor, (const char *) &pet, sizeof(pet), 0);
//     mq_receive(q_cliente, (char*) &res, sizeof(res), 0);
    
//     mq_close(q_servidor); 
//     mq_close(q_cliente); 
//     mq_unlink(queuename);

//     return res.resultado;
// }

// int get_value(int key, char *value1, int *value2, double *value3) {
//     mqd_t q_servidor; /* cola de mensajes del proceso servidor */
//     mqd_t q_cliente; /* cola de mensajes para el proceso cliente */ 
//     struct peticion pet; struct respuesta res; struct mq_attr attr; 
//     char queuename[MAXSIZE];

//     attr.mq_maxmsg = 1; 
//     attr.mq_msgsize = sizeof(res);
//     sprintf(queuename, "/Cola-%d", getpid());
//     q_cliente = mq_open(queuename, O_CREAT|O_RDONLY, 0700, &attr);

//     q_servidor = mq_open("/SERVIDOR", O_WRONLY); 

//     /* se rellena la petición */ //EDITAR
//     pet.codigo_ope = 2; strcpy(pet.q_name, queuename); pet.key = key; 
//     // AQUI, NO TENEMOS QUE PASARLE LOS VALORES EN LA PETICION, PORQUE EL GET VALUE LOS RECIBE
//     // TENEMOS QUE ALMACENAR LOS VALORES DE RESPUESTA EN LOS PUNTEROS QUE SE PASAN COMO PARAMETROS
//     pet.value1 = value1; 
//     pet.value2 = value2; 
//     pet.value3 = value3;

//     mq_send(q_servidor, (const char *) &pet, sizeof(pet), 0);
//     mq_receive(q_cliente, (char*) &res, sizeof(res), 0);
    
//     mq_close(q_servidor); 
//     mq_close(q_cliente); 
//     mq_unlink(queuename);

//     return res.resultado;
// }

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
    client_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr);

    server_queue = mq_open("/SERVER", O_WRONLY); 

    // fill request
    req.operation_id = 3;
    strcpy(req.queue_name, queue_name); 
    req.key = key;
    strcpy(req.value1, value1);
    req.value2 = value2;
    req.value3 = value3;

    mq_send(server_queue, (const char *) &req, sizeof(req), 0);
    mq_receive(client_queue, (char*) &res, sizeof(res), 0);
    
    mq_close(server_queue); 
    mq_close(client_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int delete_key(int key) {
    mqd_t server_queue; 
    mqd_t clinet_queue; 
    struct request req;
    struct response res;
    struct mq_attr attr; 

    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());
    clinet_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr);

    server_queue = mq_open("/SERVER", O_WRONLY); 

    // fill request
    req.operation_id = 4;
    strcpy(req.queue_name, queue_name);
    req.key = key;

    mq_send(server_queue, (const char *) &req, sizeof(req), 0);
    mq_receive(clinet_queue, (char*) &res, sizeof(res), 0);
    
    mq_close(server_queue); 
    mq_close(clinet_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int exist(int key) {
    mqd_t server_queue; 
    mqd_t clinet_queue; 
    struct request req;
    struct response res;
    struct mq_attr attr; 

    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());
    clinet_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr);

    server_queue = mq_open("/SERVER", O_WRONLY); 

     // fill request
    req.operation_id = 5;
    strcpy(req.queue_name, queue_name);
    req.key = key;
    
    mq_send(server_queue, (const char *) &req, sizeof(req), 0);
    mq_receive(clinet_queue, (char*) &res, sizeof(res), 0);
    
    mq_close(server_queue); 
    mq_close(clinet_queue); 
    mq_unlink(queue_name);

    return res.result;
}

int copy_key(int key1, int key2) {
    mqd_t server_queue; 
    mqd_t clinet_queue; 
    struct request req;
    struct response res;
    struct mq_attr attr; 

    char queue_name[MAXSIZE];

    attr.mq_maxmsg = 1; 
    attr.mq_msgsize = sizeof(res);
    sprintf(queue_name, "/Queue-%d", getpid());
    clinet_queue = mq_open(queue_name, O_CREAT|O_RDONLY, 0700, &attr);

    server_queue = mq_open("/SERVER", O_WRONLY); 

     // fill request
    req.operation_id = 6;
    strcpy(req.queue_name, queue_name);
    req.key = key1;
    req.value2 = key2;
    mq_send(server_queue, (const char *) &req, sizeof(req), 0);
    mq_receive(clinet_queue, (char*) &res, sizeof(res), 0);
    
    mq_close(server_queue); 
    mq_close(clinet_queue); 
    mq_unlink(queue_name);

    return res.result;
}

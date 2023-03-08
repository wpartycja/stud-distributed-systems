#include "servicios.h" 
#include <mqueue.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdbool.h> 
#include <string.h>
#include "mensajes.h"

/* mutex y variables condicionales para proteger la copia del mensaje*/ 
pthread_mutex_t mutex_mensaje;
int mensaje_no_copiado = true;          
pthread_cond_t cond_mensaje;

void tratar_mensaje(void *mess){
    struct peticion mensaje; /* mensaje local */
    mqd_t q_cliente; /* cola del cliente */
    int resultado; /* resultado de la operación */
    mensaje = (*(struct peticion *) mess);
    /* el thread copia el mensaje a un mensaje local */ 
    pthread_mutex_lock(&mutex_mensaje);
    /* ya se puede despertar al servidor*/ 
    mensaje_no_copiado = false;
    pthread_cond_signal(&cond_mensaje); 
    pthread_mutex_unlock(&mutex_mensaje);

    /* ejecutar la petición del cliente y preparar respuesta */ 
    struct respuesta respuesta_servidor;
    if (mensaje.codigo_ope == 0) //if mensaje.op == 0 para cada id de cada función
        respuesta_servidor.respuesta = init(); //respuesta_servidor.respuesta = ejecutar la función correspondiente
    
   /*  else if (mensaje.codigo_ope == 1)
        respuesta_servidor.respuesta = set_value(mensaje.key, mensaje.value1, mensaje.value2, mensaje.value3)

    else if (mensaje.codigo_ope == 2)
        respuesta_servidor.respuesta = get_value(mensaje.key, mensaje.value1, mensaje.value2, mensaje.value3)
    
    else if (mensaje.codigo_ope == 3)
        respuesta_servidor.respuesta = modify_value(mensaje.key, mensaje.value1, mensaje.value2, mensaje.value3)

    else if (mensaje.codigo_ope == 4)
        respuesta_servidor.respuesta = delete(mensaje.key)
    
    else if (mensaje.codigo_ope == 5)
        respuesta_servidor.respuesta = exist(mensaje.key)
    
    else if (mensaje.codigo_ope == 6)
        respuesta_servidor.respuesta = copy_key(mensaje.key, mensaje.value2) */
        
    /* Se devuelve el resultado al cliente */
    /* Para ello se envía el resultado a su cola */ 
    printf("%s\n", mensaje.q_name);
    q_cliente = mq_open(mensaje.q_name, O_WRONLY); //q_name nombre de la cola
    if (q_cliente == -1)
        perror(“No se puede abrir la cola del cliente”); 
    else {
        mq_send(q_cliente, (const char *) &respuesta_servidor, sizeof(respuesta_servidor), 0);
        mq_close(q_cliente); }
    pthread_exit(0); 
}

int main(void) {
    mqd_t q_servidor; 
    struct peticion mess; /* cola del servidor */
    struct mq_attr q_attr; /* mensaje a recibir */
    pthread_attr_t t_attr; /* atributos de la cola */
    pthread_t thid; /* atributos de los threads */
    
    q_attr.mq_maxmsg = 10;
    q_attr.mq_msgsize = sizeof(struct peticion);
    q_servidor = mq_open("/SERVIDOR", O_CREAT|O_RDONLY, 0700, &q_attr); 
    if (q_servidor == -1) {
        perror(”No se puede crear la cola de servidor”);
        return 1; 
    }
    pthread_mutex_init(&mutex_mensaje, NULL); 
    pthread_cond_init(&cond_mensaje, NULL); 
    pthread_attr_init(&t_attr);
    /* atributos de los threads, threads independientes */ 
    pthread_attr_setdetachstate(&t_attr, PTHREAD_CREATE_DETACHED);

    while (true) {
        mq_receive(q_servidor, (char *) &mess, sizeof(struct peticion), 0);
        if (pthread_create(&thid, &t_attr, tratar_mensaje, (void *)&mess)== 0) {
            /* se espera a que el thread copie el mensaje - Sección crítica*/ 
            pthread_mutex_lock(&mutex_mensaje);
            while (mensaje_no_copiado)
                pthread_cond_wait(&cond_mensaje, &mutex_mensaje); 
            mensaje_no_copiado = true;
            pthread_mutex_unlock(&mutex_mensaje);
        } /*IF */
    } /* FIN while */
} /* Fin main */





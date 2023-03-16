#include "servicios.h" 
#include <mqueue.h>
#include <pthread.h> 
#include <stdio.h> 
#include <stdbool.h> 
#include <string.h>
#include "mensajes.h"

// mutex & conditions to protect message copy
pthread_mutex_t mutex_message = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_server = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond_message = PTHREAD_COND_INITIALIZER;

int message_not_copied = true;          

void deal_with_message(struct request *mess){
    struct request message; 
    mqd_t client_queue;
    //int result; // operation result

    // copy message to local variable 
    pthread_mutex_lock(&mutex_message);
    message = (*(struct request *) mess);
    message_not_copied = false;
    pthread_cond_signal(&cond_message); 
    pthread_mutex_unlock(&mutex_message);

    // // deal with client request and make a response
    struct response server_response;

    printf("%d\n", server_response.result);

    switch(message.operation_id){
	    
	    case 0:
		    pthread_mutex_lock(&mutex_server);
		    server_response.result = init();
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 1:
		    pthread_mutex_lock(&mutex_server);
		    //server_response.result = set_value(message.key, message.value1, message.value2, message.value3);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 2:
		    pthread_mutex_lock(&mutex_server);
		    server_response.result = get_value(message.key, message.value1, message.value2, message.value3);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 3:
		    pthread_mutex_lock(&mutex_server);
		    server_response.result = modify_value(message.key, message.value1, message.value2, message.value3);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 4:
		    pthread_mutex_lock(&mutex_server);
		    server_response.result = delete_key(message.key);
		    pthread_mutex_unlock(&mutex_server);
		    break;

          case 5:
		    pthread_mutex_lock(&mutex_server);
		    server_response.result = exist(message.key);
		    pthread_mutex_unlock(&mutex_server);
		    break;

	    case 6:
		    pthread_mutex_lock(&mutex_server);
		    //server_response.result = copy_key(message.key, message.value2);
		    pthread_mutex_unlock(&mutex_server);
		    break;
		    
        default:
            break;

    }     
        
    /* Se devuelve el resultado al cliente */
    /* Para ello se envía el resultado a su cola */ 
    printf("%s\n", message.queue_name);
    printf("%d\n", server_response.result);
    client_queue = mq_open(message.queue_name, O_WRONLY); //q_name - name of the queue, O_WRONLY - queue for sending

    if (client_queue == -1)
        perror("Error in opening client queue"); 
    else {
        mq_send(client_queue, (const char *) &server_response, sizeof(server_response), 0);
        mq_close(client_queue); }

    pthread_exit(0); 
}

int main(void) {
    mqd_t server_queue; 
    struct request mess; // message to receive
    struct mq_attr queue_attr; // queue attributes
    pthread_attr_t thread_attr; // threads attributes
    pthread_t thid; 
    
    queue_attr.mq_maxmsg = 10; // maximum number of messages
    queue_attr.mq_msgsize = sizeof(struct request); // maximum size
    server_queue = mq_open("/SERVER", O_CREAT|O_RDONLY, 0700, &queue_attr); // create queue for receive messages
    if (server_queue == -1) {
        perror("Error in creating server queue");
        return 1; 
    }

    pthread_mutex_init(&mutex_message, NULL); 
    pthread_cond_init(&cond_message, NULL); 
    pthread_attr_init(&thread_attr);

    pthread_attr_setdetachstate(&thread_attr, PTHREAD_CREATE_DETACHED); // independent threads

    while (true) {
        mq_receive(server_queue, (char *) &mess, sizeof(struct request), 0);

        if (pthread_create(&thid, &thread_attr, (void *) deal_with_message, &mess)== 0) {

            // wait until thread copy message
            pthread_mutex_lock(&mutex_message);
            while (message_not_copied)
                pthread_cond_wait(&cond_message, &mutex_message); 
            message_not_copied = true;
            pthread_mutex_unlock(&mutex_message);
        } 
    } 
} 


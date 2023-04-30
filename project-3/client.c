#include "claves.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 2

// beautiful way to initialize mutex :)
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER; 
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int sleep_;


void client_correct(); // client that does not produce errors

void client_errors(); // client that produces errors

int main(){
    //-------------------- INIT -------------------- 
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Initialize the service of elements key, value1, value2 and value3.
    int res = init();
    printf("Repuesta init(): %d\n", res); 

    int j;
	pthread_attr_t attr; 
	pthread_t thid[NUM_THREADS];  // number of threads

	pthread_attr_init(&attr); // initialize attr with default attributes


    // create threads
    if (pthread_create(&thid[0], NULL, (void *) client_correct, NULL) == -1){
        printf("Error al crear los threads\n");
        exit(0);
    }

    // wait for threads to finish
    pthread_mutex_lock(&lock);
    sleep_ = 1; 
    while (sleep_) pthread_cond_wait(&cond, &lock); // wait for signal
    pthread_mutex_unlock(&lock); // unlock mutex

    // create threads
    if (pthread_create(&thid[1], NULL, (void *) client_errors, NULL) == -1){
    printf("Error al crear los threadsc");
    exit(0);
    }

    // wait for threads to finish
    pthread_mutex_lock(&lock);
    sleep_ = 1;
    while (sleep_) pthread_cond_wait(&cond, &lock); // wait for signal
    pthread_mutex_unlock(&lock); // unlock mutex

    // wait for threads to finish
	for (j = 0; j < NUM_THREADS; j++)
        // pthread_join() waits for the thread specified by thid to terminate.
		pthread_join(thid[j], NULL);

    // destroy mutex
	pthread_mutex_destroy(&lock);

	exit(0);// exit the program BIEN???
 
}

// client that does not produce errors
void client_correct(){
    
    pthread_mutex_lock(&lock); 
    sleep_ = 0;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    // -------------------- SET_VALUE --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    int res1 = set_value(1, "abcd", 2, 3.0);
    printf("Respuesta SET_VALUE 1 correct: %d\n", res1); 
    int res2 = set_value(2, "efgh", 4, 5.0);
    printf("Respuesta SET_VALUE 2 correct: %d\n", res2); 
    int res3 = set_value(3, "ijkl", 6, 7.0);
    printf("Respuesta SET_VALUE 3 correct: %d\n", res3); 

    // -------------------- GET_VALUE --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    char val1[256];
    int val2; 
    double val3;
    
    // Getting values of tuples - achieved successfully.
    int res4 = get_value(1, val1, &val2, &val3);
    printf("Respuesta GET_VALUE 3 correct: %d\n", res4); 
    printf("Respuesta GET_VALUE 3 - value1: %s\n", val1);
    printf("Respuesta GET_VALUE 3 - value2: %d\n", val2);
    printf("Respuesta GET_VALUE 3 - value3: %f\n", val3);

    // -------------------- MODIFY_VALUE --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Modifying values of tuples - achieved successfully.
    int res5 = modify_value(2, "mnop", 10, 11.0); 
    printf("Respuesta MODIFY_VALUE correct: %d\n", res5);

    // -------------------- DELETE_KEY --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Deleting tuple with a specific key value - achieved successfully.
    int res6 = delete_key(1);
    printf("Respuesta DELETE_KEY correct: %d\n", res6); 

    // -------------------- EXIST -------------------
    /*0 KEY EXIST, 
      1 KEY DOES NOT EXIST,
     -1 if ERROR   */ 

    // Verifying existance of a tuple with a specific key value - achieved successfully.
    int res7 = exist(2);
    printf("Respuesta EXIST correct: %d\n", res7); 

    // -------------------- COPY_KEY --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Copying the contents from one tuple to another - achieved successfully.
    int res8 = copy_key(2, 3);
    printf("Respuesta COPY_KEY 1 correct: %d\n", res8); 

    // Copying the contents from one tuple to another - achieved successfully: key 2 doesnt exist.
    int res9 = copy_key(3, 4);
    printf("Respuesta COPY_KEY 2 correct: %d\n", res9); 
}

// client that produces errors
void client_errors(){

    pthread_mutex_lock(&lock);
    sleep_ = 0;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    // -------------------- SET_VALUE --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Inserting tuples - error: value1 is longer than 256 bytes.
    int res10 = set_value(4, "The Way the Light Reflects by Richard Siken. The paint doesn’t move the way the light reflects so what’s there to be faithful to? I am faithful to you darling. I say it to the paint. The bird floats in the unfinished sky with nothing to hold it.The man stands the day shines. His insides and his outsides kept apart with an imaginary line— thick and rude and imaginary because there is no separation fallacy of the local body paint on paint. I have my body and you have yours. Believe it if you can. Negative space is silly. When you bang on the wall you have to remember you’re on both sides of it already but go ahead yell at yourself. Some people don’t understand anything. They see the man but not the light they see the field but not the varnish. There is no light in the paint so how can you argue with them? They are probably right anyway. I paint in his face and I paint it out again. There is a question I am afraid to ask: to supply the world with what?", 8, 9.0);
    printf("Respuesta SET_VALUE 1 errors: %d\n", res10); 

    // Inserting tuples - error: previously existing key.
    set_value(1, "qwert", 56, 74.0);
    int res11 = set_value(1, "qwesdfrt", 356, 741.0);
    printf("Respuesta SET_VALUE 2 errors: %d\n", res11); 
    
    // -------------------- GET_VALUE --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    char val1[256];
    int val2;
    double val3; 

    // Getting values of tuples - error: key doesnt exist.
    int res12 = get_value(10, val1, &val2, &val3);
    printf("Respuesta GET_VALUE errors: %d\n", res12); 
    
    // -------------------- MODIFY_VALUE --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Modifying values of tuples - error: key doesnt exist.
    int res13 = modify_value(10, "qrst", 12, 13.0);
    printf("Respuesta MODIFY_VALUE 1 errors: %d\n", res13); 

    // Modifying values of tuples - error: value1 longer than 256 bytes.
    int res14 = modify_value(3, "The Way the Light Reflects by Richard Siken. The paint doesn’t move the way the light reflects so what’s there to be faithful to? I am faithful to you darling. I say it to the paint. The bird floats in the unfinished sky with nothing to hold it.The man stands the day shines. His insides and his outsides kept apart with an imaginary line— thick and rude and imaginary because there is no separation fallacy of the local body paint on paint. I have my body and you have yours. Believe it if you can. Negative space is silly. When you bang on the wall you have to remember you’re on both sides of it already but go ahead yell at yourself. Some people don’t understand anything. They see the man but not the light they see the field but not the varnish. There is no light in the paint so how can you argue with them? They are probably right anyway. I paint in his face and I paint it out again. There is a question I am afraid to ask: to supply the world with what?", 123, 34.5);
    printf("Respuesta MODIFY_VALUE 1 errors: %d\n", res14); 

    // -------------------- DELETE_KEY --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Deleting tuple with a specific key value - error: key doesnt exist.
    int res15= delete_key(11);
    printf("Respuesta DELETE_KEY errors: %d\n", res15);
    
    // -------------------- EXIST --------------------
    /*0 KEY EXIST, 
      1 KEY DOES NOT EXIST,
     -1 if ERROR   */

    // Verifying existance of a tuple with a specific key value - achieved successfully.
    int res16 = exist(12);
    printf("Respuesta EXIST errors: %d\n", res16);
	   
    // -------------------- COPY_KEY --------------------
    /* 0 if SUCCESS 
      -1 if ERROR  */

    // Copying the contents from one tuple to another - error: key 1 doesnt exist.
    int res17 = copy_key(13, 14);
    printf("Respuesta COPY_KEY errors: %d\n", res17);
}

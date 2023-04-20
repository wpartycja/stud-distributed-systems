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


void client_correct();

void client_errors();

int main(){
    //-------------------- INIT -------------------- 
    // Initialize the service of elements key, value1, value2 and value3.
    init();

    int j;
	pthread_attr_t attr;
	pthread_t thid[NUM_THREADS];  // number of threads

	pthread_attr_init(&attr);


    if (pthread_create(&thid[0], NULL, (void *) client_correct, NULL) == -1){
        printf("Error al crear los threads\n");
        exit(0);
    }

    pthread_mutex_lock(&lock);
    sleep_ = 1;
    while (sleep_) pthread_cond_wait(&cond, &lock);
    pthread_mutex_unlock(&lock);


    if (pthread_create(&thid[1], NULL, (void *) client_errors, NULL) == -1){
    printf("Error al crear los threads\n");
    exit(0);
    }

    pthread_mutex_lock(&lock);
    sleep_ = 1;
    while (sleep_) pthread_cond_wait(&cond, &lock);
    pthread_mutex_unlock(&lock);

	for (j = 0; j < NUM_THREADS; j++)
		pthread_join(thid[j], NULL);

	pthread_mutex_destroy(&lock);

	exit(0);
}


void client_correct(){

    pthread_mutex_lock(&lock);
    sleep_ = 0;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    // -------------------- SET_VALUE --------------------
    set_value(1, "abcd", 2, 3.0);
    set_value(2, "efgh", 4, 5.0);   
    set_value(3, "ijkl", 6, 7.0);

    // -------------------- GET_VALUE --------------------
    char val1[256];
    int *val2 = malloc(sizeof(int));  
    double *val3 = malloc(sizeof(double));  
    
    // Getting values of tuples - achieved successfully.
    get_value(1, val1, val2, val3);

    // -------------------- MODIFY_VALUE --------------------
    // Modifying values of tuples - achieved successfully.
    modify_value(2, "mnop", 10, 11.0);

    // -------------------- DELETE_KEY --------------------
    // Deleting tuple with a specific key value - achieved successfully.
    delete_key(1);

    // -------------------- EXIST --------------------
    // Verifying existance of a tuple with a specific key value - achieved successfully.
    exist(2);

    // -------------------- COPY_KEY --------------------
    // Copying the contents from one tuple to another - achieved successfully.
    copy_key(2, 3);
    // Copying the contents from one tuple to another - achieved successfully: key 2 doesnt exist.
    copy_key(3, 4);
}

void client_errors(){

    pthread_mutex_lock(&lock);
    sleep_ = 0;
    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&lock);

    // -------------------- SET_VALUE --------------------
    // Inserting tuples - error: value1 is longer than 256 bytes.
    set_value(4, "The Way the Light Reflects by Richard Siken. The paint doesn’t move the way the light reflects so what’s there to be faithful to? I am faithful to you darling. I say it to the paint. The bird floats in the unfinished sky with nothing to hold it.The man stands the day shines. His insides and his outsides kept apart with an imaginary line— thick and rude and imaginary because there is no separation fallacy of the local body paint on paint. I have my body and you have yours. Believe it if you can. Negative space is silly. When you bang on the wall you have to remember you’re on both sides of it already but go ahead yell at yourself. Some people don’t understand anything. They see the man but not the light they see the field but not the varnish. There is no light in the paint so how can you argue with them? They are probably right anyway. I paint in his face and I paint it out again. There is a question I am afraid to ask: to supply the world with what?", 8, 9.0);

    // Inserting tuples - error: previously existing key.
    set_value(1, "qwert", 56, 74.0);
    
    // -------------------- GET_VALUE --------------------
    char val1[256];
    int *val2 = malloc(sizeof(int));  
    double *val3 = malloc(sizeof(double));  

    // Getting values of tuples - error: key doesnt exist.
    get_value(10, val1, val2, val3);

    free(val2);
    free(val3);
    
    // -------------------- MODIFY_VALUE --------------------
    // Modifying values of tuples - error: key doesnt exist.
    modify_value(10, "qrst", 12, 13.0);
    // Modifying values of tuples - error: value1 longer than 256 bytes.
    modify_value(3, "The Way the Light Reflects by Richard Siken. The paint doesn’t move the way the light reflects so what’s there to be faithful to? I am faithful to you darling. I say it to the paint. The bird floats in the unfinished sky with nothing to hold it.The man stands the day shines. His insides and his outsides kept apart with an imaginary line— thick and rude and imaginary because there is no separation fallacy of the local body paint on paint. I have my body and you have yours. Believe it if you can. Negative space is silly. When you bang on the wall you have to remember you’re on both sides of it already but go ahead yell at yourself. Some people don’t understand anything. They see the man but not the light they see the field but not the varnish. There is no light in the paint so how can you argue with them? They are probably right anyway. I paint in his face and I paint it out again. There is a question I am afraid to ask: to supply the world with what?", 123, 34.5);

    // -------------------- DELETE_KEY --------------------
    // Deleting tuple with a specific key value - error: key doesnt exist.
    delete_key(11);
    
    // -------------------- EXIST --------------------
    // Verifying existance of a tuple with a specific key value - achieved successfully.
    exist(12);
	   
    // -------------------- COPY_KEY --------------------
    // Copying the contents from one tuple to another - error: key 1 doesnt exist.
    copy_key(1, 3);
}
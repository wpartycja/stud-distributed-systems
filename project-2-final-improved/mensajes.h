#ifndef _MENSAJES_H
#define _MENSAJES_H 

#define MAXSIZE 256

struct response {
    int result; 
    char value1[MAXSIZE];
    int value2;
    double value3;
};


struct request {
    int operation_id;
    int key;
    char value1[MAXSIZE];
    int value2; // can be used as key2 in copy_key() func
    double value3; 

};

#endif
#ifndef _MENSAJES_H //si no esta definido se define
#define _MENSAJES_H 

#define MAXSIZE 256
struct respuesta {
    int resultado; 
    char value1[MAXSIZE];
    int value2;
    double value3;
};
struct peticion {
    int codigo_ope;
    char q_name[MAXSIZE]; 
    int key;
    char value1[MAXSIZE];
    int value2; //se puede utilizar como key2
    double value3; 

};

#endif
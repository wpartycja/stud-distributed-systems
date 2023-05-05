#ifndef _CLAVES_H
#define _CLAVES_H 
#include <stddef.h>
#include <unistd.h>

//--
int init(); 

int set_value(int key, char *value1, int value2, double value3);

int get_value(int key, char *value1, int *value2, double *value3);

int modify_value(int key, char *value1, int value2, double value3);

int delete_key(int key);

int exist(int key);

int copy_key(int key1, int key2); 

//--
// Funciones auxiliares
int sendMessage(int socket, char *buffer, int len);
int recvMessage(int socket, char *buffer, int len);
ssize_t readLine(int fd, void *buffer, size_t n);

#endif

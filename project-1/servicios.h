//cabeceras
#ifndef _SERVICIOS_H //si no esta definido se define
#define _SERVICIOS_H 

struct tuple {
    int clave;
    char value1[256];
    int value2;
    double value3;
};


int init();

int set_value(int key, char *value1, int value2, double value3);

int get_value(int key, char *value1, int *value2, double *value3);

int modify_value(int key, char *value1, int value2, double value3);

int delete_key(int key);

int exist(int key);

int copy_key(int key1, int key2);

#endif

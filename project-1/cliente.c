#include "clave.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    exist(1);
    copy_key(1, 3);
    set_value(2, "lalal", 5, 6);
    

    char val1[256];
    int *val2 = malloc(sizeof(int));  
    double *val3 = malloc(sizeof(double));  

    get_value(1, val1, val2, val3);

    return 0;
    }

#include "claves.h"
#include <stdio.h>
#include <stdlib.h>

int main(){
    // Initialize the service of elements key, value1, value2 and value3.
    init();

    // Inserting tuples. 
    set_value(1, "abcd", 2, 3.0);
    set_value(2, "efgh", 4, 5.0);   
    set_value(3, "ijkl", 6, 7.0);

    // Inserting tuples - error: previously existing key.
    set_value(1, "qwert", 56, 74.0);

    char val1[256];
    int *val2 = malloc(sizeof(int));  
    double *val3 = malloc(sizeof(double));  

    get_value(1, val1, val2, val3);

    modify_value(2, "mnop", 8, 9.0);

    delete_key(1);

    exist(2);

    copy_key(1, 3);

    return 0;
}

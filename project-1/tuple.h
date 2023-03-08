#define MAX_STRING_LEN 256

typedef struct {
    int key;
    char value1[MAX_STRING_LEN];
    int value2;
    double value3;
} tuple;

typedef struct {
    long mtype;
    tuple tuple;
} message;

int server_queue, client_queue;

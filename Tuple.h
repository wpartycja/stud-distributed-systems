#define MAX_STRING_LEN 256

typedef struct {
    int key;
    char value1[MAX_STRING_LEN];
    int value2;
    double value3;
} Tuple;

typedef struct {
    long mtype;
    Tuple tuple;
} Message;

int server_queue, client_queue;

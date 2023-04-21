const MAXSIZE = 256;

struct response {
    int result; 
    string value1<MAXSIZE>;
    int value2;
    double value3;
};

program PROJECT {
    version PROJECT_VER {
        int init() = 0;
        int set_value(int key, string value1<MAXSIZE>, int value2, double value3) = 1;
        response get_value(int key) = 2 ;
        int modify_value(int key, string value1<MAXSIZE>, int value2, double value3) = 3;
        int delete_key(int key) = 4;
        int exist(int key) = 5;
        int copy_key(int key1, int key2) = 6;
    } = 1;
} = 99;
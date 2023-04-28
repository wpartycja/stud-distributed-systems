const MAXSIZE = 256;

struct response {
    int result; 
    string value1<MAXSIZE>;
    int value2;
    double value3;
};

program PROJECT_RPC {
    version PROJECT_VER {
        int INIT() = 0;
        int SET_VALUE(int key, string value1<MAXSIZE>, int value2, double value3) = 1;
        struct response GET_VALUE(int key) = 2;
        int MODIFY_VALUE(int key, string value1<MAXSIZE>, int value2, double value3) = 3;
        int DELETE_KEY(int key) = 4;
        int EXIST(int key) = 5;
        int COPY_KEY(int key1, int key2) = 6;
    } = 1;
} = 99;
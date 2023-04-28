#include "project_rpc.h"
#include "claves.h"


#define MAX_SIZE    256
char *host; // @TODO should change it?

int checkenv()
{
    host = getenv("IP_TUPLAS");

    if (host == NULL)
    {
        perror("\nEnvironment variables not defined\n");
        return -1;
    }
    return 0;
}


int init(){
    int environment = checkenv();
    if (environment < 0)
    {
        return -1; 
    }


    CLIENT *clnt;
    enum clnt_stat retval;
    int result;

    clnt = clnt_create(host, PROJECT_RPC, PROJECT_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

    retval = init_1(&result, clnt);
	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}
    
    clnt_destroy(clnt);
    return result;
}

int set_value(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
    enum clnt_stat retval;
	int result;


    clnt = clnt_create(host, PROJECT_RPC, PROJECT_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

	retval = set_value_1(key, value1, value2, value3, &result, clnt);
	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

    clnt_destroy(clnt);
    return result;
}

int get_value(int key, char *value1, int *value2, double *value3){
    CLIENT *clnt;
    enum clnt_stat retval;

	struct response result;
    result.value1 = malloc(256);


    clnt = clnt_create(host, PROJECT_RPC, PROJECT_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

	retval = get_value_1(key, &result, clnt);
	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

    strcpy(value1, result.value1);
    *value2 = result.value2;
    *value3 = result.value3;

    clnt_destroy(clnt);
    return 0;
}

int modify_value(int key, char *value1, int value2, double value3){

    CLIENT *clnt;
    enum clnt_stat retval;
	int result;

     clnt = clnt_create(host, PROJECT_RPC, PROJECT_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

	retval = modify_value_1(key, value1, value2, value3, &result, clnt);
	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

    clnt_destroy(clnt);
    return result;
}

int delete_key(int key){
    CLIENT *clnt;
    enum clnt_stat retval;
    int result;

    clnt = clnt_create(host, PROJECT_RPC, PROJECT_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

    retval = delete_key_1(key, &result, clnt);
    if (retval != RPC_SUCCESS)
    {
        clnt_pcreateerror(host);
    }

    clnt_destroy(clnt);
    return result;

}

int exist(int key)
{
    CLIENT *clnt;
    enum clnt_stat retval;
    int result;

    clnt = clnt_create(host, PROJECT_RPC, PROJECT_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

    retval = exist_1(key, &result, clnt);
    if (retval != RPC_SUCCESS)
    {
        clnt_pcreateerror(host);
    }

    clnt_destroy(clnt);
    return result;
}

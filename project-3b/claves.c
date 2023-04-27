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
    printf("dupa");

    clnt_destroy(clnt);
    return result;
}

int set_value(int key, char *value1, int value2, double value3){
    CLIENT *clnt;
    enum clnt_stat retval;
	int result;
	int set_value_1_key;
	char *set_value_1_value1;
	int set_value_1_value2;
	double set_value_1_value3;

    clnt = clnt_create(host, PROJECT_RPC, PROJECT_VER, "udp");
    if (clnt == NULL)
    {
        clnt_pcreateerror(host);
        exit(1);
    }

	retval = set_value_1(set_value_1_key, set_value_1_value1, set_value_1_value2, set_value_1_value3, &result, clnt);
	if (retval != RPC_SUCCESS) {
		clnt_perror (clnt, "call failed");
	}

    clnt_destroy(clnt);
    return result;
}


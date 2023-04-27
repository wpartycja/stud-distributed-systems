#include "servicios.h"
#include "project_rpc.h"

#define MAX_MSG_SIZE 1024
#define DIR_NAME "FilesPractice3"
#define FILE_TYPE ".txt"
#define MAX_SIZE 256

pthread_mutex_t mutex_server = PTHREAD_MUTEX_INITIALIZER;
 
bool_t
init_1_svc(int *result, struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex_server);
	init();
	pthread_mutex_unlock(&mutex_server); 

	return TRUE;
}

bool_t
set_value_1_svc(int key, char *value1, int value2, double value3, int *result,  struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex_server);
	set_value(key, value1, value2, value3);
	pthread_mutex_unlock(&mutex_server); 

	return TRUE;
}

bool_t
get_value_1_svc(int key, response *result,  struct svc_req *rqstp)
{

	pthread_mutex_lock(&mutex_server);
	modify_value(key, result->value1, result->value2, result->value3);
	pthread_mutex_unlock(&mutex_server);

	return TRUE;
}

bool_t
modify_value_1_svc(int key, char *value1, int value2, double value3, int *result,  struct svc_req *rqstp)
{

	pthread_mutex_lock(&mutex_server);
	modify_value(key, value1, value2, value3);
	pthread_mutex_unlock(&mutex_server);

	return TRUE;
}

bool_t
delete_key_1_svc(int key, int *result,  struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex_server);
	delete_key(key);
	pthread_mutex_unlock(&mutex_server);
	
	return TRUE;
}

bool_t
exist_1_svc(int key, int *result,  struct svc_req *rqstp)
{

	pthread_mutex_lock(&mutex_server);
	exist(key);
	pthread_mutex_unlock(&mutex_server);

	return TRUE;
}

bool_t
copy_key_1_svc(int key1, int key2, int *result,  struct svc_req *rqstp)
{
	pthread_mutex_lock(&mutex_server);
	copy_key(key1, key2);
	pthread_mutex_unlock(&mutex_server);
	
	return TRUE;
}

int
project_rpc_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}

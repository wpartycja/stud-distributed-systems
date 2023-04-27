/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include <memory.h> /* for memset */
#include "project_rpc.h"

/* Default timeout can be changed using clnt_control() */
static struct timeval TIMEOUT = { 25, 0 };

enum clnt_stat 
init_1(int *clnt_res, CLIENT *clnt)
{
	 return (clnt_call (clnt, INIT, (xdrproc_t) xdr_void, (caddr_t) NULL,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));

}

enum clnt_stat 
set_value_1(int key, char *value1, int value2, double value3, int *clnt_res,  CLIENT *clnt)
{
	set_value_1_argument arg;
	arg.key = key;
	arg.value1 = value1;
	arg.value2 = value2;
	arg.value3 = value3;
	return (clnt_call (clnt, SET_VALUE, (xdrproc_t) xdr_set_value_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
get_value_1(int key, response *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, GET_VALUE,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_response, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
modify_value_1(int key, char *value1, int value2, double value3, int *clnt_res,  CLIENT *clnt)
{
	modify_value_1_argument arg;
	arg.key = key;
	arg.value1 = value1;
	arg.value2 = value2;
	arg.value3 = value3;
	return (clnt_call (clnt, MODIFY_VALUE, (xdrproc_t) xdr_modify_value_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
delete_key_1(int key, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, DELETE_KEY,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
exist_1(int key, int *clnt_res,  CLIENT *clnt)
{
	return (clnt_call(clnt, EXIST,
		(xdrproc_t) xdr_int, (caddr_t) &key,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

enum clnt_stat 
copy_key_1(int key1, int key2, int *clnt_res,  CLIENT *clnt)
{
	copy_key_1_argument arg;
	arg.key1 = key1;
	arg.key2 = key2;
	return (clnt_call (clnt, COPY_KEY, (xdrproc_t) xdr_copy_key_1_argument, (caddr_t) &arg,
		(xdrproc_t) xdr_int, (caddr_t) clnt_res,
		TIMEOUT));
}

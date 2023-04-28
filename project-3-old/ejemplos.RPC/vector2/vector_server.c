/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "vector.h"

bool_t
sumar_1_svc(t_vector v, int *result,  struct svc_req *rqstp)
{
	bool_t retval;

	/*
	 * insert server code here
	 */
	int i;

	*result=0;
        for (i=0;i<v.t_vector_len;i++)
          *result = *result + v.t_vector_val[i];


	return retval;
}

int
vector_1_freeresult (SVCXPRT *transp, xdrproc_t xdr_result, caddr_t result)
{
	xdr_free (xdr_result, result);

	/*
	 * Insert additional freeing code here, if needed
	 */

	return 1;
}
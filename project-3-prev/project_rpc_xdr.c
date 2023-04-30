/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "project_rpc.h"

bool_t
xdr_response (XDR *xdrs, response *objp)
{
	register int32_t *buf;

	 if (!xdr_int (xdrs, &objp->result))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->value1, MAXSIZE))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->value2))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->value3))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_set_value_1_argument (XDR *xdrs, set_value_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->key))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->value1, MAXSIZE))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->value2))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->value3))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_modify_value_1_argument (XDR *xdrs, modify_value_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->key))
		 return FALSE;
	 if (!xdr_string (xdrs, &objp->value1, MAXSIZE))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->value2))
		 return FALSE;
	 if (!xdr_double (xdrs, &objp->value3))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_copy_key_1_argument (XDR *xdrs, copy_key_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->key1))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->key2))
		 return FALSE;
	return TRUE;
}

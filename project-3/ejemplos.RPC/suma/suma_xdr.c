/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#include "suma.h"

bool_t
xdr_suma_1_argument (XDR *xdrs, suma_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->b))
		 return FALSE;
	return TRUE;
}

bool_t
xdr_resta_1_argument (XDR *xdrs, resta_1_argument *objp)
{
	 if (!xdr_int (xdrs, &objp->a))
		 return FALSE;
	 if (!xdr_int (xdrs, &objp->b))
		 return FALSE;
	return TRUE;
}

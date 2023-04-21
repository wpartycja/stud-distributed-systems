/*
 * Please do not edit this file.
 * It was generated using rpcgen.
 */

#ifndef _PROJECT3_H_RPCGEN
#define _PROJECT3_H_RPCGEN

#include <rpc/rpc.h>

#include <pthread.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MAXSIZE 256

struct response {
	int result;
	char *value1;
	int value2;
	double value3;
};
typedef struct response response;

struct set_value_1_argument {
	int key;
	char *value1;
	int value2;
	double value3;
};
typedef struct set_value_1_argument set_value_1_argument;

struct modify_value_1_argument {
	int key;
	char *value1;
	int value2;
	double value3;
};
typedef struct modify_value_1_argument modify_value_1_argument;

struct copy_key_1_argument {
	int key1;
	int key2;
};
typedef struct copy_key_1_argument copy_key_1_argument;

#define PROJECT 99
#define PROJECT_VER 1

#if defined(__STDC__) || defined(__cplusplus)
#define init 0
extern  enum clnt_stat init_1(int *, CLIENT *);
extern  bool_t init_1_svc(int *, struct svc_req *);
#define set_value 1
extern  enum clnt_stat set_value_1(int , char *, int , double , int *, CLIENT *);
extern  bool_t set_value_1_svc(int , char *, int , double , int *, struct svc_req *);
#define get_value 2
extern  enum clnt_stat get_value_1(int , response *, CLIENT *);
extern  bool_t get_value_1_svc(int , response *, struct svc_req *);
#define modify_value 3
extern  enum clnt_stat modify_value_1(int , char *, int , double , int *, CLIENT *);
extern  bool_t modify_value_1_svc(int , char *, int , double , int *, struct svc_req *);
#define delete_key 4
extern  enum clnt_stat delete_key_1(int , int *, CLIENT *);
extern  bool_t delete_key_1_svc(int , int *, struct svc_req *);
#define exist 5
extern  enum clnt_stat exist_1(int , int *, CLIENT *);
extern  bool_t exist_1_svc(int , int *, struct svc_req *);
#define copy_key 6
extern  enum clnt_stat copy_key_1(int , int , int *, CLIENT *);
extern  bool_t copy_key_1_svc(int , int , int *, struct svc_req *);
extern int project_1_freeresult (SVCXPRT *, xdrproc_t, caddr_t);

#else /* K&R C */
#define init 0
extern  enum clnt_stat init_1();
extern  bool_t init_1_svc();
#define set_value 1
extern  enum clnt_stat set_value_1();
extern  bool_t set_value_1_svc();
#define get_value 2
extern  enum clnt_stat get_value_1();
extern  bool_t get_value_1_svc();
#define modify_value 3
extern  enum clnt_stat modify_value_1();
extern  bool_t modify_value_1_svc();
#define delete_key 4
extern  enum clnt_stat delete_key_1();
extern  bool_t delete_key_1_svc();
#define exist 5
extern  enum clnt_stat exist_1();
extern  bool_t exist_1_svc();
#define copy_key 6
extern  enum clnt_stat copy_key_1();
extern  bool_t copy_key_1_svc();
extern int project_1_freeresult ();
#endif /* K&R C */

/* the xdr functions */

#if defined(__STDC__) || defined(__cplusplus)
extern  bool_t xdr_response (XDR *, response*);
extern  bool_t xdr_set_value_1_argument (XDR *, set_value_1_argument*);
extern  bool_t xdr_modify_value_1_argument (XDR *, modify_value_1_argument*);
extern  bool_t xdr_copy_key_1_argument (XDR *, copy_key_1_argument*);

#else /* K&R C */
extern bool_t xdr_response ();
extern bool_t xdr_set_value_1_argument ();
extern bool_t xdr_modify_value_1_argument ();
extern bool_t xdr_copy_key_1_argument ();

#endif /* K&R C */

#ifdef __cplusplus
}
#endif

#endif /* !_PROJECT3_H_RPCGEN */

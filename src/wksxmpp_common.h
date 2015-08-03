#ifndef _WKS_XMPP_COMMON_
#define _WKS_XMPP_COMMON_

#include <pthread.h>

#include "strophe.h"

typedef struct _wksxmpp_t {
    xmpp_ctx_t  *ctx;
    xmpp_conn_t *conn;
    xmpp_log_t  *log;
    pthread_t    pth;
} wksxmpp_t;

#endif//_WKS_XMPP_COMMON_

#include <stdlib.h>
#include <pthread.h>

#include "strophe.h"
#include "wksxmpp.h"
#include "wksxmpp_common.h"

static void _send_presense(xmpp_conn_t *conn, char *to)
{
    xmpp_ctx_t      *ctx;
    xmpp_stanza_t   *szpres;

    ctx = xmpp_conn_get_context(conn);
    szpres = xmpp_stanza_new(ctx);
    xmpp_stanza_set_name(szpres, "presence");
    xmpp_send(conn, szpres);
    xmpp_stanza_release(szpres);
}

static void _conn_handler(xmpp_conn_t * const conn, const xmpp_conn_event_t status, 
                  const int error, xmpp_stream_error_t * const stream_error, 
                  void * const userdata) 
{
    //xmpp_ctx_t  *ctx;
    //wksxmpp_t      *xmpp;

    fprintf(stderr, "\n  _conn_handler(conn<%p>, status(%d), error(%d), stream_error<%p>, userdata<%p>) \n\n", conn, status, error, stream_error, userdata);
    //ctx = xmpp_conn_get_context(conn);
    //xmpp = (wksxmpp_t *) userdata;
    if (status == XMPP_CONN_CONNECT) {
        _send_presense(conn, "");
    } else {
        fprintf(stderr, "\n    unknown status(%d) \n\n", status);
    }
}

static void *pth_func(void *arg)
{
    wksxmpp_t *xmpp;
    xmpp = (wksxmpp_t *) arg;
    xmpp_run(xmpp->ctx);
    return NULL;
}

void *wksxmpp_new()
{
    wksxmpp_t *xmpp;
    xmpp = (wksxmpp_t *) malloc(sizeof(struct _wksxmpp_t));

    xmpp_initialize();

    xmpp->log = xmpp_get_default_logger(XMPP_LEVEL_DEBUG);
    xmpp->ctx = xmpp_ctx_new(NULL, xmpp->log);
    xmpp->conn = xmpp_conn_new(xmpp->ctx);

    return xmpp;
}

void wksxmpp_connect(void *ins, char *host, int port, char *jid, char *pass)
{
    wksxmpp_t *xmpp = (wksxmpp_t *) ins;
    xmpp_conn_set_jid(xmpp->conn, jid);
    xmpp_conn_set_pass(xmpp->conn, pass);

    xmpp_connect_client(xmpp->conn, NULL, 0, _conn_handler, xmpp);
}

void wksxmpp_run_thread(void *ins)
{
    wksxmpp_t *xmpp = (wksxmpp_t *) ins;
    pthread_create(&xmpp->pth, NULL, pth_func, xmpp);
}

void wksxmpp_stop_thread(void *ins)
{
    wksxmpp_t *xmpp = (wksxmpp_t *) ins;
    xmpp_disconnect(xmpp->conn);
    xmpp_stop(xmpp->ctx);
}

void wksxmpp_thread_join(void *ins)
{
    wksxmpp_t *xmpp = (wksxmpp_t *) ins;
    pthread_join(xmpp->pth, NULL);
}

int wksxmpp_release(void *ins)
{
    wksxmpp_t *xmpp = (wksxmpp_t *) ins;
    xmpp_conn_release(xmpp->conn);
    xmpp->conn = NULL;
    xmpp_ctx_free(xmpp->ctx);
    xmpp->ctx = NULL;
    xmpp_shutdown();
    free(xmpp);
    return 0;
}


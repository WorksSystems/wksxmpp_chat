#ifndef _STROPHE_CHAT_
#define _STROPHE_CHAT_

#ifdef __cplusplus
extern "C" {
#endif
#include "strophe.h"

typedef int (*wksxmpp_chat_recv_handler)(xmpp_conn_t *conn, char *from,
        char *msg, void *udata);

int wksxmpp_chat_send_message(xmpp_conn_t *conn, char *to, char *msg);

void wksxmpp_chat_handler_add(xmpp_conn_t *conn, wksxmpp_chat_recv_handler handler,
        void *udata);

void wksxmpp_chat_handler_del(xmpp_conn_t *conn, wksxmpp_chat_recv_handler handler);

#ifdef __cplusplus
}
#endif

#endif//_STROPHE_CHAT_

#include <string.h>

#include "wksxmpp_common.h"
#include "wksxmpp_chat.h"

int wksxmpp_chat_send_message(void *ins, char *to, char *msg)
{
    xmpp_stanza_t   *szmsg, *szbody, *sztext;
    xmpp_ctx_t      *ctx;
    wksxmpp_t       *xmpp = (wksxmpp_t *) ins;

    ctx = xmpp_conn_get_context(xmpp->conn);

    sztext = xmpp_stanza_new(ctx);
    xmpp_stanza_set_text(sztext, msg);

    szbody = xmpp_stanza_new(ctx);
    xmpp_stanza_set_name(szbody, "body");
    xmpp_stanza_add_child(szbody, sztext);

    szmsg = xmpp_stanza_new(ctx);
    xmpp_stanza_set_name(szmsg, "message");
    xmpp_stanza_set_type(szmsg, "chat");
    xmpp_stanza_set_attribute(szmsg, "to", to);
    xmpp_stanza_add_child(szmsg, szbody);

    xmpp_send(xmpp->conn, szmsg);
    xmpp_stanza_release(szmsg);

    return 0;
}

int message_handler(xmpp_conn_t * const conn, xmpp_stanza_t * const stanza, void * const userdata)
{
        
    char        *intext;

    wksxmpp_chat_recv_handler recv_handler = (wksxmpp_chat_recv_handler) userdata;

    if(!xmpp_stanza_get_child_by_name(stanza, "body")) return 1;
    if(xmpp_stanza_get_attribute(stanza, "type") !=NULL && !strcmp(xmpp_stanza_get_attribute(stanza, "type"), "error")) return 1;
    intext = xmpp_stanza_get_text(xmpp_stanza_get_child_by_name(stanza, "body"));

    printf("Incoming message from %s: %s\n", xmpp_stanza_get_attribute(stanza, "from"), intext);
    recv_handler(conn, xmpp_stanza_get_attribute(stanza, "from"), intext);
    return 1;
}


void wksxmpp_chat_handler_add(void *ins, wksxmpp_chat_recv_handler handler)
{
    wksxmpp_t   *xmpp = (wksxmpp_t *) ins;
    xmpp_handler_add(xmpp->conn, message_handler, NULL, "message", "chat", handler);
}

void wksxmpp_chat_handler_del(void *ins, wksxmpp_chat_recv_handler handler)
{
    wksxmpp_t   *xmpp = (wksxmpp_t *) ins;
    xmpp_handler_delete(xmpp->conn, message_handler);
}

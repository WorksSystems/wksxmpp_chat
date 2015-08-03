#ifndef _STROPHE_CHAT_
#define _STROPHE_CHAT_

#ifdef __cplusplus
extern "C" {
#endif

typedef int (*wksxmpp_chat_recv_handler)(void *ins, char *from, char *msg);

int wksxmpp_chat_send_message(void *ins, char *to, char *msg);

void wksxmpp_chat_handler_add(void *ins, wksxmpp_chat_recv_handler handler);

void wksxmpp_chat_handler_del(void *ins, wksxmpp_chat_recv_handler handler);

#ifdef __cplusplus
}
#endif

#endif//_STROPHE_CHAT_

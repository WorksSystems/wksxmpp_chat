#ifndef _STROPHE_HELPER_
#define _STROPHE_HELPER_

#ifdef __cplusplus
extern "C" {
#endif

#include "strophe.h"

void *wksxmpp_new();

void wksxmpp_connect(void *ins, char *host, int port, char *jid, char *pass);

void wksxmpp_run_thread(void *ins);

void wksxmpp_stop_thread(void *ins);

void wksxmpp_thread_join(void *ins);

int wksxmpp_release(void *ins);

xmpp_conn_t *wksxmpp_get_conn(void *ins);

#ifdef __cplusplus
}
#endif

#endif//_STROPHE_HELPER_

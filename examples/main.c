#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

#include "wksxmpp.h"
#include "wksxmpp_chat.h"

char g_rejid[256];

int chat_recv_handler(xmpp_conn_t *xmpp, char *from, char *msg, void *udata)
{
    fprintf(stderr, "\n  chat_recv_handler(conn<%p>, from'%s', msg'%s'\n\n", xmpp, from, msg);
    strcpy(g_rejid, from);
    return 0;
}

void print_usage()
{
    printf("Usage: command [-s host -p port -j jid -w password -t tojid]\n");
}

int main(int argc, char *argv[])
{
    bool    looping = true;
    int     c, opt;
    void   *xmpp;

    char *host = "localhost", *jid = "user1@localhost/res1", *pass = "1234", *tojid = "user1@localhost/res1";
    int   port = 5222;

    while ((opt = getopt(argc, argv, "s:p:w:j:t:h")) != -1)
    {
        switch(opt)
        {
            case 's':
                host = optarg;
                break;
            case 'p':
                port = atoi(optarg);
                break;
            case 'w':
                pass = optarg;
                break;
            case 'j':
                jid = optarg;
                break;
            case 't':
                tojid = optarg;
                break;
            case 'h':
            default:
                print_usage();
                return -1;
        }
    }

    xmpp = wksxmpp_new();
    wksxmpp_connect(xmpp, host, port, jid, pass);
    wksxmpp_chat_handler_add(wksxmpp_get_conn(xmpp), chat_recv_handler, xmpp);
    wksxmpp_run_thread(xmpp);

    while (looping) {
        c = getchar();
        switch (c) {
            case 'q' :
                wksxmpp_stop_thread(xmpp);
                looping = false;
                break;
            case 's' :
                wksxmpp_chat_send_message(wksxmpp_get_conn(xmpp), tojid, "hello world");
                break;
            case 'r' :
                wksxmpp_chat_send_message(wksxmpp_get_conn(xmpp), g_rejid, "reply message");
                break;
            default :
                break;
        }
    }
    wksxmpp_thread_join(xmpp);
    wksxmpp_chat_handler_del(wksxmpp_get_conn(xmpp), chat_recv_handler);

    wksxmpp_release(xmpp);
    return 0;
}

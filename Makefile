TARGET=main

LIBCHAT=wksxmpp_chat
LIBWKSXMPP=wksxmpp

AR=ar
CC=gcc
CFLAGS=-Wall -Werror -fPIC
LIBFLAGS=
INCPATH=-I./inc -I../libstrophe/
LIBPATH=-L./ -L../libstrophe/.libs/
RPATH=-Wl,-rpath=./ -Wl,-rpath=../libstrophe/.libs/
LIBS=-l$(LIBCHAT) -l$(LIBWKSXMPP) -lstrophe -lssl -lcrypto -lexpat -lpthread
LDFLAGS=$(LIBPATH) $(LIBS)

MAINOBJ=examples/main.o
LIBOBJS=src/wksxmpp.o src/wksxmpp_chat.o

SHAREDLIBCHAT=lib$(LIBCHAT).so
STATICLIBCHAT=lib$(LIBCHAT).a
SHAREDLIBWKSXMPP=lib$(LIBWKSXMPP).so
STATICLIBWKSXMPP=lib$(LIBWKSXMPP).a

LIBRARIES=$(SHAREDLIBCHAT) $(STATICLIBCHAT) $(SHAREDLIBWKSXMPP) $(STATICLIBWKSXMPP)

all: libraries $(TARGET)

libraries: $(LIBRARIES)

$(TARGET): $(MAINOBJ)
	$(CC) -o $@ $(RPATH) $(MAINOBJ) $(LIBPATH) $(LIBS)

$(SHAREDLIBCHAT): src/wksxmpp_chat.o
	$(CC) -o $@ $(LIBFLAGS) -shared $^

$(STATICLIBCHAT): src/wksxmpp_chat.o
	$(AR) -c -r $@ $^

$(SHAREDLIBWKSXMPP): src/wksxmpp.o
	$(CC) -o $@ $(LIBFLAGS) -shared $^

$(STATICLIBWKSXMPP): src/wksxmpp.o
	$(AR) -c -r $@ $^

clean:
	rm -f $(LIBOBJS) $(LIBRARIES) $(MAINOBJ) $(TARGET)

.c.o:
	$(CC) -o $@ $(CFLAGS) $(INCPATH) -c $<

.c.os:
	$(CC) -o $@ $(CFLAGS) $(INCPATH) -c $<

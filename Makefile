TARGET=main

LIBCHAT=wksxmpp_chat
LIBWKSXMPP=wksxmpp

AR=ar
CC=gcc
CFLAGS=-Wall -Werror -fPIC
LIBFLAGS=
INCPATH=-I./ -I../../libstrophe/libstrophe/
LIBPATH=-L./ -L../../libstrophe/libstrophe/.libs/
RPATH=-Wl,-rpath=./ -Wl,-rpath=../../libstrophe/libstrophe/.libs/
LIBS=-l$(LIBCHAT) -l$(LIBWKSXMPP) -lstrophe -lssl -lcrypto -lexpat -lpthread
LDFLAGS=$(LIBPATH) $(LIBS)

MAINOBJ=main.o
LIBOBJS=wksxmpp.o wksxmpp_chat.o

SHAREDLIBCHAT=lib$(LIBCHAT).so
STATICLIBCHAT=lib$(LIBCHAT).a
SHAREDLIBWKSXMPP=lib$(LIBWKSXMPP).so
STATICLIBWKSXMPP=lib$(LIBWKSXMPP).a

LIBRARIES=$(SHAREDLIBCHAT) $(STATICLIBCHAT) $(SHAREDLIBWKSXMPP) $(STATICLIBWKSXMPP)

all: libraries $(TARGET)

libraries: $(LIBRARIES)

$(TARGET): $(MAINOBJ)
	$(CC) -o $@ $(RPATH) $(MAINOBJ) $(LIBPATH) $(LIBS)

$(SHAREDLIBCHAT): wksxmpp_chat.o
	$(CC) -o $@ $(LIBFLAGS) -shared $^

$(STATICLIBCHAT): wksxmpp_chat.o
	$(AR) -c -r $@ $^

$(SHAREDLIBWKSXMPP): wksxmpp.o
	$(CC) -o $@ $(LIBFLAGS) -shared $^

$(STATICLIBWKSXMPP): wksxmpp.o
	$(AR) -c -r $@ $^

clean:
	rm -f $(LIBOBJS) $(LIBRARIES) $(MAINOBJ) $(TARGET)

.c.o:
	$(CC) -o $@ $(CFLAGS) $(INCPATH) -c $<

.c.os:
	$(CC) -o $@ $(CFLAGS) $(INCPATH) -c $<

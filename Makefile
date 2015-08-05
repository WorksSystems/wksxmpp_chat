TARGET=main

LIBCHAT=wksxmpp_chat
LIBWKSXMPP=wksxmpp

LIBSTROPHE_BASE?=../libstrophe

AR=ar
CC=gcc
CFLAGS=-Wall -Werror -fPIC
LIBFLAGS=
INCPATH=-I./inc -I${LIBSTROPHE_BASE}
LIBPATH=-L./ -L${LIBSTROPHE_BASE}/.libs/
RPATH=-Wl,-rpath=./ -Wl,-rpath=${LIBSTROPHE_BASE}/.libs/
LIBS=-l$(LIBCHAT) -l$(LIBWKSXMPP) -lstrophe -lssl -lcrypto -lexpat -lpthread -lm
LDFLAGS=$(LIBPATH) $(LIBS)

MAINOBJ=out/main.o
LIBOBJS=out/wksxmpp.o out/wksxmpp_utils.o out/wksxmpp_chat.o

SHAREDLIBCHAT=lib$(LIBCHAT).so
STATICLIBCHAT=lib$(LIBCHAT).a
SHAREDLIBWKSXMPP=lib$(LIBWKSXMPP).so
STATICLIBWKSXMPP=lib$(LIBWKSXMPP).a

LIBRARIES=$(SHAREDLIBCHAT) $(STATICLIBCHAT) $(SHAREDLIBWKSXMPP) $(STATICLIBWKSXMPP)

all: out libraries $(TARGET)

libraries: $(LIBRARIES)

out:
	mkdir -p $@

$(TARGET): $(MAINOBJ)
	$(CC) -o $@ $(RPATH) $(MAINOBJ) $(LIBPATH) $(LIBS)

$(SHAREDLIBCHAT): out/wksxmpp_chat.o
	$(CC) -o $@ $(LIBFLAGS) -shared $^

$(STATICLIBCHAT): out/wksxmpp_chat.o
	$(AR) -c -r $@ $^

$(SHAREDLIBWKSXMPP): out/wksxmpp.o out/wksxmpp_utils.o
	$(CC) -o $@ $(LIBFLAGS) -shared $^

$(STATICLIBWKSXMPP): out/wksxmpp.o out/wksxmpp_utils.o
	$(AR) -c -r $@ $^

clean:
	rm -rf out $(LIBOBJS) $(LIBRARIES) $(MAINOBJ) $(TARGET)

out/%.o: src/%.c
	$(CC) -o $@ $(CFLAGS) $(INCPATH) -c $<

out/main.o: examples/main.c
	$(CC) -o $@ $(CFLAGS) $(INCPATH) -c $<

#.c.o:
#	$(CC) -o $@ $(CFLAGS) $(INCPATH) -c $<


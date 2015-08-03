import os
LIBSTROPHEPATH='../libstrophe'
INC_PATH=[LIBSTROPHEPATH, 'inc']
libenv = Environment()
libenv.AppendUnique(CPPPATH = INC_PATH, CCFLAGS = ['-Wall', '-Werror'])
libenv.SharedLibrary('wksxmpp_chat', ['src/wksxmpp_chat.c'])
libenv.SharedLibrary('wksxmpp', ['src/wksxmpp.c'])
libenv.StaticLibrary('wksxmpp_chat', ['src/wksxmpp_chat.c'])
libenv.StaticLibrary('wksxmpp', ['src/wksxmpp.c'])

LIB_PATH=[LIBSTROPHEPATH + '/.libs/', '.']
env = Environment()
env.AppendUnique(CPPPATH = INC_PATH, CCFLAGS = ['-Wall', '-Werror'])
env.AppendUnique(LIBS = ['wksxmpp_chat', 'wksxmpp', 'strophe', 'pthread'], LIBPATH = LIB_PATH, RPATH = LIB_PATH)
env.Program('examples/main.c')


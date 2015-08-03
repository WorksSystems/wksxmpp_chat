import os
LIBSTROPHEPATH='../../libstrophe/libstrophe'
INC_PATH=[LIBSTROPHEPATH, '.']
libenv = Environment()
libenv.AppendUnique(CPPPATH = INC_PATH, CCFLAGS = ['-Wall', '-Werror'])
libenv.SharedLibrary('wksxmpp_chat', ['wksxmpp_chat.c'])
libenv.SharedLibrary('wksxmpp', ['wksxmpp.c'])

LIB_PATH=[LIBSTROPHEPATH + '/.libs/', '.']
env = Environment()
env.AppendUnique(CPPPATH = INC_PATH, CCFLAGS = ['-Wall', '-Werror'])
env.AppendUnique(LIBS = ['wksxmpp_chat', 'wksxmpp', 'strophe', 'pthread'], LIBPATH = LIB_PATH, RPATH = LIB_PATH)
env.Program('main.c')


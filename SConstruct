import os

LIBSTROPHE_BASE='../libstrophe'
if ARGUMENTS.get('LIBSTROPHE_BASE') is not None :
	LIBSTROPHE_BASE=ARGUMENTS.get('LIBSTROPHE_BASE')

INC_PATH=[LIBSTROPHE_BASE, 'inc']
libenv = Environment()
libenv.AppendUnique(CPPPATH = INC_PATH, CCFLAGS = ['-Wall', '-Werror'])
libenv.SharedLibrary('wksxmpp_chat', ['src/wksxmpp_chat.c'])
libenv.SharedLibrary('wksxmpp', ['src/wksxmpp.c', 'src/wksxmpp_utils.c'])
libenv.StaticLibrary('wksxmpp_chat', ['src/wksxmpp_chat.c'])
libenv.StaticLibrary('wksxmpp', ['src/wksxmpp.c', 'src/wksxmpp_utils.c'])

LIB_PATH=[LIBSTROPHE_BASE + '/.libs/', '.']
env = Environment()
env.AppendUnique(CPPPATH = INC_PATH, CCFLAGS = ['-Wall', '-Werror'])
env.AppendUnique(LIBS = ['wksxmpp_chat', 'wksxmpp', 'strophe', 'pthread', 'm'], LIBPATH = LIB_PATH, RPATH = LIB_PATH)
env.Program('examples/main.c')


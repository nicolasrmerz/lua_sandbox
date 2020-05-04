all:
	gcc -o main main.c lua_entity.c lua_util.c lua_hook.c -Wall -I/usr/include/lua5.3 -L/usr/lib/x86_64-linux-gnu/ -llua5.3

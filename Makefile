all:
	gcc -o main main.c -Wall -I/usr/include/lua5.3 -L/usr/lib/x86_64-linux-gnu/ -llua5.3

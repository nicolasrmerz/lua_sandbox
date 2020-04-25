#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

//#include "mylua.h"

void error (lua_State *L, const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaL_dofile(L, "init.lua");
    luaL_dofile(L, "script.lua");
    lua_getglobal(L, "CallHook");
    lua_pushinteger(L, 5);
    if(lua_pcall(L, 0, 0, 0) != 0)
        error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
    lua_close(L);

    return 0;
}

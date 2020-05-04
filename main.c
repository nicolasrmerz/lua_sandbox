#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "lua_entity.h"
#include "lua_util.h"

int main() {
    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
    luaopen_ent(L);
    if(luaL_dofile(L, "init.lua") != 0)
        qlua_error(L, "error running init.lua: %s\n", lua_tostring(L, -1));
    if(luaL_dofile(L, "script.lua") != 0)
        qlua_error(L, "error running script.lua: %s\n", lua_tostring(L, -1));
    /*
    lua_getglobal(L, "CallHook");
    lua_pushinteger(L, 5);
    if(lua_pcall(L, 0, 0, 0) != 0)
        error(L, "error running function hook.test: %s\n", lua_tostring(L, -1));
    */
    lua_close(L);

    return 0;
}

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#include "lua_util.h"

void qlua_error (lua_State *L, const char *fmt, ...)
{
    va_list argp;
    va_start(argp, fmt);
    vfprintf(stderr, fmt, argp);
    va_end(argp);
    lua_close(L);
    exit(EXIT_FAILURE);
}

int qlua_checkhook(lua_State *L, const char *hook)
{
    int found;

    if (hook) {
        lua_getglobal(L, "CheckHook");
        lua_pushstring(L, hook);

        if(lua_pcall(L, 1, 1, 0) != 0)
            qlua_error(L, "error running function CheckHook: %s\n", lua_tostring(L, -1));

        found = lua_toboolean(L, -1);
        lua_pop(L, 1);
        return found;
    }
    return 0;
}

void qlua_gethook(lua_State *L, const char *hook)
{
    if (hook) {
        lua_getglobal(L, "CallHook");
        lua_pushstring(L, hook);
    }
}

int qlua_check_and_get_hook(lua_State *L, const char *hook)
{
    if (qlua_checkhook(L, hook)) {
        qlua_gethook(L, hook);
        return 1;
    }
    return 0;
}

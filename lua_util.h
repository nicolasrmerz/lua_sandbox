#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

void qlua_error (lua_State *L, const char *fmt, ...);
int luaL_typerror(lua_State *L, int narg, const char *tname);

#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

int qlua_checkhook(lua_State *L, const char *hook);

void qlua_gethook(lua_State *L, const char *hook);

int qlua_check_and_get_hook(lua_State *L, const char *hook);

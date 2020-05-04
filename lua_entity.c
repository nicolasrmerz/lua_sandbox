#include <stdio.h>
#include <string.h>
#include "lua_entity.h"
#include "lua_util.h"

int le_new_ent(lua_State *L)
{
    size_t nbytes = sizeof(entity);

    lua_newuserdata(L, nbytes);

    luaL_getmetatable(L, "Entity");
    lua_setmetatable(L, -2);

    return 1;
}

entity* le_to_ent(lua_State *L, int i)
{
    entity* e;

    if(luaL_checkudata(L, i, "Entity") == NULL) {
        luaL_typerror(L, i, "Entity");
        return NULL;
    }

    e = (entity*)lua_touserdata(L, i);

    return e;
}

int le_set_name(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA); 
    luaL_checktype(L, 2, LUA_TSTRING);

    entity* e = le_to_ent(L, 1);
    
    // When porting to Quake: replace with
    // Q_strncpyz
    // which ensures trailing NULL byte
    // Also, do entity fields have MAX_STRING_CHARS for string size??
    strncpy(e->name, lua_tostring(L,2), MAX_STRING_CHARS);

    return 0;
}

int le_get_name(lua_State *L)
{
    luaL_checktype(L, 1, LUA_TUSERDATA);

    entity* e = le_to_ent(L, 1);

    lua_pushstring(L, e->name);

    return 1;
}

static const struct luaL_Reg entlib_f [] = {
    {"new", le_new_ent},
    {NULL, NULL}
};

static const struct luaL_Reg entlib_m [] = {
    {"__tostring", le_get_name},
    {"setName", le_set_name},
    {"getName", le_get_name},
    {NULL, NULL}
};

int luaopen_ent (lua_State *L)
{
    luaL_newmetatable(L, "Entity");

    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);
    lua_settable(L, -3);

    luaL_setfuncs(L, entlib_m, 0);
    luaL_setfuncs(L, entlib_f, 0);
    lua_setglobal(L, "Entity");
    return 1;
}

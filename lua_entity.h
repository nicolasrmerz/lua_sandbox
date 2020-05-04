#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

#define MAX_STRING_CHARS 1024

typedef struct entity {
    char name[MAX_STRING_CHARS];
    int id;
    int health;
} entity;

int le_new_ent(lua_State *L);
int le_set_name(lua_State *L);
int le_get_name(lua_State *L);
int luaopen_ent(lua_State *L);

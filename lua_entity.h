#include <lauxlib.h>
#include <lua.h>
#include <lualib.h>

typedef struct entity {
    char name[50];
    int id;
    int health;
} entity;
